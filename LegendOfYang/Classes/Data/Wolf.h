#pragma once

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

class Wolf : public Enemy
{
public:
    /**
     The constructor of the class.
     Parameters: the position of the sprite of the enemy.
     Postcondition: a new object is created.
     */
    Wolf(int, int);
};

