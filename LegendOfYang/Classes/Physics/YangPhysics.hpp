//
//  YangPhysics.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#pragma once
#include "Entity.hpp"
#include "Utility.hpp"
USING_NS_CC;

class YangPhysics : public Node {
public:
    CREATE_FUNC(YangPhysics);
    virtual bool init() override;
    static YangPhysics* createWithTileMap(TMXTiledMap *map);
    
    Vector<Entity*> getCollidingEntities(Rect aabb); // Used for interaction
    void registerCallbackOnContact(std::function<void(Entity*, Entity*)> callback, Entity *node);
    void update(float delta) override;
    
protected:
    static void coalesceAABB();
    Vector<Entity*> entities; // Things that move / Objects in the world
    TMXTiledMap *tileMap;
    TMXLayer *meta;
};
