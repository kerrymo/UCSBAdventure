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
#include "Item.hpp"

class OverworldScene : public Scene {
    friend class EntityCreator;
    
public:
    // Description : initializes map using the filename of the tilemap
    // Precondition : N / A
    // Postcondition : A fully configured scene according to the contents of the tilemap file
    static OverworldScene* createWithTileMap(std::string filename);
    
    // Description : A hook for a callback function.
    // Postcondition : Pauses the game world when the gui has any member in it unpauses the game world when there is nothing left in the gui
    void guiChildrenChanged(EventCustom *event);
    
    // Description : Callback functions for keyboard events
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    
    // Description : Game world update callback function.
    void update(float delta) override;
    
    // Description : Scene delegate functions. Called whenever there are scene transitions. Used for pausing the game world when transitioning between scenes.
    virtual void onExitTransitionDidStart() override;
    virtual void onEnter() override;
    
    // Description : Follows conventions of cocos and calls alloc and init
    CREATE_FUNC(OverworldScene);
    
    // Description : A pointer to the physics world
    YangPhysics *physics;
    
    // Description : A pointer to the tilemap
    TMXTiledMap *tileMap;
    
    // Description : Contains the name of the world. i.e. The filename of the tilemap without the extension
    std::string worldName;
    
    // Description : A hook to the gui
    Node *gui;
protected:
    EntityCreator *entityCreator;
    Entity *player;
    Node *world;
    TMXLayer *meta; // Contains collision information
    bool heldKey[200];
    
};
