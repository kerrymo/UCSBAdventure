//
//  OverworldScene.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/7/18.
//

#pragma once
USING_NS_CC;
#include "Entity.hpp"
#include "YangPhysics.hpp"
#include "EntityCreator.hpp"

class OverworldScene : public Scene {
public:
    virtual bool init() override;
    static Scene* createWithTileMap(std::string filename);
    void guiChildrenChanged(EventCustom *event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void update(float delta) override;
    virtual void onExitTransitionDidStart() override;
    virtual void onEnter() override;
    
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(OverworldScene);
    YangPhysics *physics;
    
protected:
    Vec2 tileCoordForPosition(Vec2 position);
    Entity *player;
    Node *gui, *world;
    TMXTiledMap *tileMap;
    TMXLayer *meta; // Contains collision information
    bool heldKey[200];
    
};
