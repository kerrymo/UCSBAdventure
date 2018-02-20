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
    
    // Getters setters
    Vec2 getOrientation() { return orientation; }
    void setOrientation(Vec2 direction);
    
    // Interaction Properties
    std::function<void()> interact;
    std::function<void()> behavior;
    
    // Physics properties
    Rect getCollisionBox();
    Vec2 velocity;
    // Right now a body should either be solid or dynamic or neither not both you will get weird behavior if both are enabled
    // I might fix it in the future though - John
    bool isSolid;
    bool isDynamic;
    // End physics properties
    
    // This is only useful for pausing and unpausing the game world
    void addChild(Node *child) override;
    void removeChild(Node *child, bool cleanup) override;
    // Useful for physics
    Vector<Entity*> getAllEntities();
protected:
    Vec2 orientation; // Doesn't control the rotation of entity just keeps track of the direction its facing
    
};
