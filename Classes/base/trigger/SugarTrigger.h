//
//  SugarTrigger.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#ifndef __DigitalWorm__SugarTrigger__
#define __DigitalWorm__SugarTrigger__

#include "Trigger.h"

#define TRIGGER_SUGAR_YUAN_COUNT     2

class Yuan;
class SugarTrigger : public Trigger
{
public:
    SugarTrigger();
    ~SugarTrigger();
    
    CREATE_FUNC(SugarTrigger);
    
    virtual bool    init();
    
public:
    virtual short   getType();
    virtual void    addTo(PlayGround* playGround, row_col pos);
    virtual void    effect();
    virtual void    uneffect(Node* node);
    
    virtual void    onTrigger();
    
    virtual row_col getPos();
    virtual short   getEnergy() {return 100;};
    
    virtual void    focus();
    virtual void    blur();
    
protected:
    Yuan*           _yuans[TRIGGER_SUGAR_YUAN_COUNT];
    
};

#endif /* defined(__DigitalWorm__SugarTrigger__) */
