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

// initialize
bool OverworldScene::init() {
    return Scene::initWithPhysics();
}

Scene* OverworldScene::createWithTileMap(std::string filename) {
    // Setup node Layers
    auto scene = OverworldScene::create();
    scene->gui = Entity::create();
    scene->world = Entity::create();
    scene->addChild(scene->world, 0);
    scene->addChild(scene->gui, 1); // GUI always has higher event priority over anything else
    
    // Setup Tile map
    scene->tileMap = TMXTiledMap::create(filename);
    scene->meta = scene->tileMap->getLayer("Meta");
    scene->world->addChild(scene->tileMap, 0, 99);
    
    // Add physics handler to the world
    scene->physics = YangPhysics::createWithTileMap(scene->tileMap);
    scene->world->addChild(scene->physics);
    
    // Add player
    scene->player = createPlayer(scene->physics);
    scene->player->setPosition(Vec2(256.0f, 1024.0f));
    
    scene->world->addChild(scene->player);
    scene->world->runAction(Follow::create(scene->player));
    
    // Add NPC
    auto npc = createTalkingNPC(scene->gui, "Hello World");
    npc->setPosition(Vec2(64.0f, 1024.0f));
    scene->world->addChild(npc);
    
    // Add Enemy
    auto enemy = createFollowingEnemy(scene->physics, scene->player);
    enemy->setPosition(Vec2(512.0f, 1024.0f));
    scene->world->addChild(enemy);
    
    auto enemy2 = createCalpirgEnemy(scene->physics, scene->player, scene->gui);
    enemy2->setPosition(Vec2(650.0f, 1024.0f));
    scene->world->addChild(enemy2);
    
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
    float vx = heldKey[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW] - heldKey[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW];
    float vy = heldKey[(int)EventKeyboard::KeyCode::KEY_UP_ARROW] - heldKey[(int)EventKeyboard::KeyCode::KEY_DOWN_ARROW];
    
    auto velocityDirection = Vec2(vx, vy);
    velocityDirection.normalize(); // Components shouldn't compound speed should be the same in any direction
    
    player->velocity = velocityDirection * 200.0f;
    
}

void OverworldScene::onExitTransitionDidStart()  {
    Scene::onExitTransitionDidStart();
    for (int i = 0; i < 200; i++) {
        heldKey[i] = false;
    }
    physics->pauseAll();
}

void OverworldScene::onEnter() {
    Scene::onEnter();
    physics->resumeAll();
}

Vec2 OverworldScene::tileCoordForPosition(Vec2 position) {
    Size tileSize = tileMap->getTileSize();
    int x = position.x / tileSize.width;
    int y = ((tileMap->getMapSize().height * tileSize.height) - position.y) / tileSize.height;
    return Vec2(x, y);
}

#pragma mark input

void OverworldScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    heldKey[(int)keyCode] = true;
    
    if (keyCode == EventKeyboard::KeyCode::KEY_E) {
        // Present Inventory
        std::vector<LabelAndCallback> items;
        LabelAndCallback item1, item2, item3;
        item1.first = "Inventory";
        item1.second = [this](Node *sender) { // TODO : self should be weak, shared_ptr, or autorelease
            this->gui->addChild(Inventory::create());
        };
        item2.first = "Stats";
        item2.second = [this](Node *sender) {
            this->gui->addChild(PlayerStatsDisplay::create());
        };
        item3.first = "Close";
        item3.second = [this](Node *sender) {
            sender->removeFromParent();
        };
        items.push_back(item1);
        items.push_back(item2);
        items.push_back(item3);
        auto menu = KeyboardMenu::create(items);
        gui->addChild(menu);
    }
    
}

void OverworldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    heldKey[(int)keyCode] = false;
}