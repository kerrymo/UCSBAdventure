//
//  EntityCreator.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/17/18.
//

#pragma once
#include "Entity.hpp"
#include "YangPhysics.hpp"
#include "Item.hpp"
#include "Party.h"
#include "SimpleAudioEngine.h"

const int defaultSize = 32;

class OverworldScene;
class TextBox;
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
    Entity* createLoadingZone(std::string worldFilename, std::string entranceName);
    Entity* createStoreNPC(std::vector<std::pair<Item*, int>> itemsAndPrices);
    Entity* createChest(Item *item, int tag);
    Entity* createBoss();
    
protected:
    std::string uniqueKey(int tag, std::string valueName);
    void setupAnimation(Entity *entity);
    TextBox* createGoldDisplay();
    OverworldScene *scene;
};

