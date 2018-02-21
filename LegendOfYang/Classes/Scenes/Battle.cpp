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
    playerSprite->setScale(2.5);
    playerSprite->setAnchorPoint(Vec2(0.5, 0.5));
    playerSprite->setPosition(500, 100);
    this->addChild(playerSprite);
    
    // create enemies
    for(int i = 0; i < 3; i++)
    {
        enemy[i] = new Enemy();
        enemy[i]->createSprite();
        enemy[i]->setPosition(200 * i + 400, 500);
        enemy[i]->getSprite()->setPosition(enemy[i]->getPosition());
        this->addChild(enemy[i]->getSprite());
    }
    
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
    
    // set flags
    status = ChoosingCommand;
    command = Attack;
    target = Left;
    delay = 0.0;
    scheduleKey = 0;
    
    // handle input
    keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Battle::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    return true;
}

void Battle::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    // refuse input if game is in action or over
    if(status == InAction || status == Fallen) return;
    
    switch (keyCode)
    {
        // use up and down arrow keys to choose command
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            if(status != ChoosingCommand) return;
            switch (command)
            {
                case Defend:
                    defendButton->setTexture("CloseNormal.png");
                    defendLabel->disableEffect();
                    command = Attack;
                    attackButton->setTexture("CloseSelected.png");
                    attackLabel->enableBold();
                    break;
                    
                case Flee:
                    fleeButton->setTexture("CloseNormal.png");
                    fleeLabel->disableEffect();
                    command = Defend;
                    defendButton->setTexture("CloseSelected.png");
                    defendLabel->enableBold();
                    break;
                    
                default:
                    break;
            }
            break;
        
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            if(status != ChoosingCommand) return;
            switch (command)
            {
                case Attack:
                    attackButton->setTexture("CloseNormal.png");
                    attackLabel->disableEffect();
                    command = Defend;
                    defendButton->setTexture("CloseSelected.png");
                    defendLabel->enableBold();
                    break;
                    
                case Defend:
                    defendButton->setTexture("CloseNormal.png");
                    defendLabel->disableEffect();
                    command = Flee;
                    fleeButton->setTexture("CloseSelected.png");
                    fleeLabel->enableBold();
                    break;
                    
                default:
                    break;
            }
            break;
        
        // use left and right arrow keys to choose target
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            if(status != ChoosingTarget) return;
            switch(target)
            {
                case Middle:
                    if(enemy[0]->isDead()) return;
                    enemy[1]->getSprite()->setColor(Color3B::WHITE);
                    target = Left;
                    enemy[0]->getSprite()->setColor(Color3B::RED);
                    break;
                    
                case Right:
                    if(enemy[1]->isDead())
                    {
                        if(enemy[0]->isDead()) return;
                        enemy[2]->getSprite()->setColor(Color3B::WHITE);
                        target = Left;
                        enemy[0]->getSprite()->setColor(Color3B::RED);
                    }
                    else
                    {
                        enemy[2]->getSprite()->setColor(Color3B::WHITE);
                        target = Middle;
                        enemy[1]->getSprite()->setColor(Color3B::RED);
                    }
                    break;
                    
                default:
                    break;
            }
            break;
        
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            if(status != ChoosingTarget) return;
            switch(target)
            {
                case Left:
                    if(enemy[1]->isDead())
                    {
                        if(enemy[2]->isDead()) return;
                        enemy[0]->getSprite()->setColor(Color3B::WHITE);
                        target = Right;
                        enemy[2]->getSprite()->setColor(Color3B::RED);
                    }
                    else
                    {
                        enemy[0]->getSprite()->setColor(Color3B::WHITE);
                        target = Middle;
                        enemy[1]->getSprite()->setColor(Color3B::RED);
                    }
                    break;
                    
                case Middle:
                    if(enemy[2]->isDead()) return;
                    enemy[1]->getSprite()->setColor(Color3B::WHITE);
                    target = Right;
                    enemy[2]->getSprite()->setColor(Color3B::RED);
                    break;
                    
                default:
                    break;
            }
            break;
        
        // if choosing target, use escape key to return to choosing command
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            if(status != ChoosingTarget) return;
            for(int i = 0; i < 3; i++) enemy[i]->getSprite()->setColor(Color3B::WHITE);
            status = ChoosingCommand;
            break;

        // proceed to choose target or respond to command
        case EventKeyboard::KeyCode::KEY_SPACE:
            switch (status) {
                case ChoosingCommand:
                    
                    switch (command) {
                        // if attack is chosen, ask the user to choose a target
                        case Attack:
                            status = ChoosingTarget;
                            if(!enemy[0]->isDead())
                            {
                                target = Left;
                                enemy[0]->getSprite()->setColor(Color3B::RED);
                            }
                            else if(!enemy[1]->isDead())
                            {
                                target = Middle;
                                enemy[1]->getSprite()->setColor(Color3B::RED);
                            }
                            else
                            {
                                target = Right;
                                enemy[2]->getSprite()->setColor(Color3B::RED);
                            }
                            break;
                        
                        // if defend is chosen, temporarily reduce damage taken
                        case Defend:
                            status = InAction;
                            Player::defend();
                            endTurn();
                            break;
                        
                        // if flee is chosen, return to the overworld
                        case Flee:
                            audio->stopBackgroundMusic();
                            Director::getInstance()->popScene();
                            break;
                            
                        default:
                            break;
                    }
                    break;
                
                // if target is chosen, perform the attack
                case ChoosingTarget:
                    status = InAction;
                    switch (command) {
                        case Attack: {
                            switch (target) {
                                case Left:
                                    enemy[0]->getSprite()->setColor(Color3B::WHITE);
                                    playerAttack(enemy[0]);
                                    break;
                                    
                                case Middle:
                                    enemy[1]->getSprite()->setColor(Color3B::WHITE);
                                    playerAttack(enemy[1]);
                                    break;
                                    
                                case Right:
                                    enemy[2]->getSprite()->setColor(Color3B::WHITE);
                                    playerAttack(enemy[2]);
                                    break;
                                    
                                default:
                                    break;
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    endTurn();
                    break;
                    
                // if the battle is won, return to the overworld
                case Victory:
                {
                    audio->stopBackgroundMusic();
                    Director::getInstance()->popScene();
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

// display a label indicating damage dealt
void Battle::displayDamage(int damage, int x, int y)
{
    auto damageLabel = Label::createWithSystemFont("-" + std::to_string(damage), "Arial", 30);
    damageLabel->setTextColor(Color4B::RED);
    damageLabel->setPosition(x, y);
    damageLabel->runAction(FadeTo::create(1, 0));
    this->addChild(damageLabel, 0);
    this->scheduleOnce([=](float delta){ this->removeChild(damageLabel); }, 1.0, std::to_string(scheduleKey));
    scheduleKey++;
}

// called when the player attacks an enemy
void Battle::playerAttack(Enemy* enemy)
{
    int damage = enemy->takeDamage(Player::getAtk());
    displayDamage(damage, enemy->getPosition().x, enemy->getPosition().y + 150);
    if(enemy->getHp() <= 0) enemy->die();
    playerSprite->setPositionY(150);
    this->scheduleOnce([=](float delta){ playerSprite->setPositionY(100); }, 0.5, std::to_string(scheduleKey));
    scheduleKey++;
    delay++;
    
    
}

// called when an enemy attacks a player
void Battle::enemyAttack(Enemy* enemy)
{
    if(enemy->isDead()) return;
    this->scheduleOnce([=](float delta){
        enemy->getSprite()->setPositionY(450);
        int damage = Player::takeDamage(enemy->getAtk());
        displayDamage(damage, 500, 200);
        hpLabel->setString("HP " + std::to_string(Player::getCurrentHp()) + "/" + std::to_string(Player::getMaxHp()));
        if(Player::getCurrentHp() == 0) gameOver();
    }, delay, std::to_string(scheduleKey));
    scheduleKey++;
    this->scheduleOnce([=](float delta){ enemy->getSprite()->setPositionY(500); }, delay + 0.5, std::to_string(scheduleKey));
    scheduleKey++;
    delay++;
}

// after a player's turn, proceed with the enemies' turn
void Battle::endTurn()
{
    if(enemy[0]->isDead() && enemy[1]->isDead() && enemy[2]->isDead())
    {
        win();
        return;
    }
    for(int i = 0; i < 3; i++) enemyAttack(enemy[i]);
    this->scheduleOnce([=](float delta){
        Player::undefend();
        if(status != Fallen) status = ChoosingCommand;
    }, delay, std::to_string(scheduleKey));
    scheduleKey = 0;
    delay = 0.0;
}

// called when all enemies are defeated
void Battle::win()
{
    status = Victory;
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("victory.mp3");
    int expGained = 0, goldGained = 0;
    for(int i = 0; i < 3; i++)
    {
        expGained += enemy[i]->getExp();
        goldGained += enemy[i]->getGold();
    }
    lootLabel = Label::createWithSystemFont("You gained " + std::to_string(expGained) + " exp and " + std::to_string(goldGained) + " gold!", "Arial", 30);
    lootLabel->setPosition(500, 750);
    this->addChild(lootLabel);
    int levelBefore = Player::getLv();
    Player::gainExp(expGained);
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
    Player::gainGold(goldGained);
}

// called when the player is fallen
void Battle::gameOver()
{
    status = Fallen;
    playerSprite->runAction(FadeTo::create(0.25, 0));
    gameOverLabel = Label::createWithSystemFont("Game Over", "Arial", 50);
    gameOverLabel->enableBold();
    gameOverLabel->setPosition(500, 400);
    this->addChild(gameOverLabel);
    audio->stopBackgroundMusic();
    audio->playBackgroundMusic("fallen.mp3");
}
