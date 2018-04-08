#include "AppDelegate.h"
#include "OverworldScene.hpp"
#include "Player.h"
#include "Enemy.h"
#include "GameState.hpp"
#include "Guard.h"
#include "Wolf.h"
#include "Mammoth.h"
#include "Yang.h"
#include "Locke.h"
#include "Terra.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("LegendOfYang", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("LegendOfYang");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();
    
    Party party;

    // create a scene. it's an autorelease object
    auto scene = OverworldScene::createWithTileMap("TileMap.tmx");
    //auto scene = HelloWorld::createScene();
    
    // run
    //director->runWithScene(scene);
    Catch::Session session;
    session.run();

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}



TEST_CASE("gamestate-singleton") {
    GameState::defaultInstance->state["key"] = Value(true);
    REQUIRE(GameState::defaultInstance->state["key"].asBool());
}

TEST_CASE("keyboardMenu-setItems") {
    auto menu = KeyboardMenu::create({{"item1", nullptr}, {"item2", nullptr}});
    menu->setItems({{"item3", nullptr}});
    REQUIRE(menu->selectedLabelText() == "item3");
}

TEST_CASE("keyboardMenu-setContentSize") {
    auto menu = KeyboardMenu::create({{"item1", nullptr}, {"item2", nullptr}});
    menu->setContentSize(Size::ZERO);
    REQUIRE(!menu->getContentSize().equals(Size::ZERO)); // Note: should not be zero despite the call above.
}

TEST_CASE("keyboardMenu-setContentSize2") {
    auto menu = KeyboardMenu::create({{"item1", nullptr}, {"item2", nullptr}});
    menu->setContentSize(Size(1000, 1000));
    REQUIRE(!menu->getContentSize().equals(Size(1000, 1000))); // Note: should not be zero despite the call above.
}

TEST_CASE("keyboardMenu-selectedLabelText") {
    auto menu = KeyboardMenu::create({{"item1", nullptr}, {"item2", nullptr}});
    REQUIRE(menu->selectedLabelText() == "item1");
}

TEST_CASE("keyboardMenu-autoResize") {
    auto menu = KeyboardMenu::create({{"item1", nullptr}, {"item2", nullptr}});
    REQUIRE(!menu->getContentSize().equals(Size::ZERO));
}

TEST_CASE("entity-face") {
    auto e1 = Entity::create();
    auto e2 = Entity::create();
    e1->setPosition(Vec2(0, 1));
    e2->face(e1);
    REQUIRE(e2->getOrientation().equals(Vec2(0,1)));
}

TEST_CASE("entity-face2") {
    auto e1 = Entity::create();
    auto e2 = Entity::create();
    e1->setPosition(Vec2(1, 0));
    e2->face(e1);
    REQUIRE(e2->getOrientation().equals(Vec2(1,0)));
}

TEST_CASE("entity-setOrientation") {
    auto e1 = Entity::create();
    e1->setOrientation(Vec2(100, 0));
    REQUIRE(e1->getOrientation().equals(Vec2(1,0)));
}

TEST_CASE("entity-setOrientation2") {
    auto e1 = Entity::create();
    e1->setOrientation(Vec2(-100, 0));
    REQUIRE(e1->getOrientation().equals(Vec2(-1,0)));
}

TEST_CASE("entity-getCollisionBox") {
    auto e1 = Entity::create();
    e1->setPosition(1, 2);
    e1->setContentSize(Size(3, 4));
    REQUIRE(e1->getCollisionBox().equals(Rect(1, 2, 3, 4)));
}

TEST_CASE("entity-getCollisionBox2") {
    auto e1 = Entity::create();
    e1->setPosition(4, 3);
    e1->setContentSize(Size(2, 1));
    REQUIRE(e1->getCollisionBox().equals(Rect(4, 3, 2, 1)));
}

TEST_CASE("entity-getAllEntities") {
    auto e1 = Entity::create();
    auto e2 = Entity::create();
    auto e3 = Entity::create();
    
    e1->addChild(e2); e2->addChild(e3);
    REQUIRE(e1->getAllEntities().equals({e2, e3}));
}

TEST_CASE("party-fallen") {
    REQUIRE(!Party::fallen());
}

TEST_CASE("party-getFirstLivingPlayer") {
    REQUIRE(Party::getFirstLivingPlayer() == 0);
}

TEST_CASE("party-getNumOfLivingPlayer") {
    REQUIRE(Party::getNumOfLivingPlayer() == 3);
}

