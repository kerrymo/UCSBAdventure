#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "Enemy.h"
#include "Party.h"

USING_NS_CC;

enum Status { ChoosingCommand, ChoosingTarget, InAction, Victory};
enum Command { Attack, Defend, Flee };
enum Target { Left, Middle, Right };

class Battle : public Scene
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
     Parameters: the code of the key released and the event object.
     Precondition: a key is released.
     Postcondition: the input is handled.
    */
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    
    /**
     Display the damage dealt.
     Parameters: the amount of damage dealt, the x value of the position and the y value of the position.
     Precondition: damage is dealt.
     Postcondition: a damage label is displayed and destroyed after 1s.
    */
    void displayDamage(int, int, int);
    
    /**
     The player attacks an enemy.
     Parameters: the enemy under attack.
     Precondition: the player is about to attack an enemy.
     Postcondition: the player deals damage to the enemy.
    */
    void playerAttack(Enemy*);
    
    /**
     An enemy attacks the player.
     Parameters: the attacking enemy.
     Precondition: the enemy is about to attack the player.
     Postcondition: the enemy deals damage to the player.
    */
    void enemyAttack(Enemy*);
    
    /**
     Called after each player's turn.
     Precondition: the player's turn is over.
     Postcondition: the enemies' turns are over and a new round begins.
    */
    void endTurn();
    
    /**
     Called after the player won the battle.
     Precondition: all the enemies are dead.
     Postcondition: the player gets the loot and returns to the overworld.
    */
    void win();
    
    /**
     Called after the party's fallen.
     Precondition: the player is dead.
     Postcondition: the game is ended.
    */
    void gameOver();
    
    /**
     create a create() function that calls constructor, init and autorelease
     PostCondition: the constructor, init and autorelease are called.
    */
    CREATE_FUNC(Battle);
    
    void onEnterTransitionDidFinish() override;
private:
    float delay;
    int scheduleKey, actingPlayer;
    Enemy *enemy[3];
    Status status;
    Command command;
    Target target;
    Label *attackLabel, *defendLabel, *fleeLabel, *lootLabel, *levelUpLabel, *gameOverLabel;
    Sprite *playerSprite, *attackButton, *defendButton, *fleeButton;
    CocosDenshion::SimpleAudioEngine *audio;
    EventListenerKeyboard *keyboardListener;
};
