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

// TODO : Display more stats like experience till the next level

bool PlayerStatsDisplay::init() {
    if (!Node::init()) return false;
    std::vector<LabelAndCallback> items;
    LabelAndCallback item1, item2, item3, item4, item5;
    std::stringstream GPA;
    GPA << std::fixed << std::setprecision(2) << 4*Player::getCurrentHp()/(double)Player::getMaxHp();
    item1.first = "GPA : " + GPA.str() + "/4.00";
    item2.first = "Major : " + Player::lvToString(Player::getLv());
    item3.first = "Intelligence : " + std::to_string(Player::getAtk());
    item4.first = "P/NP Units : " + std::to_string(Player::getDef());
    item5.first = "Gold : " + std::to_string(Player::getGold());
    item1.second = item2.second = item3.second = item4.second = item5.second = [this](Node *sender) { this->removeFromParent(); };
    items = {item1, item2, item3, item4, item5};
    auto menu = KeyboardMenu::create(items);
    addChild(menu);
    return true;
}
