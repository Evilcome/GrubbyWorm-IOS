//
//  FreeWorm.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#ifndef __DigitalWorm__FreeWorm__
#define __DigitalWorm__FreeWorm__

#include "Worm.h"

#define WORM_FREE_YUAN_COUNT     5

class Yuan;
class FreeWorm : public Worm
{
public:
    FreeWorm();
    ~FreeWorm();
    
    CREATE_FUNC(FreeWorm);
    
    virtual bool    init();
    virtual void    update(float delta) override;
    
public:
    virtual void    born(PlayGround* playGround, start_point start);
    virtual void    die();
    virtual void    doCrawl();
    virtual row_col getPos();
    
    void            autoTurn();
    
protected:
    Yuan*           _yuans[WORM_FREE_YUAN_COUNT];
    float           _randomTurn;
    
};

#endif /* defined(__DigitalWorm__FreeWorm__) */
