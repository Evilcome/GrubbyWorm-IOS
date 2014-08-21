//
//  SugarTrigger.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#include "SugarTrigger.h"
#include "Yuan.h"
USING_NS_CC;

const int focusEffectRoot = 100;

SugarTrigger::SugarTrigger()
{
    for (short i = 0; i != TRIGGER_SUGAR_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

SugarTrigger::~SugarTrigger()
{
    for (short i = 0; i != TRIGGER_SUGAR_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

bool SugarTrigger::init()
{
    if (!Trigger::init()) {
        return false;
    }
    
    return true;
}

short SugarTrigger::getType()
{
    return TRIGGER_TYPE_SUGAR;
}

void SugarTrigger::addTo(PlayGround* playGround, row_col pos)
{
    if (playGround == nullptr) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sound/create.wav");
    
    playGround->addChild(this);
    
    setPlayGround(playGround);
    
    auto yuanBelow = Yuan::create();
    yuanBelow->getGrid()->setOpacity(0);
    yuanBelow->setGridStartPos(pos);
    yuanBelow->setPosition(_playGround->getGridPosAt(pos));
    _yuans[0] = yuanBelow;
    
    auto yuanAbove = Yuan::create();
    yuanAbove->setScale(0.6f);
    yuanAbove->setGridColor(_color);
    _yuans[1] = yuanAbove;
    
    this->addChild(yuanBelow, 0, 0);
    yuanBelow->addChild(yuanAbove, 1, 1);
    
    // effect
    auto rotate = Sequence::create(DelayTime::create(1),
                                   RotateBy::create(0.5f, 90),
                                   nullptr);
    auto scale = Sequence::create(DelayTime::create(0.5),
                                  ScaleTo::create(0.5f, 0.65f),
                                  ScaleTo::create(0.5f, 0.6f),
                                  nullptr);
    yuanAbove->runAction(RepeatForever::create(rotate));
    yuanAbove->runAction(RepeatForever::create(scale));
    
    Trigger::addTo(playGround, pos);
}

void SugarTrigger::effect()
{
    // out effect
    _yuans[1]->setVisible(false);
    
    auto yuanEffect = Yuan::create();
    yuanEffect->setGridColor(Color3B(50, 244, 244));
    yuanEffect->getGrid()->setOpacity(100);
    
    _yuans[0]->addChild(yuanEffect, 10);
    
	auto seq = Sequence::create(
                                ScaleTo::create(0.2f, 0.9f),
                                ScaleTo::create(0.1f, 0.8f),
                                ScaleTo::create(0.2f, 0.9f),
                                ScaleTo::create(0.1f, 0.8f),
                                ScaleTo::create(0.2f, 0.9f),
                                ScaleTo::create(0.1f, 0.8f),
                                FadeOut::create(0.3f),
                                CallFunc::create(CC_CALLBACK_0(SugarTrigger::uneffect, this, yuanEffect)),
                                nullptr
                                );
    yuanEffect->getGrid()->runAction(seq);
}

void SugarTrigger::uneffect(Node* node)
{
    _yuans[1]->setVisible(true);
    
    setIncubated(true);
    
    if (node != nullptr) {
        node->removeFromParentAndCleanup(true);
    }
}

void SugarTrigger::onTrigger()
{
    SimpleAudioEngine::getInstance()->playEffect("sound/eat.mp3");
    
    _yuans[1]->setGridColor(Color3B::YELLOW);
    auto seq = Sequence::create(
                                ScaleTo::create(0.5f, 0.1),
                                CallFunc::create(CC_CALLBACK_0(SugarTrigger::destroy, this)),
                                nullptr
                                );
    _yuans[1]->runAction(seq);
}

row_col SugarTrigger::getPos()
{
    return _yuans[0]->getNowPos();
}

void SugarTrigger::focus()
{
    if (!isIncubated()) {
        return;
    }
    
    if (isFocusd()) {
        return;
    } else {
        setFocus(true);
    }
    
    auto root = Node::create();
    _yuans[0]->addChild(root, 100, focusEffectRoot);
    
    Vec2 points[4] = {
        Vec2(0, 36),
        Vec2(36, 0),
        Vec2(0, -36),
        Vec2(-36, 0)
    };
    
    float rotate[4] = {
        90, 180, -90, 0
    };
    
    float random = CCRANDOM_MINUS1_1() * 50;
    
    for (short i = 0; i != 4; ++i) {
        auto triangle = Label::createWithTTF(FC_ICON, FA_MGR->getContent(FAPlay));
        if (triangle != nullptr) {
            triangle->setTextColor(Color4B(_color.r, _color.g, _color.b, 255));
            triangle->setScale(0.4f);
            triangle->enableOutline(Color4B(220, 220, 220, 90));
            triangle->setPosition(points[i]);
            triangle->setRotation(rotate[i]);
            root->addChild(triangle);
        }
    }
    
    auto action = Sequence::create(DelayTime::create(0.6f),
                                   RotateBy::create(0.2f, random),
                                   RotateBy::create(0.4f, -random * 2),
                                   nullptr);
    auto scale = Sequence::create(ScaleTo::create(0.3f, 0.95f),
                                  ScaleTo::create(0.4f, 0.9f),
                                  nullptr);
    root->runAction(RepeatForever::create(action));
    root->runAction(RepeatForever::create(scale));
}

void SugarTrigger::blur()
{
    if (!isFocusd()) {
        return;
    } else {
        setFocus(false);
    }
    
    auto root = _yuans[0]->getChildByTag(focusEffectRoot);
    if (root != nullptr) {
        root->removeFromParentAndCleanup(true);
    }
}

