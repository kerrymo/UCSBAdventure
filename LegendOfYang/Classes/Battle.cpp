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
    playerSprite = Sprite::create("CloseNormal.png");
    playerSprite->setAnchorPoint(Vec2(0.5, 0.5));
    playerSprite->setPosition(500, 100);
    this->addChild(playerSprite);
    
    // create enemy
    enemySprite = Sprite::create("HelloWorld.png");
    enemySprite->setAnchorPoint(Vec2(0.5, 0.5));
    enemySprite->setPosition(600, 500);
    this->addChild(enemySprite);
    
    // create buttons
    attackButton = Sprite::create("CloseSelected.png");
    attackButton->setAnchorPoint(Vec2(0.5, 0.5));
    attackButton->setPosition(100, 500);
    this->addChild(attackButton);
    
    defendButton = Sprite::create("CloseNormal.png");
    defendButton->setAnchorPoint(Vec2(0.5, 0.5));
    defendButton->setPosition(100, 400);
    this->addChild(defendButton);
    
    fleeButton = Sprite::create("CloseNormal.png");
    fleeButton->setAnchorPoint(Vec2(0.5, 0.5));
    fleeButton->setPosition(100, 300);
    this->addChild(fleeButton);
    
    // add labels
    hpLabel = Label::createWithSystemFont("HP " + std::to_string(Player::getCurrentHp()) + "/" + std::to_string(Player::getMaxHp()), "Arial", 25);
    hpLabel->setPosition(500, 50);
    this->addChild(hpLabel);
    
    attackLabel = Label::createWithSystemFont("Attack", "Arial", 30);
    attackLabel->enableBold();
    attackLabel->setPosition(200, 500);
    this->addChild(attackLabel);
    
    defendLabel = Label::createWithSystemFont("Defend", "Arial", 30);
    defendLabel->setPosition(200, 400);
    this->addChild(defendLabel);
    
    fleeLabel = Label::createWithSystemFont("Flee", "Arial", 30);
    fleeLabel->setPosition(200, 300);
    this->addChild(fleeLabel);
    
    // set status
    status = Attack;
    
    // handle input
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Battle::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    return true;
}

void Battle::displayDamage(int damage, int x, int y)
{
    auto damageLabel = Label::createWithSystemFont("-" + std::to_string(damage), "Arial", 30);
    damageLabel->setTextColor(Color4B::RED);
    damageLabel->setPosition(x, y);
    damageLabel->runAction(FadeTo::create(1, 0));
    this->addChild(damageLabel, 0);
    this->scheduleOnce([=](float delta){ this->removeChild(damageLabel); }, 1.0, "a");
}

void Battle::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    // refuse input if game is over
    if(fallen) return;
    
    switch (keyCode)
    {
        // select command
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            switch (status)
            {
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
            switch (status)
            {
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
            if(paused) break;
            switch (status)
            {
                case Attack:
                {
                    // player attacks
                    playerSprite->setPositionY(150);
                    this->scheduleOnce([=](float delta){ playerSprite->setPositionY(100); }, 0.5, "b");
                    int damage = enemy.takeDamage(Player::getAtk());
                    displayDamage(damage, 600, 650);
                    
                    if(enemy.getHp() <= 0)
                    // enemy dies
                    {
                        enemySprite->runAction(FadeTo::create(0.25, 0));
                        win();
                    } else
                    // enemy attacks after player attacks
                    {
                        this->scheduleOnce([=](float delta){ enemyAttack(); }, 1.0, "c");
                    }
                    break;
                }
                    
                case Defend:
                {
                    Player::defend();
                    enemyAttack();
                    break;
                }
                    
                case Flee:
                {
                    audio->stopBackgroundMusic();
                    Director::getInstance()->popScene();
                    break;
                }
                    
                case Victory:
                {
                    audio->stopBackgroundMusic();
                    Director::getInstance()->popScene();
                    break;
                }
                    
                default:
                    break;
            }
            Player::undefend();
            
            // pause for 1s after command
            paused = true;
            this->scheduleOnce([=](float delta){ paused = false; }, 1.0, "d");
            break;
            
        default:
            break;
    }
}

void Battle::enemyAttack()
{
    enemySprite->setPositionY(450);
    this->scheduleOnce([=](float delta){ enemySprite->setPositionY(500); }, 0.5, "e");
    int damage = Player::takeDamage(enemy.getAtk());
    displayDamage(damage, 500, 200);
    hpLabel->setString("HP " + std::to_string(Player::getCurrentHp()) + "/" + std::to_string(Player::getMaxHp()));
    if(Player::getCurrentHp() == 0) gameOver();
}

void Battle::win()
{
    status = Victory;
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("victory.mp3");
    lootLabel = Label::createWithSystemFont("You gained " + std::to_string(enemy.getExp()) + " exp and " + std::to_string(enemy.getGold()) + " gold!", "Arial", 30);
    lootLabel->setPosition(500, 750);
    this->addChild(lootLabel);
    int levelBefore = Player::getLv();
    Player::gainExp(enemy.getExp());
    int levelGained = Player::getLv() - levelBefore;
    if(levelGained > 0)
    {
        if(levelGained == 1)
            levelUpLabel = Label::createWithSystemFont("You gained a level!", "Arial", 30);
        else
            levelUpLabel = Label::createWithSystemFont("You gained " + std::to_string(levelGained) + " levels!", "Arial", 30);
        levelUpLabel->setPosition(500, 700);
        this->addChild(levelUpLabel);
        hpLabel->setString("HP " + std::to_string(Player::getCurrentHp()) + "/" + std::to_string(Player::getMaxHp()));
    }
    Player::gainGold(enemy.getGold());
}

void Battle::gameOver()
{
    fallen = true;
    playerSprite->runAction(FadeTo::create(0.25, 0));
    gameOverLabel = Label::createWithSystemFont("Game Over", "Arial", 50);
    gameOverLabel->enableBold();
    gameOverLabel->setPosition(500, 400);
    this->addChild(gameOverLabel);
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("fallen.mp3");
}
