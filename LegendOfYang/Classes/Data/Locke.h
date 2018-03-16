#pragma once

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;


class Locke : public Player
{
public:
    /**
     The default constructor.
     Post condition: a new object is created.
     */
    Locke();
    
    /**
     Create the sprite for the player.
     Parameters: the position of the sprite.
     Precondition: the sprite is not created.
     Postcondition: the sprite is created.
     */
    void createSprite(int x, int y);
    
    /**
     Get the name of the player.
     Return: the name of the player.
     */
    virtual std::string getName() { return "Locke"; };
};

