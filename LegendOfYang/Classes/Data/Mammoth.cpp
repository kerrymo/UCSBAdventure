#include "Mammoth.h"

Mammoth::Mammoth(int x, int y)
{
    exp = 20;
    gold = 10;
    hp = 50;
    atk = 10;
    def = 25;
    sprite = Sprite::create("mammoth.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setScale(1.5);
    setPosition(x, y);
    sprite->setPosition(getPosition());
}

