//
//  OverworldScene.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/7/18.
//

#include "OverworldScene.hpp"
#include "PagedTextBox.hpp"

// initialize
bool OverworldScene::init() {
    return Scene::initWithPhysics();
}

Scene* OverworldScene::createWithTileMap(std::string filename) {
    // Setup node Layers
    auto scene = OverworldScene::create();
    scene->gui = Node::create();
    scene->world = Node::create();
    scene->addChild(scene->world, 0);
    scene->addChild(scene->gui, 1); // GUI always has higher event priority over anything else
    
    // Setup Tile map
    scene->tileMap = TMXTiledMap::create(filename);
    scene->meta = scene->tileMap->getLayer("Meta");
    scene->world->addChild(scene->tileMap, 0, 99);
    
    scene->player = Sprite::create("CloseNormal.png");
    scene->player->setContentSize(Size(32,32));
    scene->player->setPosition(Vec2(32.0f, 32.0f));
    scene->player->setAnchorPoint(Vec2(0.0f, 0.0f));
    scene->world->addChild(scene->player);
    scene->world->runAction(Follow::create(scene->player));
    
    // Setup keyboard listener
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(OverworldScene::onKeyPressed, scene);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(OverworldScene::onKeyReleased, scene);
    scene->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, scene);
    
    // schedule update
    scene->scheduleUpdate();
    
    return scene;
}

void OverworldScene::update(float delta) {
    float vx = heldKey[(int)EventKeyboard::KeyCode::KEY_RIGHT_ARROW] - heldKey[(int)EventKeyboard::KeyCode::KEY_LEFT_ARROW];
    float vy = heldKey[(int)EventKeyboard::KeyCode::KEY_UP_ARROW] - heldKey[(int)EventKeyboard::KeyCode::KEY_DOWN_ARROW];
    
    //log("Tile ID : %d\n", tileID);
    
    auto velocityDirection = Vec2(vx, vy);
    velocityDirection.normalize(); // Components shouldn't compound speed should be the same in any direction
    player->setPosition(player->getPosition() + 200.0f * delta * velocityDirection);
    Vec2 tilePlayerIsOn = tileCoordForPosition(player->getPosition() + player->getContentSize()/2);
    auto boundingBox = player->getBoundingBox();
    for (int i = tilePlayerIsOn.x - 1; i < tilePlayerIsOn.x + 2; i++) {
        for (int j = tilePlayerIsOn.y - 1; j < tilePlayerIsOn.y + 2; j++) {
            if (i >= 0 && j >= 0 && i < tileMap->getMapSize().width && j < tileMap->getMapSize().height && meta->getTileGIDAt(Vec2(i,j)) == 49 && boundingBox.intersectsRect(meta->getTileAt(Vec2(i,j))->getBoundingBox())) {
                printf("checking:%d,%d \n",i,j);
                auto boundingBox2 = meta->getTileAt(Vec2(i,j))->getBoundingBox();
                float dx = (boundingBox.size.width + boundingBox2.size.width) / 2.0f - fabsf(boundingBox.origin.x - boundingBox2.origin.x);
                float dy = (boundingBox.size.height + boundingBox2.size.height) / 2.0f - fabsf(boundingBox.origin.y - boundingBox2.origin.y);
                if (dx / abs(vx+0.001f) < dy / abs(vy+0.001f)) {
                    // Intersected on x side first
                    if (boundingBox.origin.x < boundingBox2.origin.x) {
                        player->setPosition(Vec2(boundingBox.origin.x - dx - 1.0f, player->getPosition().y));
                    } else {
                        player->setPosition(Vec2(boundingBox.origin.x + dx + 1.0f, player->getPosition().y));
                    }
                    
                } else {
                    if (boundingBox.origin.y < boundingBox2.origin.y) {
                        player->setPosition(Vec2(player->getPosition().x, boundingBox.origin.y - dy - 0.5f));
                    } else {
                        player->setPosition(Vec2(player->getPosition().x, boundingBox.origin.y + dy + 0.5f));
                    }
                }
            }
        }
    }
    
}

Vec2 OverworldScene::tileCoordForPosition(Vec2 position) {
    Size tileSize = tileMap->getTileSize();
    int x = position.x / tileSize.width;
    int y = ((tileMap->getMapSize().height * tileSize.height) - position.y) / tileSize.height;
    return Vec2(x, y);
}

void OverworldScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event) {
    heldKey[(int)keyCode] = true;
}

void OverworldScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event) {
    heldKey[(int)keyCode] = false;
}
