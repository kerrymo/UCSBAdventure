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
    LabelAndCallback item1, item2, item3, item4;
    std::stringstream GPA;
    GPA << std::fixed << std::setprecision(2) << 4*Player::getCurrentHp()/(double)Player::getMaxHp();
    item1.first = "GPA : " + GPA.str() + "/4.00";
    item2.first = "Major : " + Player::lvToString(Player::getLv());
    item3.first = "Intelligence : " + std::to_string(Player::getAtk());
    item4.first = "P/NP Units : " + std::to_string(Player::getDef());
    item1.second = item2.second = item3.second = item4.second = [this](Node *sender) { this->removeFromParent(); };
    items = {item1, item2, item3, item4};
    auto menu = KeyboardMenu::create(items);
    addChild(menu);
    return true;
}
