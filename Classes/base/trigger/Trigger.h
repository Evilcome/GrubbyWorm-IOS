//
//  Trigger.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#ifndef __DigitalWorm__Trigger__
#define __DigitalWorm__Trigger__

#include "cocos2d.h"
#include "StructDefine.h"
#include "Observer.h"
#include "PlayGround.h"
#include "SimpleAudioEngine.h"
#include "Common.h"
#include "FAManager.h"
#include "GameManager.h"

using namespace CocosDenshion;

enum TRIGGER_TYPE {
    TRIGGER_TYPE_BASE = -1,
    TRIGGER_TYPE_SUGAR = 0,
    TRIGGER_TYPE_HONEY,
    TRIGGER_TYPE_GRUBBY,
    TRIGGER_TYPE_WALL
};

class PlayGround;
class Trigger : public cocos2d::Node
{
public:
    Trigger();
    ~Trigger();
    
    CREATE_FUNC(Trigger);
    
    virtual bool    init();
    
public:
    virtual short   getType();
    virtual void    addTo(PlayGround* playGround, row_col pos);
    virtual void    effect();
    virtual void    destroy();
    virtual void    onTrigger() {};
    
    virtual row_col getPos();
    virtual short   getEnergy();
    
    virtual void    setIncubated(bool incubate);
    virtual bool    isIncubated();
    
    virtual void    focus();
    virtual void    blur();
    
    virtual void    setFocus(bool focus);
    virtual bool    isFocusd();
    
protected:
    CC_SYNTHESIZE(PlayGround*, _playGround, PlayGround);
    CC_SYNTHESIZE(cocos2d::Color3B, _color, SugarColor);
    bool            _incubated;
    bool            _focus;
    
};

#endif /* defined(__DigitalWorm__Trigger__) */
