//
//  Worm.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-18.
//
//

#ifndef __DigitalWorm__Worm__
#define __DigitalWorm__Worm__

#include "cocos2d.h"
#include "StructDefine.h"
#include "Observer.h"
#include "Trigger.h"
#include "ConfigStruct.h"
#include "PropertyStruct.h"
#include "Common.h"

enum WORM_DIRECTION {
    WORM_DIRECTION_INVLID = -1,
    WORM_DIRECTION_NORTH = 0,
    WORM_DIRECTION_EAST,
    WORM_DIRECTION_SOUTH,
    WORM_DIRECTION_WEST
};

enum WORM_STATUS {
    WORM_STATUS_DIE = -1,
    WORM_STATUS_STOP = 0,
    WORM_STATUS_NORMAL,
    WORM_STATUS_COMBO,
    WORM_STATUS_RUNAWAY
};

class PlayGround;
class Worm : public cocos2d::Node
{
public:
    Worm();
    ~Worm();
    
    virtual bool init();
    
    CREATE_FUNC(Worm);
    
public:
    virtual void    born(PlayGround* playGround, start_point start);
    virtual void    crawl() {setCrawling(true);};
    virtual void    turn(short direction);
    virtual void    stop() {};
    virtual void    die() {setCrawling(false);setStatus(WORM_STATUS_DIE);};
    virtual void    doDie() {};
    
    virtual bool    isCrawling() {return (_crawling && _property->getSpeed() != 0);};
    virtual void    setCrawling(bool crawl) {_crawling = crawl;};
    
    virtual void    doCrawl() {};
    
    virtual void    onTrigger(Trigger* trigger) {};
    virtual void    setStatus(short status);
    virtual void    refreshView() {};
    
    virtual void    consume();
    virtual void    refreshStatus();
    virtual void    eat(short energy);
    virtual void    fullEnergy();
    virtual void    emptyEnergy();
    
    virtual row_col getPos();
    
    virtual void    setUnrivalled(bool unr) {_unrivalled = unr;};
    virtual bool    isUnrivalled() {return _unrivalled;};
    
public:
    virtual void    removeTarget(Node* target);
    
protected:
    virtual void    _prepareRunaway() {};
    virtual void    _runawayPrepared() {};
    
    CC_SYNTHESIZE(PlayGround*, _playGround, PlayGround);
    CC_SYNTHESIZE(WormConfig*, _config, Config);
    CC_SYNTHESIZE(WormProperty*, _property, Property);
    CC_SYNTHESIZE_READONLY(short, _status, Status);
    
    bool            _crawling;
    float           _add;
    bool            _unrivalled;
    
};

#endif /* defined(__DigitalWorm__Worm__) */
