#include "Battle.h"
#include "HelloWorldScene.h"

// create scene, called in AppDelegate.cpp
Scene* Battle::createScene()
{
    // call create()
    return Battle::create();
}

// initialize
bool Battle::init()
{
    // call parent init
    if (!Scene::init()) return false;
    
    // play background music
    audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("battle.mp3");
    audio->playBackgroundMusic("battle.mp3", true);
    
    // create sprite
    sprite = Sprite::create("CloseNormal.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(500, 100);
    this->addChild(sprite, 0);
    
    // create enemy
    enemy = Sprite::create("HelloWorld.png");
    enemy->setAnchorPoint(Vec2(0.5, 0.5));
    enemy->setPosition(500, 400);
    this->addChild(enemy, 0);
    
    // add label
    label = Label::createWithSystemFont("Press A to attack!", "Arial", 30);
    label->setPosition(500, 700);
    this->addChild(label, 0);
    
    // handle input
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Battle::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    return true;
}

void Battle::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    switch (keyCode) {
        // attack
        case EventKeyboard::KeyCode::KEY_A:
            die = FadeTo::create(0.25, 0);
            enemy->runAction(die);
            label->setString("Victory! Press space to continue");
            audio->stopBackgroundMusic();
            audio->playBackgroundMusic("victory.mp3");
            victory = true;
            break;
            
        // continue
        case EventKeyboard::KeyCode::KEY_SPACE:
            if(victory)
            {
                audio->stopBackgroundMusic();
                auto director = Director::getInstance();
                director->popScene();
            }
            break;
            
        default:
            break;
    }
}
