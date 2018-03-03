//
//  Item.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#pragma once
#include "KeyboardMenu.hpp"
#include <unordered_map>

// TODO : Create a weapon class that inherits from Item

class Item {
public:
    Item(std::string name = "Item", std::string info = "Hopefully does something useful") : name(name), info(info) {
        if (items == nullptr) {
            items = new std::unordered_map<std::string, Item*>();
        }
        (*items)[name] = this;
    };
    virtual KeyboardMenu* getMenu() = 0;
    std::string getName() { return name; };
    static Item* itemFromName(std::string itemName);
protected:
    LabelAndCallback infoItem();
    LabelAndCallback closeItem();
    std::string name;
    std::string info;
private:
    static std::unordered_map<std::string, Item*> *items;
};
