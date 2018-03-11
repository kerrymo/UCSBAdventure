#pragma once

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;


class Locke : public Player
{
public:
    Locke();
    void createSprite(int x, int y);
    virtual std::string getName() { return "Locke"; };
};

