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
#include "OverworldScene.hpp"
#include "Utility.hpp"
#include <iostream>

void EntityCreator::setupAnimation(Entity *entity) {
    auto size = entity->getContentSize();
    entity->setTexture("player_down.png");
    entity->setContentSize(size);
    auto orientationListener = EventListenerCustom::create("orientation-changed", [entity](EventCustom* event) {
        
        auto sender = (Entity*)event->getUserData();
        if (sender == entity) { // Adjust Player animation
            float theta = atan2f(entity->getOrientation().y, entity->getOrientation().x);
            auto size = entity->getContentSize();
            if (theta <= M_PI_4+ 0.01f && theta >= -M_PI_4 - 0.01f) {
                entity->setTexture("player_right.png");
            } else if (theta > M_PI_4 && theta < 3*M_PI_4) {
                entity->setTexture("player_up.png");
            } else if (theta > 3 * M_PI_4 || theta < -3*M_PI_4) {
                entity->setTexture("player_left.png");
            } else {
                entity->setTexture("player_down.png");
            }
            
            entity->setContentSize(size);
        }
    });
    
    scene->physics->getEventDispatcher()->addEventListenerWithSceneGraphPriority(orientationListener, entity);
}

Entity* EntityCreator::createPlayer() {
    // Add player
    auto player = Entity::create("player_down.png");
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
    interactionKeyboardListener->onKeyPressed = [interactionBox, this, player](EventKeyboard::KeyCode keyCode, Event *event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
            auto boundingBox = interactionBox->getCollisionBox();
            boundingBox.origin += defaultSize * player->getOrientation() + (player->getContentSize() - interactionBox->getContentSize()) / 2.0f;
            auto potentialInteracters = scene->physics->getCollidingEntities(boundingBox);
            for (auto potentialInteracter : potentialInteracters) {
                if (potentialInteracter->interact != nullptr) {
                    potentialInteracter->interact();
                    break; // So you only interact with one thing at a time
                }
            }
        }
    };
    
    setupAnimation(player);
    
    player->getEventDispatcher()->addEventListenerWithSceneGraphPriority(interactionKeyboardListener, interactionBox);
    player->addChild(interactionBox);
    
    return player;
}


Entity* EntityCreator::createBasicEnemy() {
    auto enemy = Entity::create("CloseNormal.png");
    enemy->setContentSize(Size(defaultSize, defaultSize));
    
    scene->physics->registerCallbackOnContact([this](Node *enemy, Node *otherEntity) {
        if (scene->player == otherEntity) {
            enemy->removeFromParent();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, Battle::createScene(), Color3B(255, 255, 255)));
        }
    }, enemy);
    
    enemy->setColor(Color3B(255, 150, 150));
    
    setupAnimation(enemy);
    
    return enemy;
}

Entity* EntityCreator::createFollowingEnemy() {
    auto enemy = createBasicEnemy();
    enemy->isDynamic = true;
    auto visiblityBox = Entity::create();
    visiblityBox->isSolid = false;
    visiblityBox->isDynamic = false;
    visiblityBox->setContentSize(Size(6.0f * defaultSize, 6.0f * defaultSize));
    visiblityBox->setAnchorPoint(Vec2::ZERO);
    auto followPlayer = [this, enemy]() {
        Vec2 towardPlayer = scene->player->getPosition() - enemy->getPosition();
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
    
    scene->physics->registerCallbackOnContact([this, enemy, followPlayer](Entity *visibilityBox, Entity *otherEntity) {
        if (scene->player == otherEntity) {
            enemy->behavior = followPlayer;
        }
    }, visiblityBox);
    
    scene->physics->registerCallbackOnSeperate([this, enemy, wander](Entity *visibilityBox, Entity *otherEntity) {
        if (scene->player == otherEntity) {
            enemy->behavior = wander;
        }
    }, visiblityBox);
    
    auto orientationListener = EventListenerCustom::create("orientation-changed", [enemy, visiblityBox](EventCustom* event) {
        auto sender = (Entity*)event->getUserData();
        if (sender == enemy) { // Adjust visibilty box accordingly when the enemy changes directions
            visiblityBox->setPosition(64.0f * enemy->getOrientation() + (enemy->getContentSize() - visiblityBox->getContentSize())/2.0f);
        }
    });
    
    scene->physics->getEventDispatcher()->addEventListenerWithSceneGraphPriority(orientationListener, enemy);
    
    enemy->addChild(visiblityBox);
    
    return enemy;
}

Entity* EntityCreator::createCalpirgEnemy() {
    auto enemy = createFollowingEnemy();
    auto textBox = TextBox::create("Would you like to make a $10 donation to Calpirg?");
    
    LabelAndCallback item1, item2;
    item1.first = "Yes";
    item1.second = [this, textBox, enemy](Node *sender) {
        sender->removeFromParent();
        sender->release();
        if (Player::getGold() >= 10) {
            textBox->updateText("Thank you! Your donation will go to a good cause.");
            auto closeListener = EventListenerKeyboard::create();
            closeListener->onKeyPressed = [enemy, textBox](EventKeyboard::KeyCode keyCode, Event *event) {
                if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                    Player::setGold(Player::getGold()-10);
                    enemy->removeFromParent();
                    textBox->removeFromParent();
                    textBox->release();
                }
            };
            textBox->getEventDispatcher()->addEventListenerWithSceneGraphPriority(closeListener, textBox);
        } else {
            textBox->updateText("Hey you don't have enough money.");
            auto closeListener = EventListenerKeyboard::create();
            closeListener->onKeyPressed = [enemy, textBox](EventKeyboard::KeyCode keyCode, Event *event) {
                if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
                    enemy->removeFromParent();
                    textBox->removeFromParent();
                    textBox->release();
                    Director::getInstance()->pushScene(TransitionFade::create(0.5, Battle::createScene(), Color3B(255, 255, 255)));
                }
            };
            textBox->getEventDispatcher()->addEventListenerWithSceneGraphPriority(closeListener, textBox);
        }
        
    };
    
    item2.first = "No";
    item2.second = [textBox, enemy](Node *sender){
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
            };
        };
        textBox->getEventDispatcher()->addEventListenerWithSceneGraphPriority(closeListener, textBox);
    };
    auto menu = KeyboardMenu::create({item1, item2});
    
    
    scene->physics->registerCallbackOnContact([textBox, menu, this](Node *enemy, Node *otherEntity) {
        if (scene->player == otherEntity) {
            scene->gui->addChild(textBox);
            scene->gui->addChild(menu);
            menu->setPosition(textBox->getPosition() + Vec2(0.0f, textBox->getContentSize().height));
        }
    }, enemy);
    
    textBox->retain();
    menu->retain();
    
    return enemy;
}

