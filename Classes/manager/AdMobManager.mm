//
//  AdMobManager.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//
#import <UIKit/UIKit.h>

#include "AdMobManager.h"
#import "GADBannerView.h"
USING_NS_CC;

AdMobManager::AdMobManager()
:_view(nullptr)
,_visible(false)
{
    
}

AdMobManager::~AdMobManager()
{
    
}

AdMobManager* AdMobManager::_instance = nullptr;

AdMobManager* AdMobManager::getInstance()
{
    if (_instance == nullptr) {
        _instance = new AdMobManager();
    }
    
    return _instance;
}

void AdMobManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
}

void AdMobManager::setBannerView(void *view)
{
    _view = view;
}

void AdMobManager::setBannerViewVisible(bool visible)
{
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        GADBannerView* bannerAd = (GADBannerView*)_view;
        if (bannerAd) {
            if (visible) {
                [bannerAd setHidden:NO];
            } else {
                [bannerAd setHidden:YES];
            }
        }
    }
}

bool AdMobManager::isBannerViewVisible()
{
    return _visible;
}