//
//  Utility.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/9/18.
//

#pragma once
USING_NS_CC;

enum LoopUpdateOrder { // The order which entries are layed out here is the order which they will be updated in game
    LOOP_UPDATE_ORDER_INPUT, // Has integer value 0
    LOOP_UPDATE_ORDER_ENTITY, // Has integer value 1 etc.
    LOOP_UPDATE_ORDER_PHYSICS_WORLD
};

static Rect intersectionOfRectangles(Rect r1, Rect r2);
Vec2 tileCoordForPosition(Vec2 position, TMXTiledMap *tileMap);
