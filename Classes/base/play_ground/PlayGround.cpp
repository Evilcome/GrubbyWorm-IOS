//
//  PlayGround.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-18.
//
//

#include "PlayGround.h"
#include "Observer.h"
#include "GameManager.h"
#include "Common.h"
#include "Worm.h"
USING_NS_CC;

const int baseMeasureMent = 64;
const int baseSplit = 4;
const int addRootTag = 888;

PlayGround::PlayGround()
:_observer(nullptr)
{
    
}

PlayGround::~PlayGround()
{
    CC_SAFE_RELEASE(_observer);
}

bool PlayGround::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    _observer = Observer::create();
    _observer->setPlayGround(this);
    CC_SAFE_RETAIN(_observer);
    
    return true;
}

void PlayGround::update(float delta)
{
    if (GAME_MGR->getGameStatus() != GAME_STATUS_RUNNING) return;
    
    if (_observer != nullptr) {
        _observer->getKing()->monitor(delta);
    }
}

void PlayGround::create(row_col size)
{
    setPlayGroundSize(size);

    setContentSize(Size((baseMeasureMent + baseSplit) * size.row + baseSplit, (baseMeasureMent + baseSplit) * size.col + baseSplit));
    
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
    
    // display add node
    auto root = Node::create();
    this->addChild(root, 1000, addRootTag);
    
    auto label = Label::createWithTTF(FC_NUMBER_SMALL, "+");
    if (label) {
        label->setTextColor(Color4B(255, 255, 0, 180));
        label->enableOutline(Color4B(255, 127, 0, 180));
        root->addChild(label, 0, 10);
    }
    
    this->scheduleUpdate();
}

void PlayGround::insertDict(cocos2d::Sprite *grid, row_col info)
{
    int tag = info.row * 1000 + info.col;
    grid->setTag(tag);
}

Sprite* PlayGround::getGridAt(row_col info)
{
    int tag = info.row * 1000 + info.col;
    return (Sprite*)getChildByTag(tag);
}

const Vec2& PlayGround::getGridPosAt(row_col info)
{
    int tag = info.row * 1000 + info.col;
    Node* node = getChildByTag(tag);
    if (node != nullptr) {
        return node->getPosition();
    }
    
    return Vec2::ZERO;
}

void PlayGround::setFocusPoint(row_col point, int speed)
{
    if (_observer) {
        _observer->setFocusPoint(point);
        _observer->cameraFocus(speed);
    }
}

Worm* PlayGround::getFocusWorm()
{
    if (_observer) {
        return _observer->getFocusWorm();
    }
    
    return nullptr;
}

void PlayGround::showAdd(int add)
{
    if (add <= 0) return;
    
    auto root = getChildByTag(addRootTag);
    
    if (root) {
        root->stopAllActions();
        root->setVisible(true);

        auto label = (Label*)root->getChildByTag(10);
        
        if (label) {
            char value[15];
            sprintf(value, "+ %d", add);
            root->setPosition(getGridPosAt(getFocusWorm()->getPos()));
            label->setString(value);
        }
    }
    
    auto scale = ScaleTo::create(0.5f, 1.5f);
    auto ease = EaseBackOut::create(MoveBy::create(0.5, Vec2(60, 60)));
    auto action = Sequence::create(ease,
                                   CallFunc::create(CC_CALLBACK_0(PlayGround::hideAdd, this)),
                                   nullptr);
    
    root->runAction(scale);
    root->runAction(action);
}

void PlayGround::hideAdd()
{
    auto root = getChildByTag(addRootTag);
    
    if (root) {
        root->setVisible(false);
    }
}