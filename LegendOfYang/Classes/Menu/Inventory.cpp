//
//  Inventory.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/10/18.
//

#include "Inventory.hpp"

bool Inventory::init() {
    if (!Node::init()) return false;
    std::vector<LabelAndCallback> items;
    LabelAndCallback item1, item2, item3;
    item1.first = "Baseball Bat";
    item2.first = "Bottle Rocket";
    item3.first = "back";
    item1.second = item2.second = CC_CALLBACK_1(Inventory::selectItem, this);
    item3.second = CC_CALLBACK_1(Inventory::close, this);
    items = {item1, item2, item3};
    auto menu = KeyboardMenu::create(items);
    addChild(menu);
    return true;
}

void Inventory::selectItem(Node *sender) {
    // TODO :: Add an item class that implements a function that presents a menu for what you can do with an item
    // So it would look like gui.addChild(item.getMenu())
    // Some options the menu would present could be...
    // equipable item - presents a menu with equip and maybe something like info
    // consumable item - presents a menu with eat
    // All items - A throw away and back button to close the menu
    // Tips : There are two ways to approach this
    // Standard OOP way : inheritence with a base item class and two subclasses consumableItem and equipableItem
    // Better way : using factory methods
    
    auto keyboardMenu = (KeyboardMenu*)sender;
    auto message = { "You selected the " + keyboardMenu->selectedLabelText() };
    auto textBox = PagedTextBox::create(message);
    addChild(textBox);
}

void Inventory::close(Node *sender) {
    this->removeFromParent();
}
