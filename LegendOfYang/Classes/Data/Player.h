#pragma once

#include "cocos2d.h"

USING_NS_CC;
#include "Item.hpp"
#include <unordered_map>

class Player
{
public:
    /**
     The getter of lv.
     Return: the lv variable.
    */
    static int getLv();
    
    /**
     Level to string.
     Return: gives level as string
     */
    static std::string lvToString(int lvl);
    
    /**
     The getter of exp.
     Return: the exp variable.
    */
    static int getExp();
    
    /**
     The getter of gold.
     Return: the gold variable.
    */
    static int getGold();
    
    static void setGold(int g) { gold = std::max(0, g); };
    
    /**
     The getter of maxHp.
     Return: the maxHp variable.
    */
    static int getMaxHp();
    
    /**
     The getter of currentHp.
     Return: the currentHp variable.
    */
    static int getCurrentHp();
    static void setCurrentHp(int hp);
    /**
     The getter of atk.
     Return: the atk variable.
    */
    static int getAtk();
    
    /**
     The getter of def.
     Return: the def variable.
    */
    static int getDef();
    
    /**
     Called when the player takes damage.
     Parameters: the raw damage taken.
     Return: the real damage taken.
     Precondition: the player is attacked.
     Postcondition: the hp is reduced by the damage taken.
    */
    static int takeDamage(int);
    
    /**
     Called when the player gains exp.
     Parameters: the amount of exp gained.
     Precondition: the player gains exp.
     Postcondition: the exp is added to the player's exp.
    */
    static void gainExp(int);
    
    /**
     Called when the player gains gold.
     Parameters: the amount of gold gained.
     Precondition: the player gains gold.
     Postcondition: the gold is added to the player's gold.
    */
    static void gainGold(int);
    
    /**
     Called when the player choose to defend himself.
     Postcondition: the defending flag is set.
    */
    static void defend();
    
    /**
     Called when a new round begins.
     Postcondition: the defending flag is set to false.
    */
    static void undefend();
    
    /**
     Adds an item to the players inventory
     */
    static void addItem(Item *item);
    
    /**
     Removes an item from the players inventory
     */
    static void removeItem(Item *item);
    
    static std::unordered_map<Item*, int> getItems() { return items; };
    
private:
    static int lv, exp, gold, maxHp, currentHp, atk, def;
    static bool defending;
    static std::unordered_map<Item*, int> items;
};
