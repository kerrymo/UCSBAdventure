#include "Enemy.h"

Enemy::Enemy()
{
    exp = 10;
    gold = 10;
    hp = 30;
    atk = 20;
    def = 0;
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
