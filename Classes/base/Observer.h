//
//  Observer.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#ifndef __DigitalWorm__Observer__
#define __DigitalWorm__Observer__

#include "cocos2d.h"
#include "StructDefine.h"
#include "King.h"

class Trigger;
class Worm;
class PlayGround;
class Observer : public cocos2d::Ref
{
public:
    Observer();
    ~Observer();
    
    CREATE_FUNC(Observer);
    
    virtual bool                init();
    
public:
    virtual void                cameraFocus(int speed);
    virtual void                setFocusPoint(row_col point);
    virtual row_col             getFocusPoint();
    
    virtual void                onFocusPointChange();
    
    cocos2d::Vector<Trigger* >& getTriggers();
    virtual void                addTrigger(Trigger* trigger);
    virtual void                removeTrigger(Trigger* trigger);
    
    virtual short               getSugerCount();
    
    virtual void                showColorTip(const cocos2d::Color3B& color);
    
protected:
    row_col                     _focusPoint;
    cocos2d::Vector<Trigger* >  _triggers;
    CC_SYNTHESIZE(PlayGround*, _playGround, PlayGround);
    CC_SYNTHESIZE(Worm*, _focusWorm, FocusWorm);
    CC_SYNTHESIZE(King*, _king, King);
    
};

#endif /* defined(__DigitalWorm__Observer__) */
