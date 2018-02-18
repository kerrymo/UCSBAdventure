#include "Enemy.h"

Enemy::Enemy()
{
    exp = 4;
    gold = 5;
    hp = 30;
    atk = 2;
    def = 0;
    dead = false;
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
    return damage;
}

Sprite* Enemy::getSprite() const
{
    return sprite;
}

void Enemy::createSprite()
{
    sprite = Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
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
