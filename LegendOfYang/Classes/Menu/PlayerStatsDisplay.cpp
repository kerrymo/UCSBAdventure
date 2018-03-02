//
//  PlayerStatsDisplay.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#include "PlayerStatsDisplay.hpp"
#include "Player.h"
#include <iomanip> // setprecision
#include <sstream> // stringstream

bool PlayerStatsDisplay::init() {
    if (!Node::init()) return false;
    std::vector<LabelAndCallback> items;
    LabelAndCallback item1, item2, item3, item4, item5;
    std::stringstream GPA;
    GPA << std::fixed << std::setprecision(2) << 4*Party::getPlayer(0)->getCurrentHp()/(double)Party::getPlayer(0)->getMaxHp();
    item1.first = "GPA : " + GPA.str() + "/4.00";
    item2.first = "Major : " + Party::getPlayer(0)->lvToString(Party::getPlayer(0)->getLv());
    item3.first = "Intelligence : " + std::to_string(Party::getPlayer(0)->getAtk());
    item4.first = "P/NP Units : " + std::to_string(Party::getPlayer(0)->getDef());
    item5.first = "Gold : " + std::to_string(Party::getGold());
    item1.second = item2.second = item3.second = item4.second = item5.second = [this](Node *sender) { this->removeFromParent(); };
    items = {item1, item2, item3, item4, item5};
    auto menu = KeyboardMenu::create(items);
    addChild(menu);
    return true;
}
