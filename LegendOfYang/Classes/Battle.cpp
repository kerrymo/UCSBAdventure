#include "Battle.h"
#include "HelloWorldScene.h"

// create scene, called in AppDelegate.cpp
Scene* Battle::createScene()
{
    // call create()
    return Battle::create();
}

// initialize
bool Battle::init()
{
    // call parent init
    if (!Scene::init()) return false;
    
    // play background music
    audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("battle.mp3");
    audio->playBackgroundMusic("battle.mp3", true);
    
    // create sprite
    sprite = Sprite::create("CloseNormal.png");
    sprite->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(500, 100);
    this->addChild(sprite, 0);
    
    // create enemy
    enemy = Sprite::create("HelloWorld.png");
    enemy->setAnchorPoint(Vec2(0.5, 0.5));
    enemy->setPosition(600, 500);
    this->addChild(enemy, 0);
    
    // create buttons
    attackButton = Sprite::create("CloseSelected.png");
    attackButton->setAnchorPoint(Vec2(0.5, 0.5));
    attackButton->setPosition(100, 500);
    this->addChild(attackButton, 0);
    
    defendButton = Sprite::create("CloseNormal.png");
    defendButton->setAnchorPoint(Vec2(0.5, 0.5));
    defendButton->setPosition(100, 400);
    this->addChild(defendButton, 0);
    
    fleeButton = Sprite::create("CloseNormal.png");
    fleeButton->setAnchorPoint(Vec2(0.5, 0.5));
    fleeButton->setPosition(100, 300);
    this->addChild(fleeButton, 0);
    
    // add labels
    attackLabel = Label::createWithSystemFont("Attack", "Arial", 30);
    attackLabel->enableBold();
    attackLabel->setPosition(200, 500);
    this->addChild(attackLabel, 0);
    
    defendLabel = Label::createWithSystemFont("Defend", "Arial", 30);
    defendLabel->setPosition(200, 400);
    this->addChild(defendLabel, 0);
    
    fleeLabel = Label::createWithSystemFont("Flee", "Arial", 30);
    fleeLabel->setPosition(200, 300);
    this->addChild(fleeLabel, 0);
    
    // set status
    status = Attack;
    
    // handle input
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Battle::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    return true;
}

void Battle::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    switch (keyCode) {
        // select command
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            switch (status) {
                case Defend:
                    defendButton->setTexture("CloseNormal.png");
                    defendLabel->disableEffect();
                    status = Attack;
                    attackButton->setTexture("CloseSelected.png");
                    attackLabel->enableBold();
                    break;
                    
                case Flee:
                    fleeButton->setTexture("CloseNormal.png");
                    fleeLabel->disableEffect();
                    status = Defend;
                    defendButton->setTexture("CloseSelected.png");
                    defendLabel->enableBold();
                    
                default:
                    break;
            }
            break;
        
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            switch (status) {
                case Attack:
                    attackButton->setTexture("CloseNormal.png");
                    attackLabel->disableEffect();
                    status = Defend;
                    defendButton->setTexture("CloseSelected.png");
                    defendLabel->enableBold();
                    break;
                    
                case Defend:
                    defendButton->setTexture("CloseNormal.png");
                    defendLabel->disableEffect();
                    status = Flee;
                    fleeButton->setTexture("CloseSelected.png");
                    fleeLabel->enableBold();
                    
                default:
                    break;
            }
            break;

        // act with command
        case EventKeyboard::KeyCode::KEY_SPACE:
            switch (status) {
                case Attack:
                    die = FadeTo::create(0.25, 0);
                    enemy->runAction(die);
                    status = Victory;
                    audio->stopBackgroundMusic();
                    audio->playBackgroundMusic("victory.mp3");
                    break;
                    
                case Defend:
                    break;
                    
                case Flee: {
                    audio->stopBackgroundMusic();
                    auto director = Director::getInstance();
                    director->popScene();
                    break;
                }
                    
                case Victory: {
                    audio->stopBackgroundMusic();
                    auto director = Director::getInstance();
                    director->popScene();
                    break;
                }
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}
