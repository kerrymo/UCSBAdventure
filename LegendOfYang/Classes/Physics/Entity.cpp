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
    scheduleUpdate(); // Just makes it so gameobjects are updated before collision resolution
    return true;
}

Entity* Entity::create(std::string filename) {
    auto entity = create();
    entity->setTexture(filename);
    return entity;
}

void Entity::update(float delta) {
    //setPosition(getPosition() + velocity * delta);
}
