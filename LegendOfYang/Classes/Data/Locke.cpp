#include "Locke.h"

Locke::Locke()
{
    lv = 1;
    exp = 0;
    maxHp = 45;
    currentHp = 45;
    atk = 15;
    def = 25;
    hpGrowth = 10;
    atkGrowth = 5;
    defGrowth = 10;
    defending = false;
    dead = false;
}

void Locke::createSprite(int x, int y)
{
    sprite = Sprite::create("Locke.png");
    sprite->setScale(2);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(x, y);
}
