//
//  Consumable.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#include "Consumable.hpp"
#include "Player.h"

Consumable *Consumable::caffinePills = new Consumable("Caffine Pills", "For lazy college students. (Fully heals you)", []() { Party::getPlayer(0)->setCurrentHp(Party::getPlayer(0)->getMaxHp()); });
Consumable *Consumable::degreePetition = new Consumable("Change of Major Form", "Your parents were tired of hearing you were undeclared so you grabbed one of these. (Increases XP by 20)", []() { Party::getPlayer(0)->gainExp(20); });

KeyboardMenu* Consumable::getMenu() {
    LabelAndCallback actionItem;
    actionItem.first = "Use";
    actionItem.second = [this](Node *sender) {
        action();
        Party::removeItem(this);
        sender->removeFromParent();
        
    };
    
    return KeyboardMenu::create({actionItem, infoItem(), closeItem()});
}
