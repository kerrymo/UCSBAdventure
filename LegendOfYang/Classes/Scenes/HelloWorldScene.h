#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"

USING_NS_CC;

class HelloWorld : public Scene
{
public:
    /**
     Create the scene.
     Return: the created scene.
     Postcondition: a new scene is created.
    */
    static Scene* createScene();
    
    /**
     Initialize the scene.
     Return: a boolean indicating success.
     Postcondition: the scene is initialized.
    */
    virtual bool init() override;
    
    /**
     Handle the input.
     Parameters: the code of the key pressed and the event object.
     Precondition: a key is pressed.
     Postcondition: the input is handled.
    */
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    
    /**
     Handle the input.
     Parameters: the code of the key released and the event object.
     Precondition: a key is released.
     Postcondition: the input is handled.
    */
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    
    /**
     Update the scene every frame.
     Parameters: the time passed since last update.
     Postcondition: the scene is updated.
    */
    void update(float) override;
    
    /**
     Handle the option selected.
     Parameters: the option selected.
     Precondition: an option is selected.
     Postcondition: the option is handled.
    */
    void handleOption(Node *option);
    
    /**
     create a create() function that calls constructor, init and autorelease
     PostCondition: the constructor, init and autorelease are called.
    */
    CREATE_FUNC(HelloWorld);
    
private:
    int speed;
    bool movingUp, movingDown, movingLeft, movingRight, paused;
    Player player;
    Sprite *sprite;
    CocosDenshion::SimpleAudioEngine *audio;
    Vec2 position;
    EventListenerKeyboard *keyboardListener;
    RepeatForever *moveUp, *moveDown, *moveLeft, *moveRight, *moveUpLeft, *moveUpRight, *moveDownLeft, *moveDownRight;
};
