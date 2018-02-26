//
//  Consumable.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#include "Consumable.hpp"
#include "Player.h"

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
