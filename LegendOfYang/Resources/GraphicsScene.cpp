//
//  GraphicsScene.cpp
//  LegendOfYang
//
//  Created by SITAO CHEN on 2/6/18.
//
//

#include "GraphicsScene.hpp"

USING_NS_CC;

Scene* GraphicsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GraphicsScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GraphicsScene::init()
{
    if( !Layer::init())
        
    {
        return false;
    }
    
    auto sprite = Sprite::create("sprite.png");
    sprite->setPosition(0,0);
    
    this->addChild(sprite,0);
    
    auto sprite = Sprite::create("coin_01.png");
    sprite->setPosition(0,0);
    
    this->addChild(sprite,0);
    
    auto sprite = Sprite::create("character.png");
    sprite->setPosition(0,0);
    
    this->addChild(sprite,0);
    return true;
}
