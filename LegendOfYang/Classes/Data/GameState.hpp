//
//  GameState.hpp
//  LegendOfYang
//
//  Created by John Rehbein on 3/7/18.
//

#pragma once
#include <unordered_map>
USING_NS_CC;

class GameState {
public:
    /**
     Singleton reference
     */
    static GameState *defaultInstance;
    
    /**
     Key value map that stores the state of the gameworld.
     i.e. chests set flags about whether or not they’ve been opened.
     */
    ValueMap state;
};