TEST_CASE("party-getGold") {
    REQUIRE(Party::getGold() == 0);
}

TEST_CASE("party-setGold") {
    Party::setGold(10);
    REQUIRE(Party::getGold() == 10);
}

TEST_CASE("guard-getExp") {
    Guard guard(0, 0);
    REQUIRE(guard.getExp() == 15);
}

TEST_CASE("guard-getGold") {
    Guard guard(0, 0);
    REQUIRE(guard.getGold() == 15);
}

TEST_CASE("guard-getHp") {
    Guard guard(0, 0);
    REQUIRE(guard.getHp() == 40);
}

TEST_CASE("guard-getAtk") {
    Guard guard(0, 0);
    REQUIRE(guard.getAtk() == 15);
}

TEST_CASE("guard-getDef") {
    Guard guard(0, 0);
    REQUIRE(guard.getDef() == 20);
}

TEST_CASE("guard-getPosition") {
    Guard guard(0, 0);
    REQUIRE(guard.getPosition() == Vec2(0, 0));
}

TEST_CASE("guard-setPosition") {
    Guard guard(0, 0);
    guard.setPosition(10, 10);
    REQUIRE(guard.getPosition() == Vec2(10, 10));
}

TEST_CASE("guard-takeDamage") {
    Guard guard(0, 0);
    guard.takeDamage(10);
    REQUIRE(guard.getHp() == 30);
}

TEST_CASE("guard-isDead") {
    Guard guard(0, 0);
    REQUIRE(!guard.isDead());
}

TEST_CASE("guard-die") {
    Guard guard(0, 0);
    guard.die();
    REQUIRE(guard.isDead());
}

TEST_CASE("wolf-getExp") {
    Wolf wolf(0, 0);
    REQUIRE(wolf.getExp() == 10);
}

TEST_CASE("wolf-getGold") {
    Wolf wolf(0, 0);
    REQUIRE(wolf.getGold() == 20);
}

TEST_CASE("wolf-getHp") {
    Wolf wolf(0, 0);
    REQUIRE(wolf.getHp() == 30);
}

TEST_CASE("wolf-getAtk") {
    Wolf wolf(0, 0);
    REQUIRE(wolf.getAtk() == 20);
}

TEST_CASE("wolf-getDef") {
    Wolf wolf(0, 0);
    REQUIRE(wolf.getDef() == 15);
}

TEST_CASE("wolf-getPosition") {
    Wolf wolf(0, 0);
    REQUIRE(wolf.getPosition() == Vec2(0, 0));
}

TEST_CASE("wolf-setPosition") {
    Wolf wolf(0, 0);
    wolf.setPosition(10, 10);
    REQUIRE(wolf.getPosition() == Vec2(10, 10));
}

TEST_CASE("wolf-takeDamage") {
    Wolf wolf(0, 0);
    wolf.takeDamage(10);
    REQUIRE(wolf.getHp() == 20);
}

TEST_CASE("wolf-isDead") {
    Wolf wolf(0, 0);
    REQUIRE(!wolf.isDead());
}

TEST_CASE("wolf-die") {
    Wolf wolf(0, 0);
    wolf.die();
    REQUIRE(wolf.isDead());
}

TEST_CASE("mammoth-getExp") {
    Mammoth mammoth(0, 0);
    REQUIRE(mammoth.getExp() == 20);
}

TEST_CASE("mammoth-getGold") {
    Mammoth mammoth(0, 0);
    REQUIRE(mammoth.getGold() == 10);
}

TEST_CASE("mammoth-getHp") {
    Mammoth mammoth(0, 0);
    REQUIRE(mammoth.getHp() == 50);
}

TEST_CASE("mammoth-getAtk") {
    Mammoth mammoth(0, 0);
    REQUIRE(mammoth.getAtk() == 10);
}

TEST_CASE("mammoth-getDef") {
    Mammoth mammoth(0, 0);
    REQUIRE(mammoth.getDef() == 25);
}

TEST_CASE("mammoth-getPosition") {
    Mammoth mammoth(0, 0);
    REQUIRE(mammoth.getPosition() == Vec2(0, 0));
}

TEST_CASE("mammoth-setPosition") {
    Mammoth mammoth(0, 0);
    mammoth.setPosition(10, 10);
    REQUIRE(mammoth.getPosition() == Vec2(10, 10));
}

TEST_CASE("mammoth-takeDamage") {
    Mammoth mammoth(0, 0);
    mammoth.takeDamage(10);
    REQUIRE(mammoth.getHp() == 41);
}

