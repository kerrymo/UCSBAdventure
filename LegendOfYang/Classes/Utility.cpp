//
//  Utility.cpp
//  LegendOfYang
//
//  Created by John Rehbein on 2/9/18.
//

#include "Utility.hpp"

static Rect intersectionOfRectangles(Rect r1, Rect r2) {
    using namespace std;
    Rect intersection;
    intersection = Rect(max(r1.getMinX(),r2.getMinX()), max(r1.getMinY(), r2.getMinY()),0,0);
    intersection.size.width = min(r1.getMaxX(), r2.getMaxX()) - intersection.getMinX();
    intersection.size.height = min(r1.getMaxY(), r2.getMaxY()) - intersection.getMinY();
    return intersection;
}

Vec2 tileCoordForPosition(Vec2 position, TMXTiledMap *tileMap) {
    Size tileSize = tileMap->getTileSize();
    int x = position.x / tileSize.width;
    int y = ((tileMap->getMapSize().height * tileSize.height) - position.y) / tileSize.height;
    return Vec2(x, y);
}

Vec2 randomDirection() {
    Vec2 rvec = Vec2(RandomHelper::random_real(-1.0f, 1.0f), RandomHelper::random_real(-1.0f, 1.0f));
    rvec.normalize();
    return rvec;
}
