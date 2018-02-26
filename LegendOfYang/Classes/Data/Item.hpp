//
//  Item.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#pragma once
#include "KeyboardMenu.hpp"

class Item {
public:
    Item(std::string name = "Item", std::string info = "Hopefully does something useful") : name(name), info(info) {};
    virtual KeyboardMenu* getMenu() = 0;
    std::string getName() { return name; };
protected:
    LabelAndCallback infoItem();
    LabelAndCallback closeItem();
    std::string name;
    std::string info;
};
