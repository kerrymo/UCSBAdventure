//
//  OverworldScene.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/7/18.
//

#pragma once
USING_NS_CC;
#include <unordered_set>

class OverworldScene : public Scene {
public:
    virtual bool init() override;
    static Scene* createWithTileMap(std::string filename);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    void update(float delta) override;
    // create a create() function that calls constructor, init and autorelease
    CREATE_FUNC(OverworldScene);
    
protected:
    Vec2 tileCoordForPosition(Vec2 position);
    
    Node *player;
    Node *gui, *world;
    TMXTiledMap *tileMap;
    TMXLayer *meta; // Contains collision information
    bool heldKey[200];
    EventListenerKeyboard *keyboardListener;
    
};
