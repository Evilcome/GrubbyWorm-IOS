//
//  FreePlayGround.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#ifndef __DigitalWorm__FreePlayGround__
#define __DigitalWorm__FreePlayGround__

#include "PlayGround.h"

class FreePlayGround : public PlayGround
{
public:
    FreePlayGround();
    ~FreePlayGround();
    
    CREATE_FUNC(FreePlayGround);
    
    virtual bool            init();
    virtual void            update(float delta) override;
    
public:
    virtual void            create(row_col info);
    virtual void            setFocusPoint(row_col point, int speed);
    void                    removeMask();
    void                    setFocus(bool focus);
    
protected:
    void                    _removeMask(cocos2d::Node* node);
    bool                    _focus;
    
};

#endif /* defined(__DigitalWorm__FreePlayGround__) */
