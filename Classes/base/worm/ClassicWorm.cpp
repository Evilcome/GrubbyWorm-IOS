//
//  ClassicWorm.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-18.
//
//

#include "ClassicWorm.h"
#include "PlayGround.h"
#include "GameManager.h"
#include "Yuan.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

const int wormMarkTag = 101;

ClassicWorm::ClassicWorm()
:_grubby(0)
,_warning(false)
{
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

ClassicWorm::~ClassicWorm()
{
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        _yuans[i] = nullptr;
    }
}

bool ClassicWorm::init()
{
    if (!Worm::init()) {
        return false;
    }
    
    _config->setNormalSpeed(500);
    _config->setComboSpeed(360);
    _config->setRunawaySpeed(240);
    _config->setComboLast(8000);
    _config->setConsume(2);
    _config->setEnergy(150);
    _config->setRunawayCount(29);
    _config->setRunawayLast(15000);
    
    //setUnrivalled(true);
    
    return true;
}

void ClassicWorm::update(float delta)
{
    if (_playGround == nullptr) return;
    
    if (GAME_MGR->getGameStatus() != GAME_STATUS_RUNNING) return;
    
    // refresh pos
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
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
    
    // runawayLave
    if (_status == WORM_STATUS_RUNAWAY) {
        
        if (_property->getRunawayLave() > 0) {
            _property->setRunawayLave(_property->getRunawayLave() - (delta * 1000));
            
            if (!_warning && _property->getRunawayLave() < 3000) {
                _warningEffect();
                _warning = true;
            }
        } else {
            GAME_MGR->resetCombo();
            _property->setComboLave(0.0f);
            _property->setRunawayLave(0.0f);
        }
    } else {
        
        // comboLave
        if (_property->getComboLave() > 0) {
            _property->setComboLave(_property->getComboLave() - (delta * 1000));
        } else {
            GAME_MGR->resetCombo();
            _property->setComboLave(0.0f);
            _warning = false;
        }
    }
    
    _notifyComboLave();
    
    _notifyCrazyLave();
    
    // if no energy
    //log("=== worm energy: %d", _property->getEnergy());
    GAME_MGR->setEnergy({_property->getEnergy(), _config->getEnergy()});
    if (_property->getEnergy() <= 0) {
        die();
    }
}

void ClassicWorm::born(PlayGround *playGround, start_point start)
{
    if (playGround == nullptr) {
        return;
    }
    
    playGround->addChild(this);
    CC_SAFE_RETAIN(this);
    playGround->getObserver()->setFocusWorm(this);
    playGround->setFocusPoint(start.info, 0);
    
    setPlayGround(playGround);
    
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        
        auto yuan = Yuan::create();
        yuan->setGridStartPos(start.info);
        _yuans[i] = yuan;
        
        this->addChild(yuan, (WORM_CLASSIC_YUAN_COUNT - i), i);
    }
    
    colorRule();
    
    _property->setDirection(start.direction);
    _property->setComboLave(0.0f);
    _property->setEnergy(_config->getEnergy());
    
    Worm::born(playGround, start);
    
    this->scheduleUpdate();     // begin update
}

void ClassicWorm::die()
{
    Worm::die();
    
    this->unscheduleUpdate();
    log("DIE!!!");
    SimpleAudioEngine::getInstance()->playEffect("sound/lose.wav");
    
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        auto action = FadeOut::create(1);
        _yuans[i]->setGridColor(Color3B::BLACK);
        _yuans[i]->getGrid()->runAction(action);
    }
    
    auto seq = Sequence::create(DelayTime::create(1),
                                CallFunc::create(CC_CALLBACK_0(ClassicWorm::doDie, this)),
                                nullptr);
    this->runAction(seq);
}

void ClassicWorm::doDie()
{
    GAME_MGR->over();
}

void ClassicWorm::doCrawl()
{
    SimpleAudioEngine::getInstance()->playEffect("sound/step.mp3");
    
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
    
    for (short i = 1; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        _yuans[i]->setGridPos(_yuans[i - 1]->getFromPos());
    }
    
    // consume energy
    consume();
    
    // refresh status
    refreshStatus();
    
    // add grubby
    addGrubby();
    
    // color tip
    showColorTip();
}

row_col ClassicWorm::getPos()
{
    if (_yuans[0]) {
        return _yuans[0]->getNowPos();
    }
    
    return Worm::getPos();
}

void ClassicWorm::colorRule()
{
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        _yuans[i]->setGridColor(C3_COLORS[i]);
    }
}

void ClassicWorm::changeColor()
{
    colorChangeRule();
}

void ClassicWorm::colorChangeRule()
{
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        short t = i + 1;
        if (t == WORM_CLASSIC_YUAN_COUNT) {
            
            short random = CCRANDOM_0_1() * COLORS_INDEX;
            random >= COLORS_INDEX ? random = 0 : random = random;
            
            Color3B color = C3_COLORS[random];
            _yuans[WORM_CLASSIC_YUAN_COUNT - 1]->setGridColor(color);
        } else {
            _yuans[i]->setGridColor(_yuans[t]->getGridColor());
        }
    }
}

