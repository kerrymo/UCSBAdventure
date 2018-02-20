//
//  EntityCreator.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/17/18.
//

#include "EntityCreator.hpp"
#include "PagedTextBox.hpp"
#include "TextBox.hpp"
#include "KeyboardMenu.hpp"
#include "Battle.h"

Entity* createPlayer(YangPhysics *physics) {
    // Add player
    auto player = Entity::create("CloseNormal.png");
    player->setName("player");
    player->setContentSize(Size(defaultSize, defaultSize));
    player->isDynamic = true;
    
    
    // Add interaction zone to player
    auto interactionBox = Entity::create();
    interactionBox->setContentSize(Size(16.0f, 16.0f));
    interactionBox->setAnchorPoint(Vec2::ZERO);
    interactionBox->isSolid = false;
    interactionBox->isDynamic = false;
    auto interactionKeyboardListener = EventListenerKeyboard::create();
    interactionKeyboardListener->onKeyPressed = [interactionBox, physics, player](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
            auto boundingBox = interactionBox->getCollisionBox();
            boundingBox.origin += defaultSize * player->getOrientation() + (player->getContentSize() - interactionBox->getContentSize())/2.0f;
            auto potentialInteracters = physics->getCollidingEntities(boundingBox);
            for (auto potentialInteracter : potentialInteracters) {
                if (potentialInteracter->interact != nullptr) {
                    potentialInteracter->interact();
                    potentialInteracter->setOrientation(player->getBoundingBox().origin - potentialInteracter->getBoundingBox().origin);
                    break; // So you only interact with one thing at a time
                }
            }
        }
    };
    
    player->getEventDispatcher()->addEventListenerWithSceneGraphPriority(interactionKeyboardListener, interactionBox);
    player->addChild(interactionBox);
    
    return player;
}


Entity* createBasicEnemy(YangPhysics *physics, Entity *player) {
    auto enemy = Entity::create("CloseNormal.png");
    enemy->setContentSize(Size(defaultSize, defaultSize));
    
    physics->registerCallbackOnContact([player](Node *enemy, Node *otherEntity) {
        if (player == otherEntity) {
            enemy->removeFromParent();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, Battle::createScene(), Color3B(255, 255, 255)));
        }
    }, enemy);
    
    return enemy;
}

Entity* createFollowingEnemy(YangPhysics *physics, Entity *player) {
    auto enemy = createBasicEnemy(physics, player);
    enemy->isDynamic = true;
    auto visiblityBox = Entity::create("CloseNormal.png");
    visiblityBox->isSolid = false;
    visiblityBox->isDynamic = false;
    visiblityBox->setContentSize(Size(4.0f * defaultSize, 4.0f * defaultSize));
    visiblityBox->setAnchorPoint(Vec2::ZERO);
    auto followPlayer = [player, enemy]() {
        Vec2 towardPlayer = player->getPosition() - enemy->getPosition();
        towardPlayer.normalize();
        enemy->velocity = 150.0f * towardPlayer;
    };
    auto wander = [enemy]() {
        enemy->velocity = Vec2::ZERO;
        Vec2 randomDirection = Vec2(rand() - (RAND_MAX / 2), rand() - (RAND_MAX / 2));
        randomDirection.normalize();
        if ((rand() % 200) == 0) {
            enemy->setOrientation(randomDirection);
            enemy->runAction(MoveBy::create(0.5f, 50.0f * randomDirection));
        }
    };
    
    enemy->behavior = wander;
    
    physics->registerCallbackOnContact([player, enemy, followPlayer](Entity *visibilityBox, Entity *otherEntity) {
        if (player == otherEntity) {
            enemy->behavior = followPlayer;
        }
    }, visiblityBox);
    
    physics->registerCallbackOnSeperate([enemy, player, wander](Entity *visibilityBox, Entity *otherEntity) {
        if (player == otherEntity) {
            enemy->behavior = wander;
        }
    }, visiblityBox);
    
    auto orientationListener = EventListenerCustom::create("orientation-changed", [enemy, visiblityBox](EventCustom* event) {
        auto sender = (Entity*)event->getUserData();
        if (sender == enemy) { // Adjust visibilty box accordingly when the enemy changes directions
            visiblityBox->setPosition(64.0f * enemy->getOrientation() + (enemy->getContentSize() - visiblityBox->getContentSize())/2.0f);
        }
    });
    
    physics->getEventDispatcher()->addEventListenerWithSceneGraphPriority(orientationListener, enemy);
    
    enemy->addChild(visiblityBox);
    
    return enemy;
}

Entity* createCalpirgEnemy(YangPhysics *physics, Entity *player, Node *gui) {
    auto enemy = createFollowingEnemy(physics, player);
    auto textBox = TextBox::create("Would you like to make a 10$ donation to Calpirg?");
    
    LabelAndCallback item1, item2;
    item1.first = "Yes";
    item1.second = [gui, textBox, enemy](Node *sender){
        sender->removeFromParent();
        sender->release();
        textBox->updateText("Thank you! Your donation will go to a good cause.");
        auto closeListener = EventListenerKeyboard::create();
        closeListener->onKeyPressed = [enemy, textBox](EventKeyboard::KeyCode keyCode, Event *event) {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                enemy->removeFromParent();
                textBox->removeFromParent();
                textBox->release();
            }
            ;
        };
        textBox->getEventDispatcher()->addEventListenerWithSceneGraphPriority(closeListener, textBox);
    };
    
    item2.first = "No";
    item2.second = [gui, textBox, enemy](Node *sender){
        sender->removeFromParent();
        sender->release();
        textBox->updateText("Wrong answer bucko.");
        auto closeListener = EventListenerKeyboard::create();
        closeListener->onKeyPressed = [enemy, textBox](EventKeyboard::KeyCode keyCode, Event *event) {
            if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                enemy->removeFromParent();
                textBox->removeFromParent();
                textBox->release();
                Director::getInstance()->pushScene(TransitionFade::create(0.5, Battle::createScene(), Color3B(255, 255, 255)));
            }
            ;
        };
        textBox->getEventDispatcher()->addEventListenerWithSceneGraphPriority(closeListener, textBox);
    };
    auto menu = KeyboardMenu::create({item1, item2});
    
    
    physics->registerCallbackOnContact([player, textBox, menu, gui](Node *enemy, Node *otherEntity) {
        if (player == otherEntity) {
            gui->addChild(textBox);
            gui->addChild(menu);
            menu->setPosition(textBox->getPosition() + Vec2(0.0f, textBox->getContentSize().height));
        }
    }, enemy);
    
    textBox->retain();
    menu->retain();
    
    return enemy;
}

Entity* createBasicNPC() {
    auto npc = Entity::create("CloseNormal.png");
    npc->setContentSize(Size(defaultSize, defaultSize));
    npc->isDynamic = false;
    
    return npc;
}

Entity* createTalkingNPC(Node* gui, std::string message) {
    auto npc = createBasicNPC();
    npc->interact = [gui, message]() {
        gui->addChild(PagedTextBox::create(message));
    };
    
    return npc;
}
