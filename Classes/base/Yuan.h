//
//  Yuan.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-21.
//
//

#ifndef __DigitalWorm__Yuan__
#define __DigitalWorm__Yuan__

#include "cocos2d.h"
#include "StructDefine.h"

class Yuan : public cocos2d::Node
{
public:
    Yuan();
    ~Yuan();
    CREATE_FUNC(Yuan);
    
    virtual bool                        init();
    
public:
    virtual void                        setGridColor(const cocos2d::Color3B& color);
    virtual const cocos2d::Color3B&     getGridColor();
    virtual void                        setGridStartPos(row_col pos);
    virtual void                        setGridPos(row_col pos);

protected:
    CC_SYNTHESIZE(cocos2d::Sprite*, _grid, Grid);
    CC_SYNTHESIZE(row_col, _nowPos, NowPos);
    CC_SYNTHESIZE(row_col, _fromPos, FromPos);
    
};

#endif /* defined(__DigitalWorm__Yuan__) */
