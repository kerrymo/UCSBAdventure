#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Player
{
public:
    static int getLv();
    static int getExp();
    static int getGold();
    static int getMaxHp();
    static int getCurrentHp();
    static int getAtk();
    static int getDef();
    static int takeDamage(int);
    static void gainExp(int);
    static void gainGold(int);
    static void defend();
    static void undefend();
    
private:
    static int lv, exp, gold, maxHp, currentHp, atk, def;
    static bool defending;
};
