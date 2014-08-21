//
//  MenuScene.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__MenuScene__
#define __DigitalWorm__MenuScene__

#include "BaseLayer.h"

class FreePlayGround;
class MenuScene : public BaseLayer
{
public:
    MenuScene();
    ~MenuScene();
    
    CREATE_FUNC(MenuScene);
    
    static cocos2d::Scene*  createScene();
    
    virtual bool            init();
    virtual short           getType();
    
public:
    void                    display();
    cocos2d::MenuItem*      displayPlayBtn();
    cocos2d::MenuItem*      displayGameCenterBtn();
    void                    displayWorm();
    
    void                    onClickPlay(cocos2d::Ref* sender);
    void                    onClickGameCenter(cocos2d::Ref* sender);
    
    void                    changeScene();
    
protected:
    CC_SYNTHESIZE(FreePlayGround*, _playGround, PlayGround);
    
};

#endif /* defined(__DigitalWorm__MenuScene__) */
