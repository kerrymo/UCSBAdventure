//
//  EntityCreator.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/17/18.
//

#pragma once
#include "Entity.hpp"
#include "YangPhysics.hpp"

const int defaultSize = 32;

class OverworldScene;
class EntityCreator {
public:
    EntityCreator(OverworldScene *s) : scene(s) {};
    
    // Description : All these functions just initialize specific entities.
    Entity* createPlayer();
    Entity* createBasicNPC();
    Entity* createTalkingNPC(std::string message);
    Entity* createBasicEnemy();
    Entity* createFollowingEnemy();
    Entity* createCalpirgEnemy();
    Entity* createLoadingZone(std::string worldFilename);
    
protected:
    void setupAnimation(Entity *entity);
    OverworldScene *scene;
};

