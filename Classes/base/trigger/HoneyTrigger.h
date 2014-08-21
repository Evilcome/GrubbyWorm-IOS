//
//  HoneyTrigger.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#ifndef __DigitalWorm__HoneyTrigger__
#define __DigitalWorm__HoneyTrigger__

#include "Trigger.h"

#define TRIGGER_HONEY_YUAN_COUNT     2

class Yuan;
class HoneyTrigger : public Trigger
{
public:
    HoneyTrigger();
    ~HoneyTrigger();
    
    CREATE_FUNC(HoneyTrigger);
    
    virtual bool    init();
    
public:
    virtual short   getType();
    virtual void    addTo(PlayGround* playGround, row_col pos);
    virtual void    effect();
    virtual void    uneffect(Node* node);
    
    virtual void    onTrigger();
    
    virtual row_col getPos();
    virtual short   getEnergy() {return 400;};
    
    void            alwaysFocus();
    
protected:
    Yuan*           _yuans[TRIGGER_HONEY_YUAN_COUNT];
    
};

#endif /* defined(__DigitalWorm__HoneyTrigger__) */
