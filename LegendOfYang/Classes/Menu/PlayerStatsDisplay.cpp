//
//  PlayerStatsDisplay.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#include "PlayerStatsDisplay.hpp"

bool PlayerStatsDisplay::init() {
    if (!Node::init()) return false;
    std::vector<LabelAndCallback> items;
    LabelAndCallback item1, item2, item3;
    item1.first = "GPA : 3.30/4.00";
    item2.first = "Major : Computer Science";
    item3.first = "Intelligence : 11";
    item1.second = item2.second = item3.second = [this](Node *sender) { this->removeFromParent(); };
    items = {item1, item2, item3};
    auto menu = KeyboardMenu::create(items);
    addChild(menu);
    return true;
}
