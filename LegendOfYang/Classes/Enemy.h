#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy
{
public:
    Enemy();
    int getExp();
    int getGold();
    int getHp();
    int getAtk();
    int getDef();
    Sprite* getSprite() const;
    Vec2 getPosition();
    void setPosition(int, int);
    int takeDamage(int);
    void createSprite();
    bool isDead();
    void die();
    
private:
    int exp, gold, hp, atk, def;
    bool dead;
    Sprite *sprite;
    Vec2 position;
};
