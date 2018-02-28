//
//  Consumable.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#include "Consumable.hpp"
#include "Player.h"

// TODO : Add some more consumable items

Consumable *Consumable::caffinePills = new Consumable("Caffine Pills", "For lazy college students. (Fully heals you)", []() { Player::setCurrentHp(Player::getMaxHp()); });
Consumable *Consumable::degreePetition = new Consumable("Change of Major Form", "Your parents were tired of hearing you were undeclared so you grabbed one of these. (Increases XP by 20)", []() { Player::gainExp(20); });

KeyboardMenu* Consumable::getMenu() {
    LabelAndCallback actionItem;
    actionItem.first = "Use";
    actionItem.second = [this](Node *sender) {
        action();
        Player::removeItem(this);
        sender->removeFromParent();
        
    };
    
    return KeyboardMenu::create({actionItem, infoItem(), closeItem()});
}
