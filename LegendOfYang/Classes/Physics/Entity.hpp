//
//  Entity.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/15/18.
//
// Description: Represents some object in the overworld like an item, the player, or an enemy. Design wise this is a bad class but it follows the conventions of cocos by jamming everything into one giant node class

#pragma once
USING_NS_CC;
#include "Utility.hpp"

class Entity : public Sprite {
public:
    virtual bool init() override;
    void update(float delta) override;
    
    CREATE_FUNC(Entity);
    static Entity* create(std::string filename);
    
    // Interaction Properties
    std::function<void()> interact;
    
    // Physics properties
    Rect getCollisionBox() { return getBoundingBox(); }
    Vec2 velocity;
    bool isSolid;
};
