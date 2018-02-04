#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class Battle : public Scene
{
public:
    static Scene* createScene();
    virtual bool init() override;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(Battle);
    
private:
    bool victory;
    Label *label;
    FadeTo *die;
    Sprite *sprite, *enemy;
    CocosDenshion::SimpleAudioEngine *audio;
    EventListenerKeyboard *keyboardListener;
};
