#include "HelloWorldScene.h"

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
    audio->playBackgroundMusic("song.mp3", true);
    
    // create sprite
    sprite = Sprite::create("CloseNormal.png");
    sprite->setAnchorPoint(Vec2(0.0,0.0));
    sprite->setPosition(100, 100);
    this->addChild(sprite, 0);
    
    // movement system
    speed = 500;
    position = sprite->getPosition();
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);
    
    // schedule update
    this->scheduleUpdate();
    
    return true;
}

// called every frame
void HelloWorld::update(float delta)
{
    if(movingUp) position.y += speed * delta;
    if(movingDown) position.y -= speed * delta;
    if(movingLeft) position.x -= speed * delta;
    if(movingRight) position.x += speed * delta;
    sprite->setPosition(position);
}


// when a key is pressed
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
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
