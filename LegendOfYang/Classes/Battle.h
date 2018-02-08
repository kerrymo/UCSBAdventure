#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Enemy.h"

USING_NS_CC;

enum Status { Attack, Defend, Flee, Victory };

class Battle : public Scene
{
public:
    static Scene* createScene();
    virtual bool init() override;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void displayDamage(int, int, int);
    void enemyAttack();
    void win();
    void gameOver();
    
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(Battle);
    
private:
    bool paused, victory, fallen;
    Player player;
    Enemy enemy;
    Status status;
    Label *hpLabel, *attackLabel, *defendLabel, *fleeLabel, *lootLabel, *levelUpLabel, *gameOverLabel;
    Sprite *playerSprite, *enemySprite, *attackButton, *defendButton, *fleeButton;
    CocosDenshion::SimpleAudioEngine *audio;
    EventListenerKeyboard *keyboardListener;
};
