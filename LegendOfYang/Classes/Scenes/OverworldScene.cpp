//
//  OverworldScene.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/7/18.
//

#include "OverworldScene.hpp"
#include "PagedTextBox.hpp"
#include "KeyboardMenu.hpp"
#include "Inventory.hpp"
#include "PlayerStatsDisplay.hpp"
#include "YangPhysics.hpp"
#include "Battle.h"
#include "Consumable.hpp"
#include "Player.h"
#include <iostream>

OverworldScene* OverworldScene::createWithTileMap(std::string filename) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("world.mp3", true);
    
    // Setup node Layers
    auto scene = OverworldScene::create();
    
    // Set world name
    size_t beforeExtension = filename.find_last_of(".");
    scene->worldName = filename.substr(0, beforeExtension);
    
    // Setup Tile map
    scene->tileMap = TMXTiledMap::create(filename);
    scene->meta = scene->tileMap->getLayer("Meta");
    scene->meta->setVisible(false);
    auto backgroundOrder = scene->tileMap->getLayer("Background")->getLocalZOrder();
    scene->addChild(scene->tileMap, 0);
    
    // Setup node Layers
    scene->gui = Entity::create();
    scene->world = Entity::create();
    scene->addChild(scene->gui, 1); // GUI always has higher event priority over anything else
    scene->tileMap->addChild(scene->world, backgroundOrder); // All entities always rendered just in front of layer named "Background"
    
    // Add physics handler to the world
    scene->physics = YangPhysics::createWithTileMap(scene->tileMap);
    scene->world->addChild(scene->physics);
    
    // Setup Entity Creator
    auto entityCreator = new EntityCreator(scene);
    scene->entityCreator = entityCreator;
    
    // Add player
    scene->player = entityCreator->createPlayer();
    
    scene->world->addChild(scene->player);
    scene->tileMap->runAction(Follow::createWithOffset(scene->player, 0, 0, Rect(Vec2::ZERO, scene->tileMap->getMapSize() * scene->tileMap->getTileSize().height)));
    
    // Populate world with entities
    auto objectGroup = scene->tileMap->getObjectGroup("Objects");
    if (objectGroup != nullptr) {
        auto spawnPoint = objectGroup->getObject("SpawnPoint");
        int x = spawnPoint["x"].asInt();
        int y = spawnPoint["y"].asInt();
        scene->player->setPosition(x,y);
        
        for (auto metaObject : objectGroup->getObjects()) {
            auto objectMap = metaObject.asValueMap();
            Node *entity;
            auto type = objectMap["type"].asString();
            if (type == "TalkingNPC") {
                entity = entityCreator->createTalkingNPC(objectMap.at("message").asString());
            } else if (type == "LoadingZone") {
                entity = entityCreator->createLoadingZone(objectMap.at("world").asString() + ".tmx", objectMap.at("entrance").asString());
                entity->setContentSize(Size(objectMap["width"].asFloat(), objectMap["height"].asFloat()));
            } else if (type == "Entrance") {
                entity = Node::create();
            } else if (type == "FollowingEnemy") {
                entity = entityCreator->createFollowingEnemy();
            } else if (type == "StoreNPC") {
                entity = entityCreator->createStoreNPC({{Consumable::caffinePills, 10}, {Consumable::degreePetition, 10}});
            } else if (type == "CalpirgEnemy") {
                entity = entityCreator->createCalpirgEnemy();
            } else if (type == "Chest") {
                auto itemName = objectMap.at("item").asString();
                entity = entityCreator->createChest(Item::itemFromName(itemName), objectMap["id"].asInt());
            } else if (type == "Boss") {
                entity = entityCreator->createBoss();
            } else {
                continue;
            }
            std::cout << metaObject.getDescription();
            entity->setPosition(objectMap["x"].asFloat(), objectMap["y"].asFloat());
            entity->setName(objectMap["name"].asString());
            entity->setTag(objectMap["id"].asInt());
            scene->world->addChild(entity);
        }
    }
    
    // Setup keyboard listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(OverworldScene::onKeyPressed, scene);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(OverworldScene::onKeyReleased, scene);
    scene->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, scene);
    
    // schedule update
    scene->scheduleUpdateWithPriority(LOOP_UPDATE_ORDER_INPUT);
    
    // Automatically pause world when something is added to gui
    auto guiListener = EventListenerCustom::create("childrenChanged", CC_CALLBACK_1(OverworldScene::guiChildrenChanged, scene));
    scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(guiListener, scene);
    
    return scene;
}

void OverworldScene::guiChildrenChanged(EventCustom *event) {
    auto sender = (Node*)(event->getUserData());
    if (sender == gui) {
        if (sender->getChildrenCount() > 0) {
            physics->pauseAll();
        } else {
            physics->resumeAll();
        }
    }
}

void OverworldScene::update(float delta) {
    float vx = (heldKey[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW] || heldKey[(int)EventKeyboard::KeyCode::KEY_D]) - (heldKey[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW] || heldKey[(int)EventKeyboard::KeyCode::KEY_A]);
    float vy = (heldKey[(int)EventKeyboard::KeyCode::KEY_UP_ARROW] || heldKey[(int)EventKeyboard::KeyCode::KEY_W]) - (heldKey[(int)EventKeyboard::KeyCode::KEY_DOWN_ARROW] || heldKey[(int)EventKeyboard::KeyCode::KEY_S]);
    
    auto velocityDirection = Vec2(vx, vy);
    velocityDirection.normalize(); // Components shouldn't compound speed should be the same in any direction
    
    player->velocity = velocityDirection * 200.0f;
    
    
}

void OverworldScene::onExitTransitionDidStart()  {
    Scene::onExitTransitionDidStart();
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopBackgroundMusic();
    for (int i = 0; i < 200; i++) {
        heldKey[i] = false;
    }
    physics->pauseAll();
}

void OverworldScene::onEnter() {
    Scene::onEnter();
    physics->resumeAll();
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("world.mp3");
}

#pragma mark input

void OverworldScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    heldKey[(int)keyCode] = true;
    
    if (keyCode == EventKeyboard::KeyCode::KEY_E) {
        // Present Inventory
        std::vector<LabelAndCallback> items;
        LabelAndCallback item1, item2;
        item1.first = "Inventory";
        item1.second = [this](Node *sender) {
            this->gui->addChild(Inventory::create());
        };
        item2.first = "Stats";
        item2.second = [this](Node *sender) {
            this->gui->addChild(PlayerStatsDisplay::create());
        };
        items.push_back(item1);
        items.push_back(item2);
        items.push_back(KeyboardMenu::closeItem());
        auto menu = KeyboardMenu::create(items);
        gui->addChild(menu);
    }
    
}

void OverworldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    heldKey[(int)keyCode] = false;
}
