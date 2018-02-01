#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// create scene
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

// initialize
bool HelloWorld::init()
{
    if (!Layer::init()) return false;
    
    // play background music
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("song.mp3");
    audio->playBackgroundMusic("song.mp3", true);
    
    // create sprite
    auto sprite = Sprite::create("CloseNormal.png");
    sprite->setAnchorPoint(Vec2(0.0,0.0));
    sprite->setPosition(100, 100);
    this->addChild(sprite, 0);
    
    // movement system
    int speed = 25;
    bool* movingUp = new bool;
    bool* movingDown = new bool;
    bool* movingLeft = new bool;
    bool* movingRight = new bool;
    
    auto eventListener = EventListenerKeyboard::create();
    
    // when a key is pressed
    eventListener->onKeyPressed = [sprite, speed, movingUp, movingDown, movingLeft, movingRight](EventKeyboard::KeyCode keyCode, Event* event) {
        
        // create actions
        auto moveUp = RepeatForever::create(MoveBy::create(0.1, Point(0, speed)));
        auto moveDown = RepeatForever::create(MoveBy::create(0.1, Point(0, (-1) * speed)));
        auto moveLeft = RepeatForever::create(MoveBy::create(0.1, Point((-1) * speed, 0)));
        auto moveRight = RepeatForever::create(MoveBy::create(0.1, Point(speed, 0)));
        auto moveUpLeft = RepeatForever::create(MoveBy::create(0.1, Point((-1) * speed, speed)));
        auto moveUpRight = RepeatForever::create(MoveBy::create(0.1, Point(speed, speed)));
        auto moveDownLeft = RepeatForever::create(MoveBy::create(0.1, Point((-1) * speed, (-1) * speed)));
        auto moveDownRight = RepeatForever::create(MoveBy::create(0.1, Point(speed, (-1) * speed)));
        
        // input respond
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                sprite->stopAllActions();
                if(*movingLeft) sprite->runAction(moveUpLeft);
                else if(*movingRight) sprite->runAction(moveUpRight);
                else sprite->runAction(moveUp);
                *movingUp = true;
                break;
                
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                sprite->stopAllActions();
                if(*movingLeft) sprite->runAction(moveDownLeft);
                else if(*movingRight) sprite->runAction(moveDownRight);
                else sprite->runAction(moveDown);
                *movingDown = true;
                break;
                
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                sprite->stopAllActions();
                if(*movingUp) sprite->runAction(moveUpLeft);
                else if(*movingDown) sprite->runAction(moveDownLeft);
                else sprite->runAction(moveLeft);
                *movingLeft = true;
                break;
                
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                sprite->stopAllActions();
                if(*movingUp) sprite->runAction(moveUpRight);
                else if(*movingDown) sprite->runAction(moveDownRight);
                else sprite->runAction(moveRight);
                *movingRight = true;
                break;
        }
    };
    
    // when a key is released
    eventListener->onKeyReleased = [sprite, speed, movingUp, movingDown, movingLeft, movingRight](EventKeyboard::KeyCode keyCode, Event* event) {
        
        // create actions
        auto moveUp = RepeatForever::create(MoveBy::create(0.1, Point(0, speed)));
        auto moveDown = RepeatForever::create(MoveBy::create(0.1, Point(0, (-1) * speed)));
        auto moveLeft = RepeatForever::create(MoveBy::create(0.1, Point((-1) * speed, 0)));
        auto moveRight = RepeatForever::create(MoveBy::create(0.1, Point(speed, 0)));
        
        // input respond
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                *movingUp = false;
                if(*movingDown) break;
                sprite->stopAllActions();
                if(*movingLeft) sprite->runAction(moveLeft);
                else if(*movingRight) sprite->runAction(moveRight);
                break;
            
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                *movingDown = false;
                if(*movingUp) break;
                sprite->stopAllActions();
                if(*movingLeft) sprite->runAction(moveLeft);
                else if(*movingRight) sprite->runAction(moveRight);
                break;
                
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                *movingLeft = false;
                if(*movingRight) break;
                sprite->stopAllActions();
                if(*movingUp) sprite->runAction(moveUp);
                else if(*movingDown) sprite->runAction(moveDown);
                break;
                
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                *movingRight = false;
                if(*movingLeft) break;
                sprite->stopAllActions();
                if(*movingUp) sprite->runAction(moveUp);
                else if(*movingDown) sprite->runAction(moveDown);
                break;
        }
    };
    
    _eventDispatcher->addEventListenerWithFixedPriority(eventListener, 2);
    
    return true;
}

