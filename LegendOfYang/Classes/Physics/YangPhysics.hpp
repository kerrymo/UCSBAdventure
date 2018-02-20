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

struct Contact {
    Entity* n1;
    Entity* n2;
};

class YangPhysics : public Entity {
public:
    CREATE_FUNC(YangPhysics);
    virtual bool init() override;
    static YangPhysics* createWithTileMap(TMXTiledMap *map);
    
    Vector<Entity*> getCollidingEntities(Rect aabb); // Used for interaction
    void registerCallbackOnContact(const std::function<void(Entity*, Entity*)> &callback, Entity *node);
    void registerCallbackOnSeperate(const std::function<void(Entity*, Entity*)> &callback, Entity *node);
    void update(float delta) override;
    
    void pauseAll();
    void resumeAll();
    
protected:
    void resolve(Entity *entity, const std::vector<Rect> &boundingBoxes);
    __int128 contactRepresentation(Entity *n1, Entity *n2);
    std::unordered_map<uint64_t, std::function<void(Entity*, Entity*)>> callbacks;
    std::unordered_map<uint64_t, std::function<void(Entity*, Entity*)>> contactEndedCallbacks;
    std::unordered_set<__int128> currentContacts;
    TMXTiledMap *tileMap;
    TMXLayer *meta;
};
