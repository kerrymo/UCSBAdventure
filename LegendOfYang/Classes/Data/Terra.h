#pragma once

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;


class Terra : public Player
{
public:
    Terra();
    void createSprite(int x, int y);
};


