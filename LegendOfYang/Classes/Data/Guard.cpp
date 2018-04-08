#include "Guard.h"

Guard::Guard(int x, int y)
{
    exp = 15;
    gold = 15;
    hp = 40;
    atk = 15;
    def = 20;
    sprite = Sprite::create("guard.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setScale(1.5);
    setPosition(x, y);
    sprite->setPosition(getPosition());
}
