//
//  Trigger.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#include "Trigger.h"
USING_NS_CC;

Trigger::Trigger()
:_playGround(nullptr)
,_incubated(false)
,_focus(false)
{
    
}

Trigger::~Trigger()
{
    _playGround = nullptr;
}

bool Trigger::init()
{
    if (!Node::init()) {
        return false;
    }
    
    _color = Color3B::WHITE;
    
    return true;
}

short Trigger::getType()
{
    return TRIGGER_TYPE_BASE;
}

void Trigger::addTo(PlayGround* playGround, row_col pos)
{
    if (playGround != nullptr) {
        playGround->getObserver()->addTrigger(this);
        effect();
    }
}

void Trigger::effect()
{
    
}

void Trigger::destroy()
{
    PlayGround* playGround = (PlayGround*)getParent();
    if (playGround != nullptr) {
        playGround->getObserver()->removeTrigger(this);
        this->removeFromParentAndCleanup(true);
    }
}

row_col Trigger::getPos()
{
    return {-1, -1};
}

short Trigger::getEnergy()
{
    return 0;
}

void Trigger::setIncubated(bool incubate)
{
    _incubated = incubate;
}

bool Trigger::isIncubated()
{
    return _incubated;
}

void Trigger::focus()
{
    
}

void Trigger::blur()
{
    
}

void Trigger::setFocus(bool focus)
{
    _focus = focus;
}

bool Trigger::isFocusd()
{
    return _focus;
}
