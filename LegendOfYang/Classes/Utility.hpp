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

// Description : Gives the intersection of two rectangles
// Precondition : r1 and r2 intersect
static Rect intersectionOfRectangles(Rect r1, Rect r2);

// Description : Given a position and a tilemap gives you a corresponding tile coordinate
// Precondition : The coordinate may be out of bounds
// Postcondition : if the position is out of bounds of the tilemap the coordinate will be out of bounds of the tile map.
// If the coordinate is within bounds then the tile coordinate will be within the bounds of the tilemap.
Vec2 tileCoordForPosition(Vec2 position, TMXTiledMap *tileMap);

Vec2 randomDirection();
