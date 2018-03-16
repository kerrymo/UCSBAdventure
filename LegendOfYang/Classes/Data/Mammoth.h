#pragma once

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

class Mammoth : public Enemy
{
public:
    /**
     The constructor of the class.
     Parameters: the position of the sprite of the enemy.
     Postcondition: a new object is created.
     */
    Mammoth(int, int);
};
