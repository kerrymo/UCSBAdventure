//
//  YangPhysics.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//
// Description : Handles collisions. You might find the callback function useful

#pragma once
#include "Entity.hpp"
#include "Utility.hpp"
#include <unordered_set>
USING_NS_CC;

class YangPhysics : public Entity {
public:
    
    
    // Description : Creates a physics world with corresponding collideable squares that are marked in the tilemap.
    // Precondition : map has a layer named meta with tiles that have id = 49 corresponding to collisions
    // Postcondition : This node should be added to the node thats contents you want to have collisions simulated.
    // So basically add it to the node representing the game world
    static YangPhysics* createWithTileMap(TMXTiledMap *map);
    
    // Description : Gives a list of the objects that collide with aabb
    Vector<Entity*> getCollidingEntities(Rect aabb);
    
    // Description : Whenever node collides with another node callback is called with arguments node and the node it collided with in that order
    // Note : This function is called once on contact
    void registerCallbackOnContact(const std::function<void(Entity*, Entity*)> &callback, Entity *node);
    
    // Description : Whenever node seperates with another node callback is called with arguments node and the node it seperated from in that order
    void registerCallbackOnSeperate(const std::function<void(Entity*, Entity*)> &callback, Entity *node);
    
    // Description : Pauses all scheduled selectors, actions and event listeners for nodes in the world
    void pauseAll();
    
    // Description : Resumes all scheduled selectors, actions and event listeners for nodes in the world
    void resumeAll();
    
protected:
    CREATE_FUNC(YangPhysics);
    virtual bool init() override;
    void update(float delta) override;
    
    void resolve(Entity *entity, const std::vector<Rect> &boundingBoxes);
    __int128 contactRepresentation(Entity *n1, Entity *n2);
    std::unordered_map<uint64_t, std::function<void(Entity*, Entity*)>> callbacks;
    std::unordered_map<uint64_t, std::function<void(Entity*, Entity*)>> contactEndedCallbacks;
    std::unordered_set<__int128> currentContacts;
    TMXTiledMap *tileMap;
    TMXLayer *meta;
};
