//
//  HoneyTrigger.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-29.
//
//

#include "HoneyTrigger.h"
#include "Yuan.h"
USING_NS_CC;

const int focusEffectRoot = 100;

HoneyTrigger::HoneyTrigger()
{
    for (short i = 0; i != TRIGGER_HONEY_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

HoneyTrigger::~HoneyTrigger()
{
    for (short i = 0; i != TRIGGER_HONEY_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

bool HoneyTrigger::init()
{
    if (!Trigger::init()) {
        return false;
    }
    
    return true;
}

short HoneyTrigger::getType()
{
    return TRIGGER_TYPE_HONEY;
}

void HoneyTrigger::addTo(PlayGround* playGround, row_col pos)
{
    if (playGround == nullptr) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sound/create.wav");
    
    playGround->addChild(this);
    
    setPlayGround(playGround);
    
    Color3B colorBelow = Color3B(50, 244, 244);
    
    auto yuanBelow = Yuan::create();
    yuanBelow->setGridColor(colorBelow);
    yuanBelow->getGrid()->setOpacity(20);
    yuanBelow->setGridStartPos(pos);
    yuanBelow->setPosition(_playGround->getGridPosAt(pos));
    _yuans[0] = yuanBelow;
    
    auto yuanAbove = Yuan::create();
    yuanAbove->setScale(0.1f);
    yuanAbove->getGrid()->setOpacity(0);
    _yuans[1] = yuanAbove;
    
    this->addChild(yuanBelow, 0, 0);
    yuanBelow->addChild(yuanAbove, 1, 1);
    
    Vec2 points[5] = {
        Vec2(0.5, 0.5),
        Vec2(1.1, -0.1),
        Vec2(-0.1, -0.1),
        Vec2(-0.1, 1.1),
        Vec2(1.1, 1.1)
    };
    
    // node
    auto node = Node::create();
    for (short i = 0; i != COLORS_INDEX; ++i) {
        auto sprite = Sprite::create("base.png");
        sprite->setColor(C3_COLORS[i]);
        sprite->setAnchorPoint(points[i]);
        
        if (i != 0) {
            sprite->setScale(0.5f);
        } else {
            sprite->setScale(1.3f);
        }
        
        node->addChild(sprite);
    }
    yuanAbove->addChild(node);
    
    // effect
    auto rotate = Sequence::create(DelayTime::create(1),
                                   RotateBy::create(0.5f, 90),
                                   nullptr);
    auto scale = Sequence::create(DelayTime::create(0.5),
                                  ScaleTo::create(0.5f, 0.5f),
                                  ScaleTo::create(0.5f, 0.45f),
                                  nullptr);
    yuanAbove->runAction(RepeatForever::create(rotate));
    yuanAbove->runAction(RepeatForever::create(scale));
    
    Trigger::addTo(playGround, pos);
}

void HoneyTrigger::effect()
{
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
                                CallFunc::create(CC_CALLBACK_0(HoneyTrigger::uneffect, this, yuanEffect)),
                                nullptr
                                );
    yuanEffect->runAction(seq);
}

void HoneyTrigger::uneffect(Node* node)
{
    _yuans[1]->setVisible(true);
    
    setIncubated(true);
    
    alwaysFocus();
    
    if (node != nullptr) {
        node->removeFromParentAndCleanup(true);
    }
}

void HoneyTrigger::onTrigger()
{
    SimpleAudioEngine::getInstance()->playEffect("sound/eat.mp3");
    
    _yuans[1]->setGridColor(Color3B::YELLOW);
    _yuans[0]->getGrid()->setOpacity(0);
    auto seq = Sequence::create(
                                ScaleTo::create(0.5f, 0.1),
                                CallFunc::create(CC_CALLBACK_0(HoneyTrigger::destroy, this)),
                                nullptr
                                );
    _yuans[1]->runAction(seq);
}

row_col HoneyTrigger::getPos()
{
    return _yuans[0]->getNowPos();
}

void HoneyTrigger::alwaysFocus()
{
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
            triangle->setTextColor(Color4B(170, 226, 246, 225));
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