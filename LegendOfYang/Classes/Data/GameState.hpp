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
    static GameState *defaultInstance;
    ValueMap state;
};
