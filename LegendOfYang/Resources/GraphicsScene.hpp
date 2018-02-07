//
//  GraphicsScene.hpp
//  LegendOfYang
//
//  Created by SITAO CHEN on 2/6/18.
//
//

#ifndef GraphicsScene_hpp
#define GraphicsScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class GraphicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GraphicsScene);
};

#endif /* GraphicsScene_hpp */
