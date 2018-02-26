//
//  Inventory.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#include "Inventory.hpp"
#include "Player.h"

bool Inventory::init() {
    if (!Node::init()) return false;
    auto inventoryListener = EventListenerCustom::create("inventory-changed", [this](EventCustom *event) { update(); });
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(inventoryListener, this);
    menu = KeyboardMenu::create();
    this->addChild(menu);
    update();
    return true;
}

void Inventory::update() {
    std::vector<LabelAndCallback> items;
    for (auto itemAndQuantity : Player::getItems()) {
        LabelAndCallback menuItem;
        menuItem.first = itemAndQuantity.first->getName() + " : " + std::to_string(itemAndQuantity.second);
        menuItem.second = [this, itemAndQuantity](Node *sender) { this->addChild(itemAndQuantity.first->getMenu()); };
        items.push_back(menuItem);
    }
    
    LabelAndCallback closeItem;
    closeItem.first = "Close";
    closeItem.second = [this](Node *sender) { this->removeFromParent(); };
    items.push_back(closeItem);
    menu->setItems(items);
}
