//
//  King.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-24.
//
//

#ifndef __DigitalWorm__King__
#define __DigitalWorm__King__

#include "cocos2d.h"
#include "StructDefine.h"

#define CREATE_TRIGGER_DELAY    1200
#define EXIST_TRIGGER_DENSITY     20

#define SUGAR_TRIGGER_COUNT       15

class Observer;
class SugarTrigger;
class King : public cocos2d::Ref
{
public:
    King();
    ~King();
    
    CREATE_FUNC(King);
    
    virtual bool    init();
    
public:
    virtual void        monitor(float delta);
    virtual bool        createTrigger(short type, row_col point);
    virtual bool        isEmptyPos(row_col point);
    
    virtual short       expectSugarCount();
    virtual void        addSuger();
    virtual void        colorRule(SugarTrigger* sugar);
    
    virtual row_col     getRandomEmptyPos();
    
    virtual void        supplementSugarFormation(cocos2d::Color3B& color);
    
protected:
    void                _initSugarFormation();
    row_col             _getRandomValue(std::vector<row_col> &points, row_col &size, row_col from = {0, 0});
    row_col_range       _getFixSize(row_col point);
    
    float               _add;
    std::vector<short>  _sugarFormation;
    
    CC_SYNTHESIZE(Observer*, _observer, Observer);
    
};

#endif /* defined(__DigitalWorm__King__) */
