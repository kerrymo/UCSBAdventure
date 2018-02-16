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
    return physics;
}

void YangPhysics::update(float delta) {
    auto worldNodes = getParent()->getChildren();
    
    
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        if (entity != nullptr) {
            entity->setPosition(entity->getPosition() + entity->velocity * delta);
        }
    }
    
    for (auto node : worldNodes) {
        auto entity = dynamic_cast<Entity*>(node); // Kind of bad design we can live with it for now though
        if (entity != nullptr) {
            Vec2 tilePlayerIsOn = tileCoordForPosition(entity->getPosition() + entity->getContentSize()/2, tileMap);
            auto boundingBox = entity->getBoundingBox();
            for (int i = tilePlayerIsOn.x - 1; i < tilePlayerIsOn.x + 2; i++) {
                for (int j = tilePlayerIsOn.y - 1; j < tilePlayerIsOn.y + 2; j++) {
                    if (i >= 0 && j >= 0 && i < tileMap->getMapSize().width && j < tileMap->getMapSize().height && meta->getTileGIDAt(Vec2(i,j)) == 49 && boundingBox.intersectsRect(meta->getTileAt(Vec2(i,j))->getBoundingBox())) {
                        auto boundingBox2 = meta->getTileAt(Vec2(i,j))->getBoundingBox();
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
        }
    }
    
}

