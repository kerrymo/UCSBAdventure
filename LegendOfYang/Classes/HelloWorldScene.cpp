#include <stdlib.h>
#include "HelloWorldScene.h"
#include "Battle.h"
#include "TextBox.hpp"
#include "PagedTextBox.hpp"
#include "KeyboardMenu.hpp"

// create scene, called in AppDelegate.cpp
Scene* HelloWorld::createScene()
{
    // call create()
    return HelloWorld::create();
}

// initialize
bool HelloWorld::init()
{
    // call parent init
    if (!Scene::init()) return false;
    
    // play background music
    audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("song.mp3");
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("song.mp3", true);
    
    // create sprite
    sprite = Sprite::create("CloseNormal.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(100, 100);
    this->addChild(sprite, 0);
    
    // movement system
    speed = 500;
    position = sprite->getPosition();
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    
    // Test Text Box
    auto textBoxSize = Size(this->getContentSize().width, 128);
    auto textBox = PagedTextBox::create({"Test"}, textBoxSize);
    this->addChild(textBox);
    
    // Test Menu
    std::vector<LabelAndCallback> items;
    LabelAndCallback item1, item2;
    item1.first = "Option 1";
    item2.first = "Option 2";
    item1.second = CC_CALLBACK_1(HelloWorld::handleOption, this);
    item2.second = CC_CALLBACK_1(HelloWorld::handleOption, this);
    items.push_back(item1);
    items.push_back(item2);
    auto menu = KeyboardMenu::create(items);
    this->addChild(menu);
    
    // initialize random number generator
    srand(time(NULL));
    
    // schedule update
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::handleOption(std::string option) {
    std::vector<std::string> text;
    if (option == "Option 1") {
        text.push_back("You selected option 1.");
    } else if (option == "Option 2") {
        text.push_back("You selected option 2.");
    }
    auto textBoxSize = Size(this->getContentSize().width, 128);
    auto textBox = PagedTextBox::create(text, textBoxSize);
    this->addChild(textBox, 4);
}

void HelloWorld::unpause(float delta)
{
    paused = false;
}

// when a key is pressed
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if(paused) return;
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            movingUp = true;
            break;
            
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            movingDown = true;
            break;
            
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            movingLeft = true;
            break;
            
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            movingRight = true;
            break;
            
        default:
            break;
    }
}

// when a key is released
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            movingUp = false;
            break;
            
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            movingDown = false;
            break;
            
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            movingLeft = false;
            break;
            
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            movingRight = false;
            break;
            
        default:
            break;
    }
}

// called every frame
void HelloWorld::update(float delta)
{
    // random encounter
    if(movingUp || movingDown || movingLeft || movingRight)
    {
        int i = rand() % 1000;
        if(i < 3)
        {
            paused = true;
            movingUp = false;
            movingDown = false;
            movingLeft = false;
            movingRight = false;
            this->scheduleOnce(schedule_selector(HelloWorld::unpause), 0.5);
            audio->stopBackgroundMusic();
            auto director = Director::getInstance();
            auto scene = Battle::createScene();
            director->pushScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
        }
    }
    
    // update position
    if(paused) return;
    if(!audio->isBackgroundMusicPlaying()) audio->playBackgroundMusic("song.mp3");
    if(movingUp) position.y += speed * delta;
    if(movingDown) position.y -= speed * delta;
    if(movingLeft) position.x -= speed * delta;
    if(movingRight) position.x += speed * delta;
    sprite->setPosition(position);
}
