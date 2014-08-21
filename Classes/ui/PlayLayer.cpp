//
//  PlayLayer.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#include "PlayLayer.h"
#include "GameScene.h"
#include "GameManager.h"
#include "FAManager.h"
#include "UIManager.h"
#include "PlayGround.h"
#include "Worm.h"
#include "Common.h"
USING_NS_CC;

PlayLayer::PlayLayer()
{
    
}

PlayLayer::~PlayLayer()
{
    auto center = NotificationCenter::getInstance();
    center->removeAllObservers(this);
}

bool PlayLayer::init()
{
    if (!BaseLayer::init()) {
        return false;
    }
    
    display();
    
    return true;
}

short PlayLayer::getType()
{
    return LAYER_PLAY;
}

void PlayLayer::display()
{
    auto spriteNormal = Sprite::create("base-r.png");
    spriteNormal->setColor(Color3B(200, 200, 200));
    auto spriteSelected = Sprite::create("base-r.png");
    auto spriteDisabled = Sprite::create("base-r.png");
    spriteDisabled->setColor(Color3B::GRAY);
    
    // pause button
    auto btn = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(PlayLayer::onClickPause, this) );
    btn->setOpacity(100);
    auto menu = Menu::create(btn, nullptr);
    menu->setPosition(Vec2(VisibleRect::top().x, VisibleRect::top().y - 60));
    addChild(menu);
    
    auto faPause = Label::createWithTTF(FC_ICON, FA_MGR->getContent(FAPause));
    if (faPause) {
        faPause->setTextColor(Color4B::WHITE);
        faPause->enableOutline(Color4B(26, 26, 26, 80));
        faPause->setPosition(Vec2(btn->getContentSize().width / 2, btn->getContentSize().height / 2));
        btn->addChild(faPause);
    }
    
    // total label
    auto scoreLabel = Label::createWithTTF(FC_NUMBER_NORMAL, "0");
    if (scoreLabel) {
        scoreLabel->setTextColor(Color4B::YELLOW);
        scoreLabel->enableOutline(Color4B::ORANGE);
        scoreLabel->setAnchorPoint(Vec2(0, 0.5));
        scoreLabel->setPosition(Vec2(VisibleRect::left().x + 40, VisibleRect::top().y - 68));
        this->addChild(scoreLabel);
        
        auto center = NotificationCenter::getInstance();
        center->addObserver(this, callfuncO_selector(PlayLayer::refreshScore), NOTI_TOTAL_VALUE, scoreLabel);
    }
    
    // energy info
    auto energyRoot = Node::create();
    if (energyRoot) {
        Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
        
        int offsetY = (int)rect.size.height % 12;
        for (short i = 0; i != (int)(rect.size.height / 12); ++i) {
            auto yuan = Sprite::create("base.png");
            yuan->setScale(0.5f, 0.125f);
            yuan->setOpacity(180);
            yuan->setAnchorPoint(Vec2(1, 0));
            yuan->setPosition(Vec2(rect.origin.x + rect.size.width, i * 8 + (i + 1) * 4));
            energyRoot->addChild(yuan, 0, i);
        }
        
        this->addChild(energyRoot);
        energyRoot->setPosition(Vec2(-4, offsetY / 2));
        
        auto center = NotificationCenter::getInstance();
        center->addObserver(this, callfuncO_selector(PlayLayer::refreshEnergy), NOTI_ENERGY_VALUE, energyRoot);
    }
    
    displayHappy();
    displayCrazy();
}