void ClassicWorm::onTrigger(Trigger* trigger)
{
    short type = trigger->getType();
    
    
    if (_status == WORM_STATUS_RUNAWAY) {
        int add = GAME_MGR->addTrigger();
        showAdd(add);
        
        fullEnergy();
        
        return;
    }
    
    switch (type) {
        case TRIGGER_TYPE_SUGAR:
        {
            auto ThisColor = _yuans[0]->getGridColor();
            auto sugarColor = trigger->getSugarColor();
            _supplementSugarFormation(sugarColor);
            
            if (ThisColor.equals(sugarColor)) {
                
                int add = GAME_MGR->addTrigger();
                showAdd(add);
                
                // energy
                fullEnergy();
                
                // color
                changeColor();
                
                // about combo
                _setCombo();
                
                // add grubby
                _grubby++;
            } else {
                emptyEnergy();
                
                GAME_MGR->resetCombo();
                _property->setComboLave(0.0f);
            }
        }
            break;
        case TRIGGER_TYPE_HONEY:
        {
            int add = GAME_MGR->addTrigger();
            showAdd(add);
            
            // energy
            fullEnergy();
            
            // about combo
            _setCombo();
            
            // add grubby
            _grubby += 5;
            
            // color
            changeColor();
        }
            break;
        case TRIGGER_TYPE_GRUBBY:
        {
            // energy
            eat(-100);
            
            GAME_MGR->resetCombo();
            _property->setComboLave(0.0f);
        }
            break;
        default:
            break;
    }
}

void ClassicWorm::refreshView()
{
    switch (_status) {
        case WORM_STATUS_DIE:
        {
            for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
                _removeMark(_yuans[i]);
            }
        }
            break;
        case WORM_STATUS_STOP:
        {
            for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
                _removeMark(_yuans[i]);
            }
        }
            break;
        case WORM_STATUS_NORMAL:
        {
            for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
                _removeMark(_yuans[i]);
            }
        }
            break;
        case WORM_STATUS_COMBO:
        {
            for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
                _removeMark(_yuans[i]);
            }
        }
            break;
        case WORM_STATUS_RUNAWAY:
        {
//            for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
//                _removeMark(_yuans[i]);
//                
//                auto mark = Sprite::create("base.png");
//                mark->setColor(Color3B::ORANGE);
//                _yuans[i]->addChild(mark, 5, wormMarkTag);
//            }
        }
            break;
        default:
            break;
    }
}

void ClassicWorm::addGrubby()
{
    if (_grubby > 0 && _playGround) {
        auto king = _playGround->getObserver()->getKing();
        bool added = king->createTrigger(TRIGGER_TYPE_GRUBBY, _yuans[WORM_CLASSIC_YUAN_COUNT - 1]->getFromPos());
        if (added) {
            _grubby--;
        }
    }
}

void ClassicWorm::showColorTip()
{
    if (_playGround != nullptr) {
        if (_status == WORM_STATUS_RUNAWAY) {
            _playGround->getObserver()->showColorTip(Color3B::ORANGE);
        } else {
            _playGround->getObserver()->showColorTip(_yuans[0]->getGridColor());
        }
    }
}

void ClassicWorm::showAdd(int add)
{
    _playGround->showAdd(add);
}

void ClassicWorm::_playComboEffect(float speed)
{
    this->stopAllActions();
    
    if (speed == 0) return;
    
    auto seq = Sequence::create(DelayTime::create(speed),
                                CallFunc::create(CC_CALLBACK_0(ClassicWorm::_comboEffect, this)),
                                nullptr);
    
    this->runAction(RepeatForever::create(seq));
}

void ClassicWorm::_comboEffect()
{
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        short targetIndex = i + 1;
        targetIndex == WORM_CLASSIC_YUAN_COUNT ? targetIndex = 0 : targetIndex = targetIndex;
        
        _yuans[i]->setGridColor(_yuans[targetIndex]->getGridColor());
    }
}

void ClassicWorm::_removeMark(Yuan *yuan)
{
    auto node = yuan->getChildByTag(wormMarkTag);
    if (node) {
        node->removeFromParentAndCleanup(true);
    }
}

void ClassicWorm::_notifyComboLave()
{
    NotificationCenter::getInstance()->postNotification(NOTI_COMBO_LAST);
}

void ClassicWorm::_notifyCrazyLave()
{
    NotificationCenter::getInstance()->postNotification(NOTI_RUNAWAY_LAST);
}

void ClassicWorm::_supplementSugarFormation(cocos2d::Color3B color)
{
    if (_playGround) {
        auto king = _playGround->getObserver()->getKing();
        king->supplementSugarFormation(color);
    }
}

void ClassicWorm::_setCombo()
{
    if (_property->getComboLave() == 0) {
        _property->setComboLave(_config->getComboLast());
    }else if (_property->getComboLave() > 0) {
        GAME_MGR->addCombo();
        _property->setComboLave(_config->getComboLast());
    } else {
        GAME_MGR->resetCombo();
        _property->setComboLave(0.0f);
    }
}

void ClassicWorm::_warningEffect()
{
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        auto mark = _yuans[i]->getChildByTag(wormMarkTag);
        
        if (mark) {
            auto action = Sequence::create(
                                           FadeOut::create(0.25),
                                           FadeIn::create(0.5),
                                           FadeOut::create(0.25),
                                           nullptr);
            
            mark->runAction(Repeat::create(action, 3));
        }
    }
}

void ClassicWorm::_prepareRunaway()
{
    this->unscheduleUpdate();
    
    SimpleAudioEngine::getInstance()->playEffect("sound/runaway.wav");
    
    for (short i = 0; i != WORM_CLASSIC_YUAN_COUNT; ++i) {
        _removeMark(_yuans[i]);
        
        auto mark = Sprite::create("base.png");
        mark->setColor(Color3B::ORANGE);
        _yuans[i]->addChild(mark, 5, wormMarkTag);
        
        auto change = Sequence::create(FadeOut::create(0.1),
                                       FadeIn::create(0.5 + i * 0.1),
                                       nullptr);
        
        mark->runAction(change);
    }
    
    runAction(Sequence::create(DelayTime::create(1),
                               CallFunc::create(CC_CALLBACK_0(ClassicWorm::_runawayPrepared, this)),
                               nullptr));
}

void ClassicWorm::_runawayPrepared()
{
    this->scheduleUpdate();
}