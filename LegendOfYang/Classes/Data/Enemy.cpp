#include "Enemy.h"

Enemy::Enemy()
{
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
    int damage = rawDamage * (255 - def) / 256 + 1;
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("die.wav");
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
