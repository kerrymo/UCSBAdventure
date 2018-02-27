#include "Player.h"

int Player::lv = 1;
int Player::exp = 0;
int Player::gold = 0;
int Player::maxHp = 60;
int Player::currentHp = 60;
int Player::atk = 10;
int Player::def = 0;
bool Player::defending = false;
std::unordered_map<Item*, int> Player::items;

int Player::getLv()
{
    return lv;
}

std::string Player::lvToString(int lvl)
{
    std::string names[6] = {"Psychology Major", "Premed", "Chemistry", "Statistics Major", "Mech E. Major", "Computer Science"};
    if (lvl-1 < 6) {
        return names[lvl-1];
    } else {
        return names[5];
    }
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

void Player::setCurrentHp(int hp) {
    currentHp = std::max(std::min(hp, maxHp), 0);
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

void Player::addItem(Item *item)
{
    items[item]++;
    EventCustom event("inventory-changed");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void Player::removeItem(Item *item)
{
    items[item]--;
    if (items[item] <= 0) {
        items.erase(item);
    }
    EventCustom event("inventory-changed");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
