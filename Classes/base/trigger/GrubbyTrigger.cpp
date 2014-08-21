//
//  GrubbyTrigger.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#include "GrubbyTrigger.h"
#include "Yuan.h"
USING_NS_CC;

GrubbyTrigger::GrubbyTrigger()
{
    for (short i = 0; i != TRIGGER_GRUBBY_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

GrubbyTrigger::~GrubbyTrigger()
{
    for (short i = 0; i != TRIGGER_GRUBBY_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

bool GrubbyTrigger::init()
{
    if (!Trigger::init()) {
        return false;
    }
    
    return true;
}

short GrubbyTrigger::getType()
{
    return TRIGGER_TYPE_GRUBBY;
}

void GrubbyTrigger::addTo(PlayGround* playGround, row_col pos)
{
    if (playGround == nullptr) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sound/grubby.wav");
    
    playGround->addChild(this);
    
    setPlayGround(playGround);
    
    Color3B colorBelow = Color3B::ORANGE;
    Color3B colorAbove = Color3B::WHITE;
    
    auto yuanBelow = Yuan::create();
    yuanBelow->setGridColor(colorBelow);
    yuanBelow->getGrid()->setOpacity(200);
    yuanBelow->setGridStartPos(pos);
    yuanBelow->setPosition(_playGround->getGridPosAt(pos));
    _yuans[0] = yuanBelow;
    
    auto yuanAbove = Yuan::create();
    yuanAbove->setGridColor(colorAbove);
    yuanAbove->getGrid()->setOpacity(0);
    _yuans[1] = yuanAbove;
    
    auto bb = Sprite::create("bb.png");
    if (bb) {
        bb->setOpacity(160);
        yuanAbove->addChild(bb);
    }
    
    this->addChild(yuanBelow, 0, 0);
    yuanBelow->addChild(yuanAbove, 1, 1);
    
    auto scale = Sequence::create(ScaleTo::create(0.5f, 0.9f),
                                  ScaleTo::create(0.5f, 0.82f),
                                  nullptr);
    yuanAbove->runAction(RepeatForever::create(scale));
    
    Trigger::addTo(playGround, pos);
}

void GrubbyTrigger::effect()
{
    // out effect
    auto yuanEffect = Yuan::create();
    yuanEffect->setGridColor(Color3B::YELLOW);
    yuanEffect->getGrid()->setOpacity(25);
    
    _yuans[0]->addChild(yuanEffect, 0);
    
	auto seq = Sequence::create(
                                ScaleTo::create(1.0f, 2.8),
                                FadeOut::create(0.2f),
                                CallFunc::create(CC_CALLBACK_0(GrubbyTrigger::uneffect, this, yuanEffect)),
                                nullptr
                                );
    yuanEffect->runAction(seq);
    
    setIncubated(true);
}

void GrubbyTrigger::uneffect(Node* node)
{
    if (node != nullptr) {
        node->removeFromParentAndCleanup(true);
    }
}

void GrubbyTrigger::onTrigger()
{
    SimpleAudioEngine::getInstance()->playEffect("sound/eat_grubby.mp3");
    
    _yuans[1]->setGridColor(Color3B::YELLOW);
    _yuans[0]->getGrid()->setOpacity(0);
    auto seq = Sequence::create(
                                ScaleTo::create(0.5f, 0.1),
                                CallFunc::create(CC_CALLBACK_0(GrubbyTrigger::destroy, this)),
                                nullptr
                                );
    _yuans[1]->runAction(seq);
}

row_col GrubbyTrigger::getPos()
{
    return _yuans[0]->getNowPos();
}