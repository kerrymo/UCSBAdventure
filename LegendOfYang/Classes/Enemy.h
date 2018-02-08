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
    int takeDamage(int);
    
private:
    int exp, gold, hp, atk, def;
};