void PlayLayer::displayHappy()
{
    auto root = Node::create();
    root->setPosition(Vec2(VisibleRect::right().x - 170, VisibleRect::top().y - 60));
    this->addChild(root);
    
    root->setVisible(false);
    
    auto scale = Sequence::create(ScaleTo::create(0.3f, 0.8f),
                                  ScaleTo::create(0.25f, 0.75f),
                                  nullptr);
    root->runAction(RepeatForever::create(scale));
    
    auto labelDown = Label::createWithTTF(FC_NUMBER_NORMAL, "happy");
    auto labelCombo = Label::createWithTTF(FC_NUMBER_NORMAL, "happy");
    if (labelDown) {
        labelDown->setTextColor(Color4B::WHITE);
        labelDown->enableOutline(Color4B(180, 160, 26, 200));
        root->addChild(labelDown, 1, 1);
    }
    
    if (labelCombo) {
        labelCombo->setTextColor(Color4B(255, 237, 35, 255));
        labelCombo->enableOutline(Color4B(255, 255, 255, 0));
        auto size = labelCombo->getContentSize();
        labelCombo->setPosition(Vec2(size.width / 2, size.height / 2));
        
        auto clipper = ClippingNode::create();
        clipper->setContentSize(size);
        clipper->setAnchorPoint(Vec2(0.5, 0.5));
        root->addChild(clipper, 2, 2);
        
        auto stencil = DrawNode::create();
        Vec2 rectangle[4];
        rectangle[0] = Vec2(0, 0);
        rectangle[1] = Vec2(clipper->getContentSize().width, 0);
        rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
        rectangle[3] = Vec2(0, clipper->getContentSize().height);
        
        Color4F white(1, 1, 1, 1);
        stencil->drawPolygon(rectangle, 4, white, 1, white);
        clipper->setStencil(stencil);
        
        clipper->addChild(labelCombo);
        
        auto center = NotificationCenter::getInstance();
        center->addObserver(this, callfuncO_selector(PlayLayer::refreshComboLast), NOTI_COMBO_LAST, root);
    }
}

void PlayLayer::displayCrazy()
{
    auto root = Node::create();
    root->setPosition(Vec2(VisibleRect::right().x - 170, VisibleRect::top().y - 60));
    this->addChild(root);
    
    root->setVisible(false);
    
    auto scale = Sequence::create(ScaleTo::create(0.2f, 0.8f),
                                  ScaleTo::create(0.15f, 0.75f),
                                  nullptr);
    root->runAction(RepeatForever::create(scale));
    
    auto labelDown = Label::createWithTTF(FC_NUMBER_NORMAL, "crazy!");
    auto labelDisplay = Label::createWithTTF(FC_NUMBER_NORMAL, "crazy!");
    if (labelDown) {
        labelDown->setTextColor(Color4B::WHITE);
        labelDown->enableOutline(Color4B::RED);
        root->addChild(labelDown, 1, 1);
    }
    
    if (labelDisplay) {
        labelDisplay->setTextColor(Color4B::ORANGE);
        labelDisplay->enableOutline(Color4B(255, 255, 255, 0));
        auto size = labelDisplay->getContentSize();
        labelDisplay->setPosition(Vec2(size.width / 2, size.height / 2));
        
        auto clipper = ClippingNode::create();
        clipper->setContentSize(size);
        clipper->setAnchorPoint(Vec2(0.5, 0.5));
        root->addChild(clipper, 2, 2);
        
        auto stencil = DrawNode::create();
        Vec2 rectangle[4];
        rectangle[0] = Vec2(0, 0);
        rectangle[1] = Vec2(clipper->getContentSize().width, 0);
        rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
        rectangle[3] = Vec2(0, clipper->getContentSize().height);
        
        Color4F white(1, 1, 1, 1);
        stencil->drawPolygon(rectangle, 4, white, 1, white);
        clipper->setStencil(stencil);
        
        clipper->addChild(labelDisplay);
        
        auto center = NotificationCenter::getInstance();
        center->addObserver(this, callfuncO_selector(PlayLayer::refreshCrazyLast), NOTI_RUNAWAY_LAST, root);
    }
}

void PlayLayer::refreshScore(cocos2d::Ref* sender)
{
    if (sender != nullptr) {
        auto label = (Label*)sender;
        if (label) {
            
            int value = GAME_MGR->getScore().total;
            
            char combo[10];
            sprintf(combo, "%d", value);
            label->setString(combo);
            label->setVisible(true);
            
            auto action = label->getActionByTag(10);
            if(action == nullptr) {
                auto scaleAction = ScaleBy::create(0.1f, 1.5f, 1.5f);
                auto seq = Sequence::create(
                                            scaleAction,
                                            scaleAction->reverse(),
                                            NULL);
                seq->setTag(10);
                label->runAction(seq);
            }
        }
    }
}

void PlayLayer::refreshEnergy(cocos2d::Ref* sender)
{
    if (sender != nullptr) {
        auto energyRoot = (Node*)sender;
        count_detail detail = GAME_MGR->getEnergy();
        
        int percent = detail.now * 100 / detail.max;
        int colorCount = (int)(percent * energyRoot->getChildrenCount() / 100);
        
        auto color = Color3B::WHITE;
        if (percent > 66) {
            color = Color3B::GREEN;
        } else if (percent > 33) {
            color = Color3B::ORANGE;
        } else {
            color = Color3B::RED;
        }
        
        for (short i = 0; i != energyRoot->getChildrenCount(); ++i) {
            auto yuan = (Sprite*)energyRoot->getChildByTag(i);
            if (yuan) {
                if (i < colorCount) {
                    yuan->setColor(color);
                } else {
                    yuan->setColor(Color3B::WHITE);
                }
            }
        }
    }
}

void PlayLayer::refreshComboLast(Ref* sender)
{
    auto layer = (GameScene*)UI_MGR->find(LAYER_GAME);
    if (layer == nullptr) return;
    
    auto playGround = layer->getPlayGround();
    auto worm = (Worm*)playGround->getFocusWorm();
    
    if (worm) {
        
        auto root = (Node*)sender;
        if (root) {
            
            if (worm->getStatus() == WORM_STATUS_RUNAWAY) {
                root->setVisible(false);
                return;
            }
            
            if (GAME_MGR->getScore().combo == 0) {
                root->setVisible(false);
                return;
            }
            
            root->setVisible(true);
            
            auto clipper = (ClippingNode*)root->getChildByTag(2);
            
            if (clipper) {
                CC_SAFE_RETAIN(clipper);
                clipper->removeFromParent();
                
                auto oldStencil = clipper->getStencil();
                oldStencil->removeFromParentAndCleanup(true);
                
                auto stencil = DrawNode::create();
                short last = worm->getConfig()->getComboLast();
                float lave = worm->getProperty()->getComboLave();
                
                float width = (1 - lave / (float)last) * clipper->getContentSize().width;
                width >= 0 ? width = width : width = 0;
                
                Vec2 rectangle[4];
                rectangle[0] = Vec2(width, 0);
                rectangle[1] = Vec2(clipper->getContentSize().width, 0);
                rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
                rectangle[3] = Vec2(width, clipper->getContentSize().height);
                
                Color4F white(1, 1, 1, 1);
                stencil->drawPolygon(rectangle, 4, white, 1, white);
                
                clipper->setStencil(stencil);
                
                root->addChild(clipper, 2, 2);
                CC_SAFE_RELEASE(clipper);
            }
        }
    }
}

void PlayLayer::refreshCrazyLast(Ref* sender)
{
    auto layer = (GameScene*)UI_MGR->find(LAYER_GAME);
    if (layer == nullptr) return;
    
    auto playGround = layer->getPlayGround();
    auto worm = (Worm*)playGround->getFocusWorm();
    
    if (worm) {
        auto root = (Node*)sender;
        if (root) {
            
            if (worm->getStatus() != WORM_STATUS_RUNAWAY) {
                root->setVisible(false);
                return;
            }
            
            root->setVisible(true);
            
            auto clipper = (ClippingNode*)root->getChildByTag(2);
            
            if (clipper) {
                CC_SAFE_RETAIN(clipper);
                clipper->removeFromParent();
                
                auto oldStencil = clipper->getStencil();
                oldStencil->removeFromParentAndCleanup(true);
                
                auto stencil = DrawNode::create();
                short last = worm->getConfig()->getRunawayLast();
                float lave = worm->getProperty()->getRunawayLave();
                
                float width = (1 - lave / (float)last) * clipper->getContentSize().width;
                width >= 0 ? width = width : width = 0;
                
                Vec2 rectangle[4];
                rectangle[0] = Vec2(width, 0);
                rectangle[1] = Vec2(clipper->getContentSize().width, 0);
                rectangle[2] = Vec2(clipper->getContentSize().width, clipper->getContentSize().height);
                rectangle[3] = Vec2(width, clipper->getContentSize().height);
                
                Color4F white(1, 1, 1, 1);
                stencil->drawPolygon(rectangle, 4, white, 1, white);
                
                clipper->setStencil(stencil);
                
                root->addChild(clipper, 2, 2);
                CC_SAFE_RELEASE(clipper);
            }
        }
    }
}

void PlayLayer::onClickPause(Ref* sender)
{
    GAME_MGR->pause();
}
