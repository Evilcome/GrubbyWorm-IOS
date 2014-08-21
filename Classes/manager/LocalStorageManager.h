//
//  LocalStorageManager.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-30.
//
//

#ifndef __DigitalWorm__LocalStorageManager__
#define __DigitalWorm__LocalStorageManager__

#include "cocos2d.h"

#define LS_MGR              LocalStorageManager::getInstance()

#define LS_INT_BEST_SCORE   "best_score"
#define LS_BOOL_NEWER       "is_newer"

class LocalStorageManager : public cocos2d::Ref
{
public:
    LocalStorageManager();
    ~LocalStorageManager();
    
    static LocalStorageManager*         getInstance();
    void                                destoryInstance();
    
public:
    bool                                isNewer();
    void                                setBestScore(int value);
    int                                 getBestScore();
    
protected:
    static LocalStorageManager*         _instance;
    
};

#endif /* defined(__DigitalWorm__LocalStorageManager__) */
