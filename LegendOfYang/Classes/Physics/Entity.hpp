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
    
    // Description : creates an entity with no textures
    CREATE_FUNC(Entity);
    
    // Description : creates an entity with a sprite
    static Entity* create(std::string filename);
    
    // Description : Returns the orientation as a unit vector
    Vec2 getOrientation() { return orientation; }
    
    // Description : Sets orientation as a unit vector
    // Precondition : direction can be of any magnitude
    // Postcondition : orientation is a unit vector pointing in the same direction as direction
    void setOrientation(Vec2 direction);
    
    /**
     Makes this entity oriented toward target
     */
    void face(Entity *target) { setOrientation(target->getCollisionBox().origin - this->getCollisionBox().origin); };
    
    // Interaction Properties
    
    // Description : This is called when the player interacts with this entity.
    // Use Case : An NPC would probably present a text box to the gui when interacted with.
    std::function<void()> interact;
    
    // Description : This is called in the update loop of the entity
    std::function<void()> behavior;
    
    // Description : Returns the bounding box of the node in terms of screen space since thats where collisions are computed
    Rect getCollisionBox();
    
    // Description : in points/seconds
    Vec2 velocity;
    
    // Note: Right now a body should either be solid or dynamic or neither not both you will get weird behavior if both are enabled.
    // Description : Determines whether if collisions resolve. You would disable this if all you're interested in doing is spatial queries
    // i.e. checking if a player lies in the view of an enemy
    bool isSolid;
    
    // Description : Determines whether
    bool isDynamic;
    // End physics properties
    
    // Description : These methods were overwritten to send events nothing else was changed
    void addChild(Node *child) override;
    void removeChild(Node *child, bool cleanup) override;
    
    // Description : Returns all the entities in a tree
    Vector<Entity*> getAllEntities();
    
protected:
    virtual bool init() override;
    void update(float delta) override;
    
    Vec2 orientation; // Doesn't control the rotation of entity just keeps track of the direction its facing
    
};
