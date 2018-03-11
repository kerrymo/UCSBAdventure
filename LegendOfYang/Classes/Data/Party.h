#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "Locke.h"
#include "Terra.h"
#include "Yang.h"

USING_NS_CC;

class Party
{
public:
    Party();
    
    static Player* getPlayer(int);
    
    static std::vector<Player*> getPlayers();
    
    static bool fallen();
    
    static int getFirstLivingPlayer();
    
    static int getNumOfLivingPlayer();
    
    /**
     The getter of gold.
     Return: the gold variable.
     */
    static int getGold();
    
    static void setGold(int g);
    
    /**
     Called when the player gains gold.
     Parameters: the amount of gold gained.
     Precondition: the player gains gold.
     Postcondition: the gold is added to the player's gold.
     */
    static void gainGold(int);
    
    static std::unordered_map<Item*, int> getItems() { return items; };
    
    /**
     Adds an item to the players inventory
     */
    static void addItem(Item *item);
    
    /**
     Removes an item from the players inventory
     */
    static void removeItem(Item *item);
    
private:
    static Player *player[3];
    static int gold;
    static std::unordered_map<Item*, int> items;
};
