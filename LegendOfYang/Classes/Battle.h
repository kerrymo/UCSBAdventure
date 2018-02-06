#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

enum Status { Attack, Defend, Flee, Victory };

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
    Status status;
    Label *label, *attackLabel, *defendLabel, *fleeLabel;
    FadeTo *die;
    Sprite *sprite, *enemy, *attackButton, *defendButton, *fleeButton;
    CocosDenshion::SimpleAudioEngine *audio;
    EventListenerKeyboard *keyboardListener;
};
