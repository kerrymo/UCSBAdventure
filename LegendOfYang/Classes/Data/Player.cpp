#include "Player.h"

Player::Player()
{
    lv = 1;
    exp = 0;
    maxHp = 60;
    currentHp = 60;
    atk = 10;
    def = 0;
    hpGrowth = 10;
    atkGrowth = 10;
    defGrowth = 10;
    defending = false;
    dead = false;
}

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
    int damage = rawDamage * 100 / (def + 100);
    if(damage < 0) return 0;
    if(defending) damage /= 2;
    currentHp -= damage;
    if(currentHp < 0) currentHp = 0;
    return damage;
}

void Player::gainExp(int gainedExp)
{
    exp += gainedExp;
    while(exp >= 25 * lv)
    {
        exp -= 25 * lv;
        lv++;
        maxHp += hpGrowth;
        currentHp = maxHp;
        atk += atkGrowth;
        def += defGrowth;
    }
}

void Player::defend()
{
    defending = true;
}

void Player::undefend()
{
    defending = false;
}

void Player::createSprite(int x, int y)
{
    sprite = Sprite::create("player_up.png");
    sprite->setScale(5);
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(x, y);
}

Sprite* Player::getSprite()
{
    return sprite;
}

Label* Player::getHpLabel()
{
    return hpLabel;
}

void Player::createHpLabel(int x, int y)
{
    hpLabel = Label::createWithSystemFont("HP " + std::to_string(currentHp) + "/" + std::to_string(maxHp), "Arial", 25);
    hpLabel->setPosition(x, y);
}

bool Player::isDead()
{
    return dead;
}

void Player::die()
{
    sprite->runAction(FadeTo::create(0.25, 0));
    dead = true;
}

void Player::updateHpLabel()
{
    hpLabel->setString("HP " + std::to_string(currentHp) + "/" + std::to_string(maxHp));
}
