//
//  MenuScene.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#include "MenuScene.h"
#include "GameScene.h"
#include "Common.h"
#include "FAManager.h"
#include "GameManager.h"
#include "GameCenter.h"
#include "FreePlayGround.h"
#include "FreeWorm.h"
USING_NS_CC;

const int logoTag = 10;
const int menuTag = 11;

MenuScene::MenuScene()
:_playGround(nullptr)
{
    
}

MenuScene::~MenuScene()
{
    _playGround = nullptr;
}

Scene* MenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init()
{
    if (!BaseLayer::init()) {
        return false;
    }
    
    display();
    displayWorm();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.wav", true);
    
    return true;
}

short MenuScene::getType()
{
    return LAYER_MENU;
}

void MenuScene::display()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto layer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    
    this->addChild(layer);
    
    // logo
    auto logoLabel = Label::createWithTTF(FC_NUMBER_MIDDLE, "grubby worm");
    if (logoLabel) {
        logoLabel->setTextColor(C4_LIGHT_GREEN);
        logoLabel->enableOutline(C4_DARK_GREEN);
        logoLabel->setAnchorPoint(Vec2(0.5, 1));
        logoLabel->setPosition(Vec2(VisibleRect::center().x, VisibleRect::top().y - 95));
        this->addChild(logoLabel, 10, logoTag);
        
        auto action = RotateTo::create(3, -2);
        auto action2 = RotateTo::create(6, 2);
        logoLabel->runAction(RepeatForever::create(Sequence::create(action, action2, nullptr)));
    }
    
    // buttons
    auto playBtn = displayPlayBtn();
    auto gameCenterBtn = displayGameCenterBtn();
    
    auto menu = Menu::create(playBtn, gameCenterBtn, nullptr);
    menu->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y - 100));
    this->addChild(menu, 10, menuTag);

}

MenuItem* MenuScene::displayPlayBtn()
{
    auto spriteNormal = Sprite::create("base.png");
    spriteNormal->setColor(Color3B(170, 226, 246));
    auto spriteSelected = Sprite::create("base.png");
    spriteSelected->setColor(Color3B(182, 230, 246));
    auto spriteDisabled = Sprite::create("base.png");
    spriteDisabled->setColor(Color3B::GRAY);
    
    auto btn = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(MenuScene::onClickPlay, this) );
    btn->setScale(3.6f, 1.8f);
    btn->setPosition(Vec2(-170, 0));
    btn->setOpacity(200);
    
    auto cupIcon = Label::createWithTTF(FC_ICON_BIG, FA_MGR->getContent(FAPlayCircle));
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

MenuItem* MenuScene::displayGameCenterBtn()
{
    auto spriteNormal = Sprite::create("base.png");
    spriteNormal->setColor(Color3B(246, 222, 160));
    auto spriteSelected = Sprite::create("base.png");
    spriteSelected->setColor(Color3B(248, 224, 164));
    auto spriteDisabled = Sprite::create("base.png");
    spriteDisabled->setColor(Color3B::GRAY);
    
    auto btn = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(MenuScene::onClickGameCenter, this) );
    btn->setScale(3.6f, 1.8f);
    btn->setPosition(Vec2(170, 0));
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

void MenuScene::displayWorm()
{
    row_col size = {20, 18};
    FreePlayGround* playGround = FreePlayGround::create();
    playGround->create(size);
    playGround->setScale(1.4f);
    auto contentSize = playGround->getContentSize();
    playGround->setPosition(Vec2(-contentSize.width / 2, -contentSize.height / 2) + VisibleRect::center());
    playGround->setRotation(45);
    
    auto action = ScaleTo::create(4, 1.2);
    auto action2 = ScaleTo::create(4, 1.4);
    playGround->runAction(RepeatForever::create(Sequence::create(action, action2, nullptr)));
    
    this->addChild(playGround);
    
    setPlayGround(playGround);
    
    auto worm = FreeWorm::create();
    start_point start;
    start.info = {0, 9};
    start.direction = 1;
    
    worm->born(playGround, start);
    worm->setOpacity(150);
    worm->crawl();
}

void MenuScene::onClickPlay(cocos2d::Ref *sender)
{
    _playGround->stopAllActions();
    _playGround->removeMask();
    
    auto scale = ScaleTo::create(0.5f, 1);
    auto rotate = RotateTo::create(0.5f, 0);
    _playGround->runAction(scale);
    _playGround->runAction(rotate);
    
    start_point point;
    point.info = _playGround->getFocusWorm()->getPos();
    point.direction = _playGround->getFocusWorm()->getProperty()->getDirection();
    
    GAME_MGR->setStartPoint(point);
    
    auto logo = (Label*)getChildByTag(logoTag);
    if (logo) {
        logo->stopAllActions();
        auto move = MoveBy::create(0.5f, Vec2(100, 280));
        auto rotate = RotateTo::create(0.5f, 15);
        auto easeMove = EaseBackOut::create(move);
        
        logo->runAction(easeMove);
        logo->runAction(rotate);
    }
    
    auto menu = getChildByTag(menuTag);
    if (menu) {
        menu->stopAllActions();
        auto move = MoveBy::create(0.5f, Vec2(-100, -280));
        auto rotate = RotateTo::create(0.5f, -15);
        auto easeMove = EaseBackOut::create(move);
        
        menu->runAction(easeMove);
        menu->runAction(rotate);
    }
    
    auto action = Sequence::create(DelayTime::create(0.5f),
                                   CallFunc::create(CC_CALLBACK_0(MenuScene::changeScene, this)),
                                   nullptr);
    this->runAction(action);
}

void MenuScene::onClickGameCenter(cocos2d::Ref *sender)
{
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        GameCenter* center = (GameCenter*)GAME_MGR->getGameCenter();
        if (center) {
            center->showScores();
        }
    }
}

void MenuScene::changeScene()
{
    auto scene = TransitionFadeTR::create(0.45f, GameScene::createScene());
    Director::getInstance()->replaceScene(scene);
}