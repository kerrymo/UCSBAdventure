//
//  Entity.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/15/18.
//

#include "Entity.hpp"
bool Entity::init() {
    // call parent init
    if (!Sprite::init()) return false;
    scheduleUpdateWithPriority(LOOP_UPDATE_ORDER_ENTITY);
    isSolid = true;
    isDynamic = false;
    behavior = []() {
        
    };
    setAnchorPoint(Vec2(0.0f, 0.0f));
    
    
    return true;
}

void Entity::setOrientation(Vec2 direction) {
    direction.normalize();
    orientation = direction;
    EventCustom event("orientation-changed");
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
    // TODO : Add a sprite that can face 4 or 8 directions and set the right image here according to the correct direction
}

Entity* Entity::create(std::string filename) {
    auto entity = create();
    entity->setTexture(filename);
    return entity;
}

void Entity::update(float delta) {
    if (isDynamic) {
        behavior();
        if (fabsf(velocity.x) > 0.1f || fabsf(velocity.y) > 0.1f) {
            setOrientation(velocity);
        }
        setPosition(getPosition() + velocity * delta);
    }
}

void Entity::addChild(Node *child) {
    Sprite::addChild(child);
    EventCustom event("childrenChanged");
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
}

void Entity::removeChild(Node *child, bool cleanup) {
    Sprite::removeChild(child, cleanup);
    EventCustom event("childrenChanged");
    event.setUserData(this);
    getEventDispatcher()->dispatchEvent(&event);
}

// Converts bounding box to screenspace from node space since collisions are computed in screen space
Rect Entity::getCollisionBox() {
    Rect r = getBoundingBox();
    r.origin = convertToWorldSpace(-getAnchorPointInPoints());
    return r;
}

// Technically only gets the children of Entities
Vector<Entity*> Entity::getAllEntities() {
    Vector<Entity*> allEntities;
    for(auto  node : _children)
    {
        auto entity = dynamic_cast<Entity*>(node);
        if (entity != nullptr) {
            allEntities.pushBack(entity);
            Vector<Entity*>  entities = entity->getAllEntities();
            if(entities.size() > 0) {
                allEntities.pushBack(entities);
            }
        }
        
        
    }
    return  allEntities;
}