Entity* EntityCreator::createBasicNPC() {
    auto npc = Entity::create("CloseNormal.png");
    npc->setContentSize(Size(defaultSize, defaultSize));
    npc->isDynamic = false;
    
    npc->setColor(Color3B(150, 255, 150));
    setupAnimation(npc);
    
    return npc;
}

Entity* EntityCreator::createLoadingZone(std::string worldFilename, std::string entranceName) {
    auto loadingZone = Entity::create("CloseNormal.png");
    loadingZone->setContentSize(Size(defaultSize, defaultSize));
    loadingZone->isDynamic = false;
    loadingZone->isSolid = false;
    
    scene->physics->registerCallbackOnContact([this, worldFilename, entranceName](Node *loadingZone, Node *otherEntity) {
        if (scene->player == otherEntity) {
            auto nextScene = OverworldScene::createWithTileMap(worldFilename);
            auto entrance = nextScene->world->getChildByName(entranceName);
            
            nextScene->player->setPosition(entrance->getPosition());
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, nextScene, Color3B(0, 0, 0)));
        }
    }, loadingZone);
    
    return loadingZone;
}

Entity* EntityCreator::createTalkingNPC(std::string message) {
    auto npc = createBasicNPC();
    auto lookAround = [npc](float dt) {
        npc->setOrientation(randomDirection());
    };
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule(lookAround, npc, 4.0f, kRepeatForever, 0.0f, false, "myCallbackKey");
    
    npc->interact = [this, message, npc]() {
        npc->setOrientation(scene->player->getCollisionBox().origin - npc->getCollisionBox().origin);
        scene->gui->addChild(PagedTextBox::create(message));
    };
    
    
    return npc;
}

Entity* EntityCreator::createStoreNPC(std::vector<std::pair<Item*, int>> itemsAndPrices) {
    auto npc = createBasicNPC();
    npc->interact = [this, npc, itemsAndPrices]() {
        auto textBox = TextBox::create("Hey kid I got that stuff you're looking for. You buying?");
        
        npc->setOrientation(scene->player->getCollisionBox().origin - npc->getCollisionBox().origin);
        LabelAndCallback yesItem, noItem;
        yesItem.first = "Yes";
        yesItem.second = [this, itemsAndPrices](Node *sender) {
            std::vector<LabelAndCallback> shopItems;
            for (auto itemAndPrice : itemsAndPrices) {
                LabelAndCallback shopItem;
                shopItem.first = itemAndPrice.first->getName() + "   $" + std::to_string(itemAndPrice.second);
                shopItem.second = [this, itemAndPrice](Node *sender) {
                    if (Player::getGold() > itemAndPrice.second) {
                        Player::addItem(itemAndPrice.first);
                        Player::setGold(Player::getGold() - itemAndPrice.second);
                        scene->gui->addChild(PagedTextBox::create("Holla Holla get Dollas."));
                    } else {
                        scene->gui->addChild(PagedTextBox::create("Come back here when you're not poor."));
                    }
                };
                shopItems.push_back(shopItem);
            }
            shopItems.push_back(KeyboardMenu::closeItem());
            scene->gui->addChild(KeyboardMenu::create(shopItems));
        };
        noItem.first = "No";
        noItem.second = [this, textBox](Node *sender) {
            textBox->removeFromParent();
            sender->removeFromParent();
            scene->gui->addChild(PagedTextBox::create("If your GPA ever gets too low come see me again."));
        };
        auto menu = KeyboardMenu::create({yesItem, noItem});
        menu->setPosition(textBox->getPosition() + Vec2(0.0f, textBox->getContentSize().height));
        
        scene->gui->addChild(textBox);
        scene->gui->addChild(menu);
    };
    
    return npc;
}

Entity* createChest(Item *item) {
    // TODO : The graphics needed are already in the resource folder
    
}
