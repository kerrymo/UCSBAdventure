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

Entity* createPlayer(YangPhysics *physics);
Entity* createBasicNPC();
Entity* createTalkingNPC(Node *gui, std::string message);
Entity* createBasicEnemy(YangPhysics *physics, Entity *player);
Entity* createFollowingEnemy(YangPhysics *physics, Entity *player);
Entity* createCalpirgEnemy(YangPhysics *physics, Entity *player, Node *gui);
