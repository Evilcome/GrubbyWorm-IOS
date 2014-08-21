//
//  Observer.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#include "Observer.h"
#include "PlayGround.h"
#include "GameManager.h"
#include "Trigger.h"
#include "Worm.h"
USING_NS_CC;

Observer::Observer()
:_playGround(nullptr)
,_focusWorm(nullptr)
,_king(nullptr)
{
    
}

Observer::~Observer()
{
    _playGround = nullptr;
    CC_SAFE_RELEASE(_focusWorm);
    CC_SAFE_RELEASE(_king);
}

bool Observer::init()
{
    _focusPoint = {-1, -1};
    
    _king = King::create();
    _king->setObserver(this);
    CC_SAFE_RETAIN(_king);
    
    return true;
}

void Observer::cameraFocus(int speed)
{
    if (_focusPoint.row == -1 && _focusPoint.col == -1) return;
    
    _playGround->stopAllActions();
    Vec2 pos = _playGround->getGridPosAt(_focusPoint) + _playGround->getPosition();
    
    Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    Vec2 center = Vec2(rect.origin.x + rect.size.width / 2, rect.origin.y + rect.size.height / 2);
    
    Vec2 move = _playGround->getPosition() - (pos - center);
    
    // border handle
    Size size = _playGround->getContentSize();
    Size winSize = rect.size;
    
    if (move.x > 0) {
        move.x = 0;
    }
    
    if (move.x < - (size.width - winSize.width)) {
        move.x = - (size.width - winSize.width);
    }
    
    if (move.y > 0) {
        move.y = 0;
    }
    
    if (move.y < - (size.height - winSize.height)) {
        move.y = - (size.height - winSize.height);
    }
    
    auto action = MoveTo::create((float)speed / 800, move);
    _playGround->runAction(action);
}

void Observer::setFocusPoint(row_col point)
{
    _focusPoint = point;
    onFocusPointChange();
}

row_col Observer::getFocusPoint()
{
    return _focusPoint;
}

void Observer::onFocusPointChange()
{
    GAME_MGR->addStep();
    
    // trigger
    for(auto each : _triggers)
    {
        if (each->isIncubated()) {
            row_col pos = each->getPos();
            if (pos.row == _focusPoint.row && pos.col == _focusPoint.col) {
                _focusWorm->onTrigger(each);
                each->onTrigger();
            }
        }
    }
}

Vector<Trigger* >& Observer::getTriggers()
{
    return _triggers;
}

void Observer::addTrigger(Trigger* trigger)
{
    _triggers.pushBack(trigger);
}

void Observer::removeTrigger(Trigger *trigger)
{
    _triggers.erase(_triggers.find(trigger));
}

short Observer::getSugerCount()
{
    short count = 0;
    
    // trigger
    for(auto each : _triggers)
    {
        short type = each->getType();
        if (type == TRIGGER_TYPE_SUGAR || type == TRIGGER_TYPE_HONEY) {
            count++;
        }
    }
    
    return count;
}

void Observer::showColorTip(const cocos2d::Color3B& color)
{
    for(auto each : _triggers)
    {
        short type = each->getType();
        if (type == TRIGGER_TYPE_SUGAR) {
            if (each->getSugarColor() == color) {
                each->focus();
            } else {
                each->blur();
            }
        }
    }
}