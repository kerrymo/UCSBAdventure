#include "Party.h"

Player* Party::player[3];
int Party::gold = 0;
std::unordered_map<Item*, int> Party::items;

Party::Party()
{
    player[0] = new Yang();
    player[1] = new Locke();
    player[2] = new Terra();
}

Player* Party::getPlayer(int num)
{
    return player[num];
}

std::vector<Player*> Party::getPlayers() {
    return std::vector<Player*>(player, player + sizeof(player) / sizeof(player[0]));
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

void Party::setGold(int g) {
    gold = std::max(0, g);
    EventCustom event("inventory-changed");
    Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
};


void Party::gainGold(int gainedGold)
{
    setGold(gold + gainedGold);
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
