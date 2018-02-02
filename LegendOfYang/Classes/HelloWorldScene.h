#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void update(float) override;
    
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(HelloWorld);
    
private:
    int speed;
    bool movingUp, movingDown, movingLeft, movingRight;
    Sprite *sprite;
    CocosDenshion::SimpleAudioEngine *audio;
    Vec2 position;
    EventListenerKeyboard *keyboardListener;
    RepeatForever *moveUp, *moveDown, *moveLeft, *moveRight, *moveUpLeft, *moveUpRight, *moveDownLeft, *moveDownRight;
};
