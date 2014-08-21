//
//  GameManager.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#ifndef __DigitalWorm__GameManager__
#define __DigitalWorm__GameManager__

#include "cocos2d.h"
#include "StructDefine.h"

#define NOTI_TRIGGER_VALUE      "NOTI_TRIGGER_VALUE"
#define NOTI_COMBO_VALUE        "NOTI_COMBO_VALUE"
#define NOTI_STEP_VALUE         "NOTI_STEP_VALUE"
#define NOTI_ENERGY_VALUE       "NOTI_ENERGY_VALUE"
#define NOTI_COMBO_LAST         "NOTI_COMBO_LAST"
#define NOTI_TOTAL_VALUE        "NOTI_TOTAL_VALUE"
#define NOTI_RUNAWAY_LAST       "NOTI_RUNAWAY_LAST"

#define GAME_MGR                GameManager::getInstance()

enum GAME_STATUS {
    GAME_STATUS_STANDBY = 0,
    GAME_STATUS_RUNNING,
    GAME_STATUS_PAUSE,
    GAME_STATUS_OVER
};

class GameCenter;
class GameManager : public cocos2d::Ref
{
public:
    GameManager();
    ~GameManager();
    
    static GameManager*     getInstance();
    void                    destoryInstance();
    
public:
    void                    init();
    
    void                    addCombo(short count = 1);
    void                    resetCombo();
    void                    addStep();
    int                     addTrigger(short count = 1);
    void                    setEnergy(count_detail detail);
    
    void                    resetScore(bool refresh = true);
    
    void                    setGameStatus(short status);
    void                    onGameStatusChange();
    
public:
    int                     getPlayerScore();
    int                     getBestScore();
    void                    setBestScore(int value);
    bool                    isNewer();
    
public:
    // operation
    void                    pause();
    void                    play();
    void                    over();
    void                    restart();
    
protected:
    static GameManager*     _instance;
    
    CC_SYNTHESIZE_READONLY(score, _score, Score);
    CC_SYNTHESIZE_READONLY(count_detail, _energy, Energy);
    CC_SYNTHESIZE(GameCenter*, _gameCenter, GameCenter);
    CC_SYNTHESIZE(start_point, _startPoint, StartPoint);
    CC_SYNTHESIZE_READONLY(short, _gameStatus, GameStatus);
    
};

#endif /* defined(__DigitalWorm__GameManager__) */
