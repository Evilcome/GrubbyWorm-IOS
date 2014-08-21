//
//  FreePlayGround.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#include "FreePlayGround.h"
USING_NS_CC;

const int baseMeasureMent = 64;
const int baseSplit = 4;
const int maskTag = 101;

FreePlayGround::FreePlayGround()
:_focus(false)
{
    
}

FreePlayGround::~FreePlayGround()
{
}

bool FreePlayGround::init()
{
    if (!PlayGround::init()) {
        return false;
    }
    
    return true;
}

void FreePlayGround::update(float delta)
{
    
}

void FreePlayGround::create(row_col size)
{
    setPlayGroundSize(size);
    
    setContentSize(Size((baseMeasureMent + baseSplit) * size.row + baseSplit, (baseMeasureMent + baseSplit) * size.col + baseSplit));
    
    Size contentSize = getContentSize();
    auto layer = LayerColor::create(Color4B::WHITE, contentSize.width, contentSize.height);
    layer->setOpacity(40);
    this->addChild(layer, 10, maskTag);
    
    for (short i = 0; i != size.row; ++i) {
        for (short j = 0; j != size.col; ++j) {
            
            auto base = Sprite::create("base.png");
            base->setColor(Color3B(238, 238, 238));
            base->setOpacity(100);
            base->setPosition(Vec2(baseSplit * (i + 1) + baseMeasureMent * (i + 0.5), baseSplit * (j + 1) + baseMeasureMent * (j + 0.5)));
            
            this->addChild(base);
            
            row_col info = {i, j};
            insertDict(base, info);
        }
    }
}

void FreePlayGround::setFocusPoint(row_col point, int speed)
{
    if (_focus) {
        PlayGround::setFocusPoint(point, speed);
    }
}

void FreePlayGround::removeMask()
{
    auto layer = (LayerColor*)getChildByTag(maskTag);
    if (layer) {
        auto action = FadeOut::create(0.5);
        auto seq = Sequence::create(action,
                                    CallFunc::create(CC_CALLBACK_0(FreePlayGround::_removeMask, this, layer)),
                                    nullptr);
        layer->runAction(seq);
    }
}

void FreePlayGround::setFocus(bool focus)
{
    _focus = focus;
}

void FreePlayGround::_removeMask(Node* node)
{
    if (node) {
        node->removeFromParentAndCleanup(true);
        setFocus(true);
    }
}