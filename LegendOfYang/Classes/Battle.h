#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Enemy.h"

USING_NS_CC;

enum Status { ChoosingCommand, ChoosingTarget, InAction, Victory, Fallen };
enum Command { Attack, Defend, Flee };
enum Target { Left, Middle, Right };

class Battle : public Scene
{
public:
    static Scene* createScene();
    virtual bool init() override;
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void displayDamage(int, int, int);
    void playerAttack(Enemy*);
    void enemyAttack(Enemy*);
    void endTurn();
    void win();
    void gameOver();
    
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(Battle);
    
private:
    float delay;
    int scheduleKey;
    Player player;
    Enemy *enemy[3];
    Status status;
    Command command;
    Target target;
    Label *hpLabel, *attackLabel, *defendLabel, *fleeLabel, *lootLabel, *levelUpLabel, *gameOverLabel;
    Sprite *playerSprite, *attackButton, *defendButton, *fleeButton;
    CocosDenshion::SimpleAudioEngine *audio;
    EventListenerKeyboard *keyboardListener;
};
