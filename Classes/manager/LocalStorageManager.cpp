//
//  LocalStorageManager.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-30.
//
//

#include "LocalStorageManager.h"
USING_NS_CC;

LocalStorageManager::LocalStorageManager()
{
    
}

LocalStorageManager::~LocalStorageManager()
{
    
}

LocalStorageManager* LocalStorageManager::_instance = nullptr;

LocalStorageManager* LocalStorageManager::getInstance()
{
    if (_instance == nullptr) {
        _instance = new LocalStorageManager();
    }
    
    return _instance;
}

void LocalStorageManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
}

bool LocalStorageManager::isNewer()
{
    return UserDefault::getInstance()->getBoolForKey(LS_BOOL_NEWER);
}

void LocalStorageManager::setBestScore(int value)
{
    UserDefault::getInstance()->setIntegerForKey(LS_INT_BEST_SCORE, value);
}

int LocalStorageManager::getBestScore()
{
    return UserDefault::getInstance()->getIntegerForKey(LS_INT_BEST_SCORE, 0);
}