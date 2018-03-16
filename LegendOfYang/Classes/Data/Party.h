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
    /**
     The default constructor.
     Postcondition: a new object is created.
    */
    Party();
    
    /**
     The getter of the specified player.
     Parameter: the position of the player in the array.
     Return: the pointer of the player.
    */
    static Player* getPlayer(int);
    
    /**
     The getter of the players vector.
     Return: the players vector.
    */
    static std::vector<Player*> getPlayers();
    
    /**
     The getter of fallen flag.
     Return: the fallen boolean.
    */
    static bool fallen();
    
    /**
     The getter of the first living player.
     Return: the position of the first living player in the array.
    */
    static int getFirstLivingPlayer();
    
    /**
     The getter of the number of living players in the party.
     Return: the number of living players in the party.
    */
    static int getNumOfLivingPlayer();
    
    /**
     The getter of gold.
     Return: the gold variable.
     */
    static int getGold();
    
    /**
     The setter of the gold variable.
     Parameters: the new value of gold.
     Postcondition: the gold variable is set to the new value.
    */
    static void setGold(int g);
    
    /**
     Called when the player gains gold.
     Parameters: the amount of gold gained.
     Precondition: the player gains gold.
     Postcondition: the gold is added to the player's gold.
     */
    static void gainGold(int);
    
    /**
     The getter of items.
     Return: the items vector.
    */
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
