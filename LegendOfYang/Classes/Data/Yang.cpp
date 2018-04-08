#include "Yang.h"

Yang::Yang()
{
    lv = 1;
    exp = 0;
    maxHp = 50;
    currentHp = 50;
    atk = 10;
    def = 30;
    hpGrowth = 12;
    atkGrowth = 3;
    defGrowth = 15;
    defending = false;
    dead = false;
}

void Yang::createSprite(int x, int y)
{
    sprite = Sprite::create("player_up.png");
    sprite->setScale(5);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(x, y);
}

