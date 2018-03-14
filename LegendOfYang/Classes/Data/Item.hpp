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
    /**
     Initializes an item with name and description
     */
    Item(std::string name = "Item", std::string info = "Hopefully does something useful") : name(name), info(info) {
        if (items == nullptr) {
            items = new std::unordered_map<std::string, Item*>();
        }
        (*items)[name] = this;
    };
    
    /**
     Returns a menu that takes input and displays all the actions that can be performed with the item
     */
    virtual KeyboardMenu* getMenu() = 0;
    
    /**
     Returns the name of the item
     */
    std::string getName() { return name; };
    
    /**
     Returns an item reference given the name of the item
     Precondition: Don't call this when initializing a static member.
     */
    static Item* itemFromName(std::string itemName);
protected:
    LabelAndCallback infoItem();
    LabelAndCallback closeItem();
    std::string name;
    std::string info;
private:
    static std::unordered_map<std::string, Item*> *items;
};
