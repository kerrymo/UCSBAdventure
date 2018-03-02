#include "Enemy.h"

Enemy::Enemy(int x, int y)
{
    exp = 6;
    gold = 5;
    hp = 30;
    atk = 20;
    def = 0;
    dead = false;
    sprite = Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    setPosition(x, y);
    sprite->setPosition(getPosition());
}

int Enemy::getExp()
{
    return exp;
}

int Enemy::getGold()
{
    return gold;
}

int Enemy::getHp()
{
    return hp;
}

int Enemy::getAtk()
{
    return atk;
}

int Enemy::getDef()
{
    return def;
}

int Enemy::takeDamage(int rawDamage)
{
    int damage = rawDamage - def;
    if(damage < 0) return 0;
    hp -= damage;
    if(hp <= 0) die();
    return damage;
}

Sprite* Enemy::getSprite() const
{
    return sprite;
}

bool Enemy::isDead()
{
    return dead;
}

void Enemy::die()
{
    sprite->runAction(FadeTo::create(0.25, 0));
    dead = true;
}

Vec2 Enemy::getPosition()
{
    return position;
}

void Enemy::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}
