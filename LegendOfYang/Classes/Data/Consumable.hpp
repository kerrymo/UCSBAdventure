//
//  Consumable.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#pragma once
#include "Item.hpp"
#include "Party.h"

class Consumable : public Item {
public:
    Consumable(std::string name, std::string info, std::function<void(Node*, Consumable*)> action) : Item(name, info), action(action) {};
    virtual KeyboardMenu* getMenu();
    
    static Consumable *caffinePills;
    static Consumable *degreePetition;
    static Consumable *communityCollegeCredits;
    
protected:
    static std::function<void(Node*, Consumable*)> createSingleUseAction(std::function<void()> action);
    static std::function<void(Node*, Consumable*)> createPartyAction(std::function<void(Player*)> playerAction);
    std::function<void(Node*, Consumable*)> action;
};
