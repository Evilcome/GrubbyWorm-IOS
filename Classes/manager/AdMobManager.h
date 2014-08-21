//
//  AdMobManager.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#ifndef __DigitalWorm__AdMobManager__
#define __DigitalWorm__AdMobManager__

#include "cocos2d.h"

#define ADMOB_MGR              AdMobManager::getInstance()

class AdMobManager : public cocos2d::Ref
{
public:
    AdMobManager();
    ~AdMobManager();
    
    static AdMobManager*        getInstance();
    void                        destoryInstance();
    
public:
    void                        setBannerView(void* view);
    void                        setBannerViewVisible(bool visible);
    bool                        isBannerViewVisible();
    
protected:
    static AdMobManager*        _instance;
    void*                       _view;
    bool                        _visible;
    
};

#endif /* defined(__DigitalWorm__AdMobManager__) */
