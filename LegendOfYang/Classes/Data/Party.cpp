#include "Party.h"

Player* Party::player[3];
int Party::gold = 0;
std::unordered_map<Item*, int> Party::items;

Party::Party()
{
    for(int n = 0; n < 3; n++)
        player[n] = new Player();
}

Player* Party::getPlayer(int num)
{
    return player[num];
}

bool Party::fallen()
{
    bool temp = true;
    for(int n = 0; n < 3; n++)
        if(!player[n]->isDead()) temp = false;
    return temp;
}

int Party::getFirstLivingPlayer()
{
    if(!player[0]->isDead()) return 0;
    else if(!player[1]->isDead()) return 1;
    else return 2;
}

int Party::getNumOfLivingPlayer()
{
    int n = 0;
    for(int i = 0; i < 3; i++)
        if(!player[i]->isDead()) n++;
    return n;
}

int Party::getGold()
{
    return gold;
}

void Party::gainGold(int gainedGold)
{
    gold += gainedGold;
}

void Party::addItem(Item *item)
{
    items[item]++;
    EventCustom event("inventory-changed");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

void Party::removeItem(Item *item)
{
    items[item]--;
    if (items[item] <= 0) {
        items.erase(item);
    }
    EventCustom event("inventory-changed");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}
