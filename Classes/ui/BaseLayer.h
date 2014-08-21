//
//  BaseLayer.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__BaseLayer__
#define __DigitalWorm__BaseLayer__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

enum LAYER_TYPE{
    LAYER_BASE = 0,
    LAYER_MENU,
    LAYER_PAUSE,
    LAYER_GAME_OVER,
    LAYER_PLAY,
    LAYER_GAME,
    LAYER_MAX
};

class BaseLayer : public cocos2d::Layer
{
public:
    BaseLayer();
    ~BaseLayer();
    
    CREATE_FUNC(BaseLayer);
    
    virtual bool    init();
    
public:
    virtual short   getType();
    
};

#endif /* defined(__DigitalWorm__BaseLayer__) */
