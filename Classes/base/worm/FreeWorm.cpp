//
//  FreeWorm.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#include "FreeWorm.h"
#include "PlayGround.h"
#include "Yuan.h"
USING_NS_CC;

FreeWorm::FreeWorm()
:_randomTurn(0.0f)
{
    for (short i = 0; i != WORM_FREE_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

FreeWorm::~FreeWorm()
{
    for (short i = 0; i != WORM_FREE_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

bool FreeWorm::init()
{
    if (!Worm::init()) {
        return false;
    }
    
    _config->setNormalSpeed(600);
    _config->setComboSpeed(400);
    _config->setRunawaySpeed(300);
    _config->setComboLast(5000);
    _config->setConsume(0);
    _config->setEnergy(1000);
    
    return true;
}

void FreeWorm::update(float delta)
{
    if (_playGround == nullptr) return;
    
    // refresh pos
    for (short i = 0; i != WORM_FREE_YUAN_COUNT; ++i) {
        _yuans[i]->setPosition(_playGround->getGridPosAt(_yuans[i]->getNowPos()));
    }
    
    // crawl
    if (isCrawling()) {
        _add += (delta * 1000);
        if (_add >= _property->getSpeed())
        {
            _add = 0.0f;
            doCrawl();
        }
    }
    
    // auto turn
    _randomTurn += (delta * 1000);
    int random = 8000 + CCRANDOM_0_1() * 4000;
    if (_randomTurn >= random) {
        _randomTurn = 0.0f;
        autoTurn();
    }
}

void FreeWorm::born(PlayGround *playGround, start_point start)
{
    if (playGround == nullptr) {
        return;
    }
    
    playGround->addChild(this);
    CC_SAFE_RETAIN(this);
    playGround->getObserver()->setFocusWorm(this);
    
    setPlayGround(playGround);
    
    Color3B colors[WORM_FREE_YUAN_COUNT] = {
        Color3B(30, 104, 35),
        Color3B(68, 163, 64),
        Color3B(140, 198, 101),
        Color3B(214, 230, 133),
        Color3B(208, 208, 208)
    };
    
    for (short i = 0; i != WORM_FREE_YUAN_COUNT; ++i) {
        
        auto yuan = Yuan::create();
        yuan->setGridColor(colors[i]);
        yuan->setGridStartPos(start.info);
        _yuans[i] = yuan;
        
        this->addChild(yuan, (WORM_FREE_YUAN_COUNT - i), i);
    }
    
    _property->setDirection(start.direction);
    _property->setComboLave(0.0f);
    _property->setEnergy(_config->getEnergy());
    
    Worm::born(playGround, start);
    
    this->scheduleUpdate();     // begin update
}

void FreeWorm::die()
{
    Worm::die();
    
    this->unscheduleUpdate();
}

void FreeWorm::doCrawl()
{
    row_col info = _yuans[0]->getNowPos();
    row_col mapSize = _playGround->getPlayGroundSize();
    
    switch (_property->getDirection()) {
        case WORM_DIRECTION_NORTH:
            info.col++;
            break;
        case WORM_DIRECTION_EAST:
            info.row++;
            break;
        case WORM_DIRECTION_SOUTH:
            info.col--;
            break;
        case WORM_DIRECTION_WEST:
            info.row--;
            break;
        default:
            break;
    }
    
    if (info.row >= mapSize.row) {
        info.row = 0;
    }
    
    if (info.row < 0) {
        info.row = mapSize.row - 1;
    }
    
    if (info.col >= mapSize.col) {
        info.col = 0;
    }
    
    if (info.col < 0) {
        info.col = mapSize.col - 1;
    }
    
    _yuans[0]->setGridPos(info);
    _playGround->setFocusPoint(info, _property->getSpeed());
    
    for (short i = 1; i != WORM_FREE_YUAN_COUNT; ++i) {
        _yuans[i]->setGridPos(_yuans[i - 1]->getFromPos());
    }
    
    // consume energy
    consume();
    
    // refresh status
    refreshStatus();
}

row_col FreeWorm::getPos()
{
    if (_yuans[0]) {
        return _yuans[0]->getNowPos();
    }
    
    return Worm::getPos();
}

void FreeWorm::autoTurn()
{
    short add;
    if (CCRANDOM_MINUS1_1() >= 0) {
        add = 1;
    } else {
        add = -1;
    }
    
    short dir = _property->getDirection() + add;
    if (dir < 0) {
        dir = WORM_DIRECTION_WEST;
    }
    
    if (dir > WORM_DIRECTION_WEST) {
        dir = WORM_DIRECTION_NORTH;
    }
    
    turn(dir);
}