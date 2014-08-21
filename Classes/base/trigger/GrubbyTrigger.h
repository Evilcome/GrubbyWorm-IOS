//
//  GrubbyTrigger.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#ifndef __DigitalWorm__GrubbyTrigger__
#define __DigitalWorm__GrubbyTrigger__

#include "Trigger.h"

#define TRIGGER_GRUBBY_YUAN_COUNT     2

class Yuan;
class GrubbyTrigger : public Trigger
{
public:
    GrubbyTrigger();
    ~GrubbyTrigger();
    
    CREATE_FUNC(GrubbyTrigger);
    
    virtual bool    init();
    
public:
    virtual short   getType();
    virtual void    addTo(PlayGround* playGround, row_col pos);
    virtual void    effect();
    virtual void    uneffect(Node* node);
    
    virtual void    onTrigger();
    
    virtual row_col getPos();
    virtual short   getEnergy() {return -100;};
    
protected:
    Yuan*           _yuans[TRIGGER_GRUBBY_YUAN_COUNT];
    
};

#endif /* defined(__DigitalWorm__GrubbyTrigger__) */
