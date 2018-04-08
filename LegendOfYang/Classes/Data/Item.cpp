//
//  Item.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#include "Item.hpp"
#include "PagedTextBox.hpp"
#include "OverworldScene.hpp"

std::unordered_map<std::string, Item*> *Item::items = nullptr;

Item* Item::itemFromName(std::string itemName) {
    return items->at(itemName);
}

LabelAndCallback Item::infoItem() {
    LabelAndCallback item;
    item.first = "Info";
    item.second = [this](Node *sender) {
        auto overworld = dynamic_cast<OverworldScene*>(Director::getInstance()->getRunningScene());
        if (overworld) {
            overworld->gui->addChild(PagedTextBox::create(info));
        }
    };
    
    return item;
}

LabelAndCallback Item::closeItem() {
    return KeyboardMenu::closeItem();
}
