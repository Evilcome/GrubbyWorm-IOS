//
//  Worm.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-18.
//
//

#include "Worm.h"
#include "GameManager.h"
USING_NS_CC;

Worm::Worm()
:_playGround(nullptr)
,_crawling(false)
,_add(0.0f)
,_config(nullptr)
,_property(nullptr)
,_status(WORM_STATUS_STOP)
,_unrivalled(false)
{
    
}

Worm::~Worm()
{
    _playGround = nullptr;
    
    CC_SAFE_DELETE(_config);
    CC_SAFE_DELETE(_property);
}

bool Worm::init()
{
    if (!Node::init()) {
        return false;
    }
    
    _config = new WormConfig();
    _property = new WormProperty();
    
    return true;
}

void Worm::born(PlayGround *playGround, start_point start)
{
    setStatus(WORM_STATUS_NORMAL);
}

void Worm::turn(short direction)
{
    if (_property->getDirection() == direction) {
        return;
    }
    
    _property->setDirection(direction);
    _add = 0.0f;
    doCrawl();
}

void Worm::setStatus(short status)
{
    if (_status == status) return;
    
    //log("worm status -> %d", status);
    
    if (status == WORM_STATUS_RUNAWAY) {
        _property->setRunawayLave(_config->getRunawayLast());
        _prepareRunaway();
    }
    
    _status = status;
    switch (status) {
        case WORM_STATUS_DIE:
            _property->setSpeed(0);
            break;
        case WORM_STATUS_STOP:
            _property->setSpeed(0);
            break;
        case WORM_STATUS_NORMAL:
            _property->setSpeed(_config->getNormalSpeed());
            break;
        case WORM_STATUS_COMBO:
            _property->setSpeed(_config->getComboSpeed());
            break;
        case WORM_STATUS_RUNAWAY:
            _property->setSpeed(_config->getRunawaySpeed());
            break;
        default:
            break;
    }
    
    refreshView();
}

void Worm::consume()
{
    if (_unrivalled) {
        return;
    }
    
    short consume = _config->getConsume();
    _property->setEnergy(_property->getEnergy() - consume);
}

void Worm::refreshStatus()
{
    int combo = GAME_MGR->getScore().combo;
    
    if (combo > 0) {
        if (combo >= _config->getRunawayCount()) {
            setStatus(WORM_STATUS_RUNAWAY);
        } else {
            setStatus(WORM_STATUS_COMBO);
        }
    } else {
        setStatus(WORM_STATUS_NORMAL);
    }
}

void Worm::eat(short energy)
{
    if (_unrivalled) {
        return;
    }
    
    short e = _property->getEnergy() + energy;
    e > _config->getEnergy() ? e = _config->getEnergy() : e = e;
    _property->setEnergy(e);
}

void Worm::fullEnergy()
{
    _property->setEnergy(_config->getEnergy());
}

void Worm::emptyEnergy()
{
    if (_unrivalled) {
        return;
    }
    
    _property->setEnergy(0);
}

row_col Worm::getPos()
{
    return {-1, -1};
}

void Worm::removeTarget(cocos2d::Node *target)
{
    if (target) {
        target->removeFromParentAndCleanup(true);
    }
}
