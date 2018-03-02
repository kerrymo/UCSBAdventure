#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy
{
public:
    /**
     The default constructor.
     Postcondition: a new object is created.
    */
    Enemy(int, int);
    
    /**
     The getter of exp.
     Return: the exp variable.
    */
    int getExp();
    
    /**
     The getter of gold.
     Return: the gold variable.
    */
    int getGold();
    
    /**
     The getter of hp.
     Return: the hp variable.
    */
    int getHp();
    
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
     The getter of sprite pointer.
     Return: the sprite pointer.
    */
    Sprite* getSprite() const;
    
    /**
     The getter of position.
     Return: the position variable.
    */
    Vec2 getPosition();
    
    /**
     The setter of position.
     Parameters: the x and y values of the new position.
     Postcondition: the position variable is set to the new position.
    */
    void setPosition(int, int);
    
    /**
     Called when the enemy takes damage.
     Parameters: the raw damage taken.
     Return: the real damage taken.
     Precondition: the enemy is attacked.
     Postcondition: the hp is reduced by the damage taken.
    */
    int takeDamage(int);
    
    /**
     Check if the enemy is dead.
     Return: the dead flag.
    */
    bool isDead();
    
    /**
     Called when the enemy is killed.
     Precondition: the enemy is killed.
     Postcondition: the animation is played and dead is set to true.
    */
    void die();
    
private:
    int exp, gold, hp, atk, def;
    bool dead;
    Sprite *sprite;
    Vec2 position;
};
