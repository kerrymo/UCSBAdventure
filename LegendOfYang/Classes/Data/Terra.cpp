#include "Terra.h"

Terra::Terra()
{
    lv = 1;
    exp = 0;
    maxHp = 40;
    currentHp = 40;
    atk = 20;
    def = 20;
    hpGrowth = 8;
    atkGrowth = 7;
    defGrowth = 5;
    defending = false;
    dead = false;
}

void Terra::createSprite(int x, int y)
{
    sprite = Sprite::create("Terra.png");
    sprite->setScale(2);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(x, y);
}
