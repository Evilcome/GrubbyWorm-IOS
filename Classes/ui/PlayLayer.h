//
//  PlayLayer.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__PlayLayer__
#define __DigitalWorm__PlayLayer__

#include "BaseLayer.h"

class PlayLayer : public BaseLayer
{
public:
    PlayLayer();
    ~PlayLayer();
    
    CREATE_FUNC(PlayLayer);
    
    virtual bool    init();
    virtual short   getType();
    
public:
    void            display();
    void            displayHappy();
    void            displayCrazy();
    
    void            refreshScore(cocos2d::Ref* sender);
    void            refreshEnergy(cocos2d::Ref* sender);
    void            refreshComboLast(cocos2d::Ref* sender);
    void            refreshCrazyLast(cocos2d::Ref* sender);
    
    void            onClickPause(Ref* sender);
    
protected:
    
};

#endif /* defined(__DigitalWorm__PlayLayer__) */
