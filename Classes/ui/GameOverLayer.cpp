//
//  GameOverLayer.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#include "GameOverLayer.h"
#include "FAManager.h"
#include "GameManager.h"
#include "GameCenter.h"
#include "Common.h"
USING_NS_CC;

const int rootNodeTag = 100;

GameOverLayer::GameOverLayer()
{
    
}

GameOverLayer::~GameOverLayer()
{
    
}

bool GameOverLayer::init()
{
    if (!BaseLayer::init()) {
        return false;
    }
    
    display();
    
    return true;
}

short GameOverLayer::getType()
{
    return LAYER_GAME_OVER;
}

void GameOverLayer::display()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto maskLayer = LayerColor::create(Color4B(26, 26, 26, 200), visibleSize.width, visibleSize.height);
    
    this->addChild(maskLayer);
    
    displayContent();
}

void GameOverLayer::displayContent()
{
    // effect node
    auto root = Node::create();
    this->addChild(root, 0, rootNodeTag);
    if (root) {
        root->setPosition(Vec2(100, -400));
        root->setRotation(-30);
        auto move = MoveTo::create(0.5f, Vec2::ZERO);
        auto rotate = RotateTo::create(0.5f, 0);
        auto easeRotate = EaseBackOut::create(rotate);
        
        root->runAction(move);
        root->runAction(easeRotate);
    }
    
    // content
    auto size = Size(660, 380);
    auto contentLayer = LayerColor::create(Color4B::WHITE, size.width, size.height);
    contentLayer->setPosition(Vec2(VisibleRect::center().x - size.width / 2, VisibleRect::center().y - size.height / 2));
    root->addChild(contentLayer, 1);
    
    displayScore(contentLayer);
    
    // title
    auto titleLabel = Label::createWithTTF(FC_NUMBER_TITLE, "game over");
    if (titleLabel) {
        titleLabel->setTextColor(C4_LIGHT_GREEN);
        titleLabel->enableOutline(C4_DARK_GREEN);
        titleLabel->setAnchorPoint(Vec2(0.5, 1));
        titleLabel->setPosition(VisibleRect::center() - contentLayer->getPosition() + Vec2(0, 190));
        contentLayer->addChild(titleLabel);
    }
    
    auto restartBtn = displayRestartBtn();
    auto gameCenterBtn = displayGameCenterBtn();
    
    auto menu = Menu::create(restartBtn, gameCenterBtn, nullptr);
    menu->setPosition(VisibleRect::center() - contentLayer->getPosition());
    contentLayer->addChild(menu);
}

void GameOverLayer::displayScore(Node* parent)
{
    // score
    auto scoreTitle = Label::createWithTTF(FC_NUMBER_SMALL, "score");
    if (scoreTitle) {
        scoreTitle->setTextColor(C4_LIGHT_GREEN);
        scoreTitle->enableOutline(C4_DARK_GREEN);
        scoreTitle->setPosition(Vec2(160, 250));
        parent->addChild(scoreTitle);
    }
    char score[10];
    sprintf(score, "%d", GAME_MGR->getPlayerScore());
    auto scoreLabel = Label::createWithTTF(FC_NUMBER_NORMAL, score);
    if (scoreLabel) {
        scoreLabel->setTextColor(Color4B::YELLOW);
        scoreLabel->enableOutline(Color4B::ORANGE);
        scoreLabel->setPosition(Vec2(160, 170));
        parent->addChild(scoreLabel);
    }
    
    // best score
    auto bestScoreTitle = Label::createWithTTF(FC_NUMBER_SMALL, "best");
    if (bestScoreTitle) {
        bestScoreTitle->setTextColor(C4_LIGHT_GREEN);
        bestScoreTitle->enableOutline(C4_DARK_GREEN);
        bestScoreTitle->setPosition(Vec2(490, 250));
        parent->addChild(bestScoreTitle);
    }
    char bestScore[10];
    sprintf(bestScore, "%d", GAME_MGR->getBestScore());
    auto bestScoreLabel = Label::createWithTTF(FC_NUMBER_NORMAL, bestScore);
    if (bestScoreLabel) {
        bestScoreLabel->setTextColor(Color4B::YELLOW);
        bestScoreLabel->enableOutline(Color4B::ORANGE);
        bestScoreLabel->setPosition(Vec2(490, 170));
        parent->addChild(bestScoreLabel);
    }
}

MenuItem* GameOverLayer::displayRestartBtn()
{
    auto spriteNormal = Sprite::create("base.png");
    spriteNormal->setColor(Color3B(170, 226, 246));
    auto spriteSelected = Sprite::create("base.png");
    spriteSelected->setColor(Color3B(182, 230, 246));
    auto spriteDisabled = Sprite::create("base.png");
    spriteDisabled->setColor(Color3B::GRAY);
    
    auto btn = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(GameOverLayer::onClickRestart, this) );
    btn->setScale(3.6f, 1.8f);
    btn->setPosition(Vec2(-170, -110));
    btn->setOpacity(200);
    
    auto cupIcon = Label::createWithTTF(FC_ICON_BIG, FA_MGR->getContent(FARefresh));
    if (cupIcon) {
        cupIcon->setTextColor(Color4B::WHITE);
        cupIcon->enableOutline(Color4B::GRAY);
        cupIcon->setScaleX(1.0f / 3.6f);
        cupIcon->setScaleY(1.0f / 1.8f);
        auto size = btn->getContentSize();
        cupIcon->setPosition(Vec2(size.width / 2, size.height / 2));
        btn->addChild(cupIcon, 10);
    }
    
    return btn;
}

MenuItem* GameOverLayer::displayGameCenterBtn()
{
    auto spriteNormal = Sprite::create("base.png");
    spriteNormal->setColor(Color3B(246, 222, 160));
    auto spriteSelected = Sprite::create("base.png");
    spriteSelected->setColor(Color3B(248, 224, 164));
    auto spriteDisabled = Sprite::create("base.png");
    spriteDisabled->setColor(Color3B::GRAY);
    
    auto btn = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(GameOverLayer::onClickGameCenter, this) );
    btn->setScale(3.6f, 1.8f);
    btn->setPosition(Vec2(170, -110));
    btn->setOpacity(200);
    
    auto cupIcon = Label::createWithTTF(FC_ICON_BIG, FA_MGR->getContent(FAGamepad));
    if (cupIcon) {
        cupIcon->setTextColor(Color4B::WHITE);
        cupIcon->enableOutline(Color4B::GRAY);
        cupIcon->setScaleX(1.0f / 3.6f);
        cupIcon->setScaleY(1.0f / 1.8f);
        auto size = btn->getContentSize();
        cupIcon->setPosition(Vec2(size.width / 2, size.height / 2));
        btn->addChild(cupIcon, 10);
    }
    
    return btn;
}

void GameOverLayer::onClickRestart(cocos2d::Ref *sender)
{
    GAME_MGR->restart();
}

void GameOverLayer::onClickGameCenter(cocos2d::Ref *sender)
{
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        GameCenter* center = (GameCenter*)GAME_MGR->getGameCenter();
        if (center) {
            center->showScores();
        }
    }
}