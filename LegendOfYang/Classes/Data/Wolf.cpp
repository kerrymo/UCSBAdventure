#include "Wolf.h"

Wolf::Wolf(int x, int y)
{
    exp = 10;
    gold = 20;
    hp = 30;
    atk = 20;
    def = 15;
    sprite = Sprite::create("wolf.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setScale(1.5);
    setPosition(x, y);
    sprite->setPosition(getPosition());
}

