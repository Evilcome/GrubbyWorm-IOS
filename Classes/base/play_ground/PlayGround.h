//
//  PlayGround.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-18.
//
//

#ifndef __DigitalWorm__PlayGround__
#define __DigitalWorm__PlayGround__

#include "cocos2d.h"
#include "StructDefine.h"

class Observer;
class Worm;
class PlayGround : public cocos2d::Layer
{
public:
    PlayGround();
    ~PlayGround();
    
    CREATE_FUNC(PlayGround);
    
    virtual bool            init();
    virtual void            update(float delta) override;
    
public:
    virtual void            create(row_col info);
    virtual void            setFocusPoint(row_col point, int speed);
    
    void                    insertDict(cocos2d::Sprite* grid, row_col info);
    
    cocos2d::Sprite*        getGridAt(row_col info);
    const cocos2d::Vec2&    getGridPosAt(row_col info);

    Worm*                   getFocusWorm();
    
    void                    showAdd(int add);
    void                    hideAdd();
    
protected:
    CC_SYNTHESIZE(row_col, _info, PlayGroundSize);
    CC_SYNTHESIZE(Observer*, _observer, Observer);
    
};

#endif /* defined(__DigitalWorm__PlayGround__) */
