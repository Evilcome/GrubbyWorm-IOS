//
//  BaseLayer.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#include "BaseLayer.h"
#include "UIManager.h"
USING_NS_CC;

BaseLayer::BaseLayer()
{
    
}

BaseLayer::~BaseLayer()
{
    if (this == UI_MGR->find(getType())) {
        UI_MGR->erase(getType());
    }
}

bool BaseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    UI_MGR->inject(this);
    
    return true;
}

short BaseLayer::getType()
{
    return LAYER_BASE;
}