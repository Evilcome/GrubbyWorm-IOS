//
//  GameScene.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-28.
//
//

#include "GameScene.h"
#include "PlayGround.h"
#include "ClassicWorm.h"
#include "SugarTrigger.h"
#include "PlayLayer.h"
#include "PauseLayer.h"
#include "GameOverLayer.h"
#include "GameManager.h"
#include "UIManager.h"
#include "Common.h"

USING_NS_CC;

const int playLayerTag = 10;

GameScene::GameScene()
:_playGround(nullptr)
{
    
}

GameScene::~GameScene()
{
    _playGround = nullptr;
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!BaseLayer::init()) {
        return false;
    }
    
    display();
    
    return true;
}

short GameScene::getType()
{
    return LAYER_GAME;
}

void GameScene::display()
{
    GAME_MGR->setGameStatus(GAME_STATUS_RUNNING);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto layer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
    
    this->addChild(layer, 0);
    
    row_col size = {20, 18};
    PlayGround* playGround = PlayGround::create();
    playGround->create(size);
    playGround->setPosition(Vec2::ZERO);
    
    this->addChild(playGround);
    
    setPlayGround(playGround);
    
    auto worm = ClassicWorm::create();
    
    worm->born(playGround, GAME_MGR->getStartPoint());
    worm->crawl();
    
    auto interface = PlayLayer::create();
    this->addChild(interface, 100, playLayerTag);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        return true;
    };
    
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::pause()
{
    auto playLayer = getChildByTag(playLayerTag);
    if (playLayer) {
        playLayer->setVisible(false);
    }
    
    auto pauseLayer = PauseLayer::create();
    this->addChild(pauseLayer, 11);
}

void GameScene::play()
{
    auto playLayer = getChildByTag(playLayerTag);
    if (playLayer) {
        playLayer->setVisible(true);
    }
}

void GameScene::over()
{
    auto playLayer = getChildByTag(playLayerTag);
    if (playLayer) {
        playLayer->setVisible(false);
    }
    
    auto overLayer = GameOverLayer::create();
    this->addChild(overLayer, 12);
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (_playGround == nullptr) return;
    
    if (GAME_MGR->getGameStatus() != GAME_STATUS_RUNNING) return;
    
    auto worm = _playGround->getFocusWorm();
    if (worm == nullptr) return;
    
    if (!worm->isCrawling()) return;
    
    short direction = worm->getProperty()->getDirection();
    
    Vec2 start = touch->getStartLocation();
    Vec2 now = touch->getLocation();
    
    float distance = start.distance(now);
    
    if (distance <= 10) return;
    
    Vec2 offsetVector = now - start;
    float angle = offsetVector.getAngle();
    float cocosAngle = CC_RADIANS_TO_DEGREES(angle);
    
    if (cocosAngle >= 45 && cocosAngle < 135) {
        
        // north
        if (direction != WORM_DIRECTION_SOUTH) worm->turn(WORM_DIRECTION_NORTH);
        
    } else if (cocosAngle >= -45 && cocosAngle < 45) {
        
        // east
        if (direction != WORM_DIRECTION_WEST) worm->turn(WORM_DIRECTION_EAST);
        
    } else if (cocosAngle >= -135 && cocosAngle < -45) {
        
        // south
        if (direction != WORM_DIRECTION_NORTH) worm->turn(WORM_DIRECTION_SOUTH);
        
    } else {
        
        // west
        if (direction != WORM_DIRECTION_EAST) worm->turn(WORM_DIRECTION_WEST);
    }
}
