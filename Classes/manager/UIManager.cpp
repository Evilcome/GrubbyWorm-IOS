//
//  UIManager.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#include "UIManager.h"
USING_NS_CC;

UIManager::UIManager()
{
    for (short i = 0; i != LAYER_MAX; ++i) {
        _cache[i] = nullptr;
    }
}

UIManager::~UIManager()
{
    for (short i = 0; i != LAYER_MAX; ++i) {
        _cache[i] = nullptr;
    }
}

UIManager* UIManager::_instance = nullptr;

UIManager* UIManager::getInstance()
{
    if (_instance == nullptr) {
        _instance = new UIManager();
    }
    
    return _instance;
}

void UIManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
}

Scene* UIManager::getRunningScene()
{
    return Director::getInstance()->getRunningScene();
}

void UIManager::inject(BaseLayer* layer)
{
    _cache[layer->getType()] = layer;
}

BaseLayer* UIManager::find(short type)
{
    return _cache[type];
}

void UIManager::erase(short type)
{
    _cache[type] = nullptr;
}



