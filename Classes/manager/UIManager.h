//
//  UIManager.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__UIManager__
#define __DigitalWorm__UIManager__

#include "cocos2d.h"
#include "BaseLayer.h"

#define UI_MGR              UIManager::getInstance()

class UIManager : public cocos2d::Ref
{
public:
    UIManager();
    ~UIManager();
    
    static UIManager*               getInstance();
    void                            destoryInstance();
    
public:
    cocos2d::Scene*                 getRunningScene();
    void                            inject(BaseLayer* layer);
    BaseLayer*                      find(short type);
    void                            erase(short type);
    
protected:
    static UIManager*               _instance;
    BaseLayer*                      _cache[LAYER_MAX];
    
};

#endif /* defined(__DigitalWorm__UIManager__) */
