#include "Player.h"

int Player::lv = 1;
int Player::exp = 0;
int Player::gold = 0;
int Player::maxHp = 60;
int Player::currentHp = 60;
int Player::atk = 10;
int Player::def = 0;
bool Player::defending = false;

int Player::getLv()
{
    return lv;
}

int Player::getExp()
{
    return exp;
}

int Player::getGold()
{
    return gold;
}

int Player::getMaxHp()
{
    return maxHp;
}

int Player::getCurrentHp()
{
    return currentHp;
}

int Player::getAtk()
{
    return atk;
}

int Player::getDef()
{
    return def;
}

int Player::takeDamage(int rawDamage)
{
    int damage = rawDamage - def;
    if(damage < 0) return 0;
    if(defending) damage /= 2;
    currentHp -= damage;
    if(currentHp < 0) currentHp = 0;
    return damage;
}

void Player::gainExp(int gainedExp)
{
    exp += gainedExp;
    while(exp >= 10 * lv)
    {
        exp -= 10 * lv;
        lv++;
        maxHp += 10;
        currentHp = maxHp;
        atk += 10;
        def += 10;
    }
}

void Player::gainGold(int gainedGold)
{
    gold += gainedGold;
}

void Player::defend()
{
    defending = true;
}

void Player::undefend()
{
    defending = false;
}
