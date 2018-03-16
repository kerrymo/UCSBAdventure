#pragma once

#include "cocos2d.h"

USING_NS_CC;
#include "Item.hpp"
#include <unordered_map>

class Player
{
public:
    /**
     The default constructor.
     Postcondition: a new object is created.
    */
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
    
    /**
     The setter of currentHp.
     Parameters: the new value of currentHp.
     Postcondition: the currentHp has been set to the new value.
    */
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
    
    /**
     Create the sprite for the player.
     Parameters: the position of the sprite.
     Precondition: the sprite is not created.
     Postcondition: the sprite is created.
    */
    virtual void createSprite(int, int);
    
    /**
     The getter of sprite.
     Return: the sprite pointer.
    */
    Sprite* getSprite();
    
    /**
     The getter of hpLabel.
     Return: the hpLabel pointer.
    */
    Label* getHpLabel();
    
    /**
     Create the hp label for the player.
     Parameters: the position of the label.
     Precondition: the label is not created.
     Postcondition: the label is created.
    */
    void createHpLabel(int, int);
    
    /**
     The getter of dead flag.
     Return: the dead boolean.
    */
    bool isDead();
    
    /**
     Called when the player dies.
     Precondition: the player is not dead.
     Postcondition: the player is dead.
    */
    void die();
    
    /**
     Called when the hp of the player changes.
     Postcondition: the hp label of the player is updated.
    */
    void updateHpLabel();
    
protected:
    int lv, exp, maxHp, currentHp, atk, def, hpGrowth, atkGrowth, defGrowth;
    bool defending, dead;
    Sprite *sprite;
    Label *hpLabel;
};