TEST_CASE("mammoth-isDead") {
    Mammoth mammoth(0, 0);
    REQUIRE(!mammoth.isDead());
}

TEST_CASE("mammoth-die") {
    Mammoth mammoth(0, 0);
    mammoth.die();
    REQUIRE(mammoth.isDead());
}

TEST_CASE("yang-getLv") {
    Yang yang;
    REQUIRE(yang.getLv() == 1);
}

TEST_CASE("yang-getExp") {
    Yang yang;
    REQUIRE(yang.getExp() == 0);
}

TEST_CASE("yang-getMaxHp") {
    Yang yang;
    REQUIRE(yang.getMaxHp() == 50);
}

TEST_CASE("yang-getCurrentHp") {
    Yang yang;
    REQUIRE(yang.getCurrentHp() == 50);
}

TEST_CASE("yang-setCurrentHp") {
    Yang yang;
    yang.setCurrentHp(40);
    REQUIRE(yang.getCurrentHp() == 40);
}

TEST_CASE("yang-getAtk") {
    Yang yang;
    REQUIRE(yang.getAtk() == 10);
}

TEST_CASE("yang-getDef") {
    Yang yang;
    REQUIRE(yang.getDef() == 30);
}

TEST_CASE("yang-takeDamage") {
    Yang yang;
    yang.takeDamage(10);
    REQUIRE(yang.getCurrentHp() == 43);
}

TEST_CASE("yang-gainExp") {
    Yang yang;
    yang.gainExp(10);
    REQUIRE(yang.getExp() == 10);
}

TEST_CASE("yang-isDead") {
    Yang yang;
    REQUIRE(!yang.isDead());
}

TEST_CASE("locke-getLv") {
    Locke locke;
    REQUIRE(locke.getLv() == 1);
}

TEST_CASE("locke-getExp") {
    Locke locke;
    REQUIRE(locke.getExp() == 0);
}

TEST_CASE("locke-getMaxHp") {
    Locke locke;
    REQUIRE(locke.getMaxHp() == 45);
}

TEST_CASE("locke-getCurrentHp") {
    Locke locke;
    REQUIRE(locke.getCurrentHp() == 45);
}

TEST_CASE("locke-setCurrentHp") {
    Locke locke;
    locke.setCurrentHp(40);
    REQUIRE(locke.getCurrentHp() == 40);
}

TEST_CASE("locke-getAtk") {
    Locke locke;
    REQUIRE(locke.getAtk() == 15);
}

TEST_CASE("locke-getDef") {
    Locke locke;
    REQUIRE(locke.getDef() == 25);
}

TEST_CASE("locke-takeDamage") {
    Locke locke;
    locke.takeDamage(10);
    REQUIRE(locke.getCurrentHp() == 37);
}

TEST_CASE("locke-gainExp") {
    Locke locke;
    locke.gainExp(10);
    REQUIRE(locke.getExp() == 10);
}

TEST_CASE("locke-isDead") {
    Locke locke;
    REQUIRE(!locke.isDead());
}

TEST_CASE("terra-getLv") {
    Terra terra;
    REQUIRE(terra.getLv() == 1);
}

TEST_CASE("terra-getExp") {
    Terra terra;
    REQUIRE(terra.getExp() == 0);
}

TEST_CASE("terra-getMaxHp") {
    Terra terra;
    REQUIRE(terra.getMaxHp() == 40);
}

TEST_CASE("terra-getCurrentHp") {
    Terra terra;
    REQUIRE(terra.getCurrentHp() == 40);
}

TEST_CASE("terra-setCurrentHp") {
    Terra terra;
    terra.setCurrentHp(30);
    REQUIRE(terra.getCurrentHp() == 30);
}

TEST_CASE("terra-getAtk") {
    Terra terra;
    REQUIRE(terra.getAtk() == 20);
}

TEST_CASE("terra-getDef") {
    Terra terra;
    REQUIRE(terra.getDef() == 20);
}

TEST_CASE("terra-takeDamage") {
    Terra terra;
    terra.takeDamage(10);
    REQUIRE(terra.getCurrentHp() == 32);
}

TEST_CASE("terra-gainExp") {
    Terra terra;
    terra.gainExp(10);
    REQUIRE(terra.getExp() == 10);
}

TEST_CASE("terra-isDead") {
    Terra terra;
    REQUIRE(!terra.isDead());
}

