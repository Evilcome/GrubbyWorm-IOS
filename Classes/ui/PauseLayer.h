//
//  PauseLayer.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-27.
//
//

#ifndef __DigitalWorm__PauseLayer__
#define __DigitalWorm__PauseLayer__

#include "BaseLayer.h"

class PauseLayer : public BaseLayer
{
public:
    PauseLayer();
    ~PauseLayer();
    
    CREATE_FUNC(PauseLayer);
    
    virtual bool            init();
    virtual short           getType();
    
    void                    display();
    void                    displayContent();
    void                    displayScore(cocos2d::Node* parent);
    cocos2d::MenuItem*      displayPlayBtn();
    cocos2d::MenuItem*      displayRestartBtn();
    cocos2d::MenuItem*      displayGameCenterBtn();
    
    void                    onClickPlay(cocos2d::Ref* sender);
    void                    onClickRestart(cocos2d::Ref* sender);
    void                    onClickGameCenter(cocos2d::Ref* sender);
    
    void                    doClickPlay();
    
protected:
    
};

#endif /* defined(__DigitalWorm__PauseLayer__) */
