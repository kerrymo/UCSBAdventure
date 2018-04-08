//
//  YangPhysics.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#include "YangPhysics.hpp"
#include <iostream>

bool YangPhysics::init() {
    if (!Node::init()) return false;
    scheduleUpdateWithPriority(LOOP_UPDATE_ORDER_PHYSICS_WORLD); // Just makes it so gameobjects are updated before collision resolution
    
    return true;
}

YangPhysics* YangPhysics::createWithTileMap(TMXTiledMap *map) {
    auto physics = create();
    physics->tileMap = map;
    physics->meta = map->getLayer("Meta");
    physics->GID = physics->meta->getTileSet()->_firstGid;
    return physics;
}

Vector<Entity*> YangPhysics::getCollidingEntities(Rect aabb) {
    Vector<Entity*> intersectedEntities;
    
    auto worldNodes = getParent()->getChildren();
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        if (entity != nullptr) {
            auto boundingBox = entity->getBoundingBox();
            boundingBox.origin = entity->convertToWorldSpace(Vec2::ZERO);
            if (boundingBox.intersectsRect(aabb)) {
                intersectedEntities.pushBack(entity);
            }
            
        }
    }
    
    return intersectedEntities;
}

void YangPhysics::registerCallbackOnContact(const std::function<void(Entity*, Entity*)> &callback, Entity *node) {
    callbacks[(uint64_t)node] = callback;
}

void YangPhysics::registerCallbackOnSeperate(const std::function<void(Entity*, Entity*)> &callback, Entity *node) {
    contactEndedCallbacks[(uint64_t)node] = callback;
}

void YangPhysics::resolve(Entity *entity, const std::vector<Rect> &boundingBoxes) {
    auto boundingBox = entity->getBoundingBox();
    for (auto boundingBox2 : boundingBoxes) {
        if (boundingBox.intersectsRect(boundingBox2) && !boundingBox.equals(boundingBox2)) {
            float dx = (boundingBox.size.width + boundingBox2.size.width) / 2.0f - fabsf(boundingBox.getMidX() - boundingBox2.getMidX());
            float dy = (boundingBox.size.height + boundingBox2.size.height) / 2.0f - fabsf(boundingBox.getMidY() - boundingBox2.getMidY());
            if (fabsf(dx / entity->velocity.x+0.001f) < fabsf(dy / entity->velocity.y+0.001f)) {
                // Intersected on x side first
                if (boundingBox.origin.x < boundingBox2.origin.x) {
                    entity->setPosition(Vec2(boundingBox.origin.x - dx - 1.0f, entity->getPosition().y));
                } else {
                    entity->setPosition(Vec2(boundingBox.origin.x + dx + 1.0f, entity->getPosition().y));
                }
                
            } else {
                if (boundingBox.origin.y < boundingBox2.origin.y) {
                    entity->setPosition(Vec2(entity->getPosition().x, boundingBox.origin.y - dy));
                } else {
                    entity->setPosition(Vec2(entity->getPosition().x, boundingBox.origin.y + dy));
                }
            }
        }
    }
}

void YangPhysics::update(float delta) {
    auto worldNodes = dynamic_cast<Entity*>(getParent())->getAllEntities();
    std::vector<Rect> entityBoundingBoxes;
    Vector<Entity*> entities;
    
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        if (entity != nullptr) {
            if (entity->isSolid) {
                entityBoundingBoxes.push_back(entity->getBoundingBox());
            }
            entities.pushBack(entity);
        }
    }
    
    // Very inefficient since you effectively do the same thing twice compared with the other loop but very easy to code
    for (auto entity : entities) {
        if (callbacks.find((uint64_t)entity) != callbacks.end()) {
            for (auto otherEntity : entities) {
                if (entity->getCollisionBox().intersectsRect(otherEntity->getCollisionBox())) {
                    const auto contact = contactRepresentation(entity, otherEntity);
                    if (currentContacts.find(contact) == currentContacts.end()) {
                        callbacks[(uint64_t)entity](entity, otherEntity);
                         currentContacts.insert(contact);
                        entity->retain(); // Take ownership because I'm storing these in the state of the physics handler
                        otherEntity->retain();
                    }
                }
            }
        }
    }
    
    auto currentContactsCopy = currentContacts; // Can't mutate the set you're iterating through can cause a segfault
    for (auto contact : currentContactsCopy) {
        Entity *node1 = (Entity*)contact;
        Entity *node2 = (Entity*)(contact>>64);
        
        // Handle stale references
        if (!node1->getParent()) { node1->release(); }
        if (!node2->getParent()) { node2->release(); }
        if (!node1->getParent() || !node2->getParent()) { currentContacts.erase(contactRepresentation(node1, node2)); continue; }
        
        if (!node1->getCollisionBox().intersectsRect(node2->getCollisionBox())) {
            if (contactEndedCallbacks.find((uint64_t)node1) != contactEndedCallbacks.end()) {
                contactEndedCallbacks[(uint64_t)node1](node1, node2);
            }
            if (contactEndedCallbacks.find((uint64_t)node2) != contactEndedCallbacks.end()) {
                contactEndedCallbacks[(uint64_t)node2](node2, node1);
            }
            currentContacts.erase(contactRepresentation(node1, node2));
        }
        
    }
    
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        std::vector<Rect> boundingBoxs;
        if (entity != nullptr && entity->isDynamic && entity->isSolid) {
            Vec2 tilePlayerIsOn = tileCoordForPosition(entity->getPosition() + entity->getContentSize()/2, tileMap);
            for (int i = tilePlayerIsOn.x - 1; i < tilePlayerIsOn.x + 2; i++) {
                for (int j = tilePlayerIsOn.y - 1; j < tilePlayerIsOn.y + 2; j++) {
                    if (i >= 0 && j >= 0 && i < tileMap->getMapSize().width && j < tileMap->getMapSize().height && meta->getTileGIDAt(Vec2(i,j)) == GID) {
                        boundingBoxs.push_back(meta->getTileAt(Vec2(i,j))->getBoundingBox());
                    }
                }
            }
            
            boundingBoxs.insert(boundingBoxs.end(), entityBoundingBoxes.begin(), entityBoundingBoxes.end());
            resolve(entity, boundingBoxs);
        }
    }
    
}

__int128 YangPhysics::contactRepresentation(Entity *n1, Entity *n2) {
    __int128 x1 = (uint64_t)n1;
    __int128 x2 = (uint64_t)n2;
    if ( x1 > x2 ) {
        return x1 | (x2 << 64);
    } else {
        return x2 | (x1 << 64);
    }
}

void YangPhysics::pauseAll() {
    auto worldNodes = getParent()->getChildren();
    
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        if (entity != nullptr) {
            entity->pause();
        }
    }
}

void YangPhysics::resumeAll() {
    auto worldNodes = getParent()->getChildren();
    
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        if (entity != nullptr) {
            entity->resume();
        }
    }
}

