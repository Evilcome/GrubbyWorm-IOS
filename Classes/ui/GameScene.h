//
//  GameScene.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__GameScene__
#define __DigitalWorm__GameScene__

#include "BaseLayer.h"

class PlayGround;
class GameScene : public BaseLayer
{
public:
    GameScene();
    ~GameScene();
    
    CREATE_FUNC(GameScene);
    
    static cocos2d::Scene*  createScene();
    
    virtual bool            init();
    virtual short           getType();
    
public:
    void                    display();
    void                    pause();
    void                    play();
    void                    over();
    
    void                    onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

protected:
    CC_SYNTHESIZE(PlayGround*, _playGround, PlayGround);
    
};

#endif /* defined(__DigitalWorm__GameScene__) */
