//
//  Consumable.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/24/18.
//

#include "Consumable.hpp"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include "OverworldScene.hpp"

Consumable *Consumable::caffinePills = new Consumable("Caffine Pills", "For lazy college students. (Fully heals one party member)", createPartyAction([](Player *p) { p->setCurrentHp(p->getMaxHp()); }));
                                                      
Consumable *Consumable::degreePetition = new Consumable("Change of Major Form", "Your parents were tired of hearing you were undeclared so you grabbed one of these. (Increases XP by 20 for one party member)", createPartyAction([](Player *p) { p->gainExp(20); }));

Consumable *Consumable::communityCollegeCredits = new Consumable("Community College Transfer Credits", "Nothing is easier than getting an A when half your classmates have second jobs. (Increases XP by 30 for party)", createSingleUseAction([]() {
    for(auto player : Party::getPlayers())
        player->gainExp(30);
}));

/*Consumable *Consumable:: = new Consumable("Change of Major Form", "Your parents were tired of hearing you were undeclared so you grabbed one of these. (Increases XP by 20 for one party member)", createSingleUseAction([]() {
for(auto player : Party::getPlayers())
    player->setCurrentHp(player->getMaxHp());
}));*/
                                                        
KeyboardMenu* Consumable::getMenu() {
    LabelAndCallback actionItem;
    actionItem.first = "Use";
    actionItem.second = [this](Node *sender) {
        action(sender, this);
    };
    
    return KeyboardMenu::create({actionItem, infoItem(), closeItem()});
}

std::function<void(Node*,Consumable*)> Consumable::createSingleUseAction(std::function<void()> action) {
    return [action](Node *sender, Consumable *item) {
        action();
        Party::removeItem(item);
        sender->removeFromParent();
        
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect("equip.wav");
    };
}
                                                      
std::function<void(Node*, Consumable*)> Consumable::createPartyAction(std::function<void(Player*)> playerAction) {
    return [playerAction](Node *sender, Consumable *item) {
        auto itemMenu = sender;
        std::vector<LabelAndCallback> characterItems;
        for (auto player : Party::getPlayers()) {
            characterItems.push_back({player->getName(), [player, playerAction, item, itemMenu](Node* sender) {
                playerAction(player);
                Party::removeItem(item);
                sender->removeFromParent();
                itemMenu->removeFromParent();
                
                auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
                audio->playEffect("equip.wav");
            }});
        }
        characterItems.push_back(KeyboardMenu::closeItem());
        
        // Prepare Menu
        auto characterActionMenu = KeyboardMenu::create(characterItems);
        characterActionMenu->setPosition(sender->convertToWorldSpace(-sender->getAnchorPointInPoints()) + Vec2(sender->getContentSize().width, 0));
        
        auto overworld = dynamic_cast<OverworldScene*>(Director::getInstance()->getRunningScene());
        if (overworld) {
            overworld->gui->addChild(characterActionMenu);
        }
    };
}
