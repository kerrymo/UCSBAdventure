#pragma once

#include "cocos2d.h"

USING_NS_CC;
#include "Item.hpp"
#include <unordered_map>

class Player
{
public:
    Player();
    
    /**
     The getter of lv.
     Return: the lv variable.
    */
    int getLv();
    
    /**
     Level to string.
     Return: gives level as string
     */
    std::string lvToString(int lvl);
    
    /**
     The getter of exp.
     Return: the exp variable.
    */
    int getExp();
    
    /**
     The getter of maxHp.
     Return: the maxHp variable.
    */
    int getMaxHp();
    
    /**
     The getter of currentHp.
     Return: the currentHp variable.
    */
    int getCurrentHp();
    
    void setCurrentHp(int hp);
    /**
     The getter of atk.
     Return: the atk variable.
    */
    int getAtk();
    
    /**
     The getter of def.
     Return: the def variable.
    */
    int getDef();
    
    /**
     Called when the player takes damage.
     Parameters: the raw damage taken.
     Return: the real damage taken.
     Precondition: the player is attacked.
     Postcondition: the hp is reduced by the damage taken.
    */
    int takeDamage(int);
    
    /**
     Called when the player gains exp.
     Parameters: the amount of exp gained.
     Precondition: the player gains exp.
     Postcondition: the exp is added to the player's exp.
    */
    void gainExp(int);
    
    /**
     Called when the player choose to defend himself.
     Postcondition: the defending flag is set.
    */
    void defend();
    
    /**
     Called when a new round begins.
     Postcondition: the defending flag is set to false.
    */
    void undefend();
    
    virtual std::string getName() = 0;
    
    virtual void createSprite(int, int);
    
    Sprite* getSprite();
    
    Label* getHpLabel();
    
    void createHpLabel(int, int);
    
    bool isDead();
    
    void die();
    
    void updateHpLabel();
    
protected:
    int lv, exp, maxHp, currentHp, atk, def, hpGrowth, atkGrowth, defGrowth;
    bool defending, dead;
    Sprite *sprite;
    Label *hpLabel;
};
