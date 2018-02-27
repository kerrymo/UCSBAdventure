//
//  Consumable.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#pragma once
#include "Item.hpp"

class Consumable : public Item {
public:
    Consumable(std::string name, std::string info, std::function<void()> action) : Item(name, info), action(action) {};
    virtual KeyboardMenu* getMenu();
    
    static Consumable *caffinePills;
    static Consumable *degreePetition;
protected:
    std::function<void()> action;
};
