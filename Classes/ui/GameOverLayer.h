//
//  GameOverLayer.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__GameOverLayer__
#define __DigitalWorm__GameOverLayer__

#include "BaseLayer.h"

class GameOverLayer : public BaseLayer
{
public:
    GameOverLayer();
    ~GameOverLayer();
    
    CREATE_FUNC(GameOverLayer);
    
    virtual bool            init();
    virtual short           getType();
    
public:
    void                    display();
    void                    displayContent();
    void                    displayScore(cocos2d::Node* parent);
    cocos2d::MenuItem*      displayRestartBtn();
    cocos2d::MenuItem*      displayGameCenterBtn();
    
    void                    onClickRestart(cocos2d::Ref* sender);
    void                    onClickGameCenter(cocos2d::Ref* sender);
    
protected:
    
};

#endif /* defined(__DigitalWorm__GameOverLayer__) */
