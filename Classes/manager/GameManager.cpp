//
//  GameManager.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-22.
//
//

#include "GameManager.h"
#include "AdMobManager.h"
#include "UIManager.h"
#include "LocalStorageManager.h"

#include "GameCenter.h"
#include "GameScene.h"

USING_NS_CC;

GameManager::GameManager()
:_gameCenter(nullptr)
,_gameStatus(GAME_STATUS_STANDBY)
{
    _score.combo = 0;
    _score.combo_max = 0;
    _score.combo_times = 0;
    _score.step = 0;
    _score.trigger = 0;
    _score.total = 0;
}

GameManager::~GameManager()
{
    CC_SAFE_DELETE(_gameCenter);
}

GameManager* GameManager::_instance = nullptr;

GameManager* GameManager::getInstance()
{
    if (_instance == nullptr) {
        _instance = new GameManager();
    }
    
    return _instance;
}

void GameManager::destoryInstance()
{
    CC_SAFE_DELETE(_instance);
}

void GameManager::init()
{
    // init game center in ios
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
        _gameCenter = new GameCenter();
        _gameCenter->login();
    }
}

void GameManager::addCombo(short count /* = 1 */)
{
    _score.combo += count;
	NotificationCenter::getInstance()->postNotification(NOTI_COMBO_VALUE);
}

void GameManager::resetCombo()
{
    if (_score.combo == 0) return;
    
    if (_score.combo > _score.combo_max) {
        _score.combo_max = _score.combo;
    }
    
    _score.combo = 0;
    _score.combo_times++;
	NotificationCenter::getInstance()->postNotification(NOTI_COMBO_VALUE);
}

void GameManager::addStep()
{
    _score.step++;
	NotificationCenter::getInstance()->postNotification(NOTI_STEP_VALUE);
}

int GameManager::addTrigger(short count /* = 1 */)
{
    _score.trigger += count;
	NotificationCenter::getInstance()->postNotification(NOTI_TRIGGER_VALUE);
    
    int add = count;
    _score.combo == 0 ? add = count : add = (count * _score.combo + 1);
    
    _score.total += add;
	NotificationCenter::getInstance()->postNotification(NOTI_TOTAL_VALUE);
    
    return add;
}

void GameManager::setEnergy(count_detail detail)
{
    _energy = detail;
	NotificationCenter::getInstance()->postNotification(NOTI_ENERGY_VALUE);
}

void GameManager::resetScore(bool refresh /* = true */)
{
    _score.combo = 0;
    _score.combo_max = 0;
    _score.combo_times = 0;
    _score.step = 0;
    _score.trigger = 0;
    _score.total = 0;
    
    if (refresh) {
        NotificationCenter::getInstance()->postNotification(NOTI_COMBO_VALUE);
        NotificationCenter::getInstance()->postNotification(NOTI_STEP_VALUE);
        NotificationCenter::getInstance()->postNotification(NOTI_TRIGGER_VALUE);
        NotificationCenter::getInstance()->postNotification(NOTI_TOTAL_VALUE);
    }
}

void GameManager::setGameStatus(short status)
{
    if (_gameStatus != status) {
        _gameStatus = status;
        onGameStatusChange();
    }
}

void GameManager::onGameStatusChange()
{
    switch (_gameStatus) {
        case GAME_STATUS_STANDBY:
            ADMOB_MGR->setBannerViewVisible(false);
            break;
        case GAME_STATUS_RUNNING:
            ADMOB_MGR->setBannerViewVisible(false);
            break;
        case GAME_STATUS_PAUSE:
            ADMOB_MGR->setBannerViewVisible(true);
            break;
        case GAME_STATUS_OVER:
            ADMOB_MGR->setBannerViewVisible(true);
            break;
        default:
            break;
    }
}

int GameManager::getPlayerScore()
{    
    setBestScore(_score.total);
    return _score.total;
}

int GameManager::getBestScore()
{
    return LS_MGR->getBestScore();
}

void GameManager::setBestScore(int value)
{
    if (value > getBestScore()) {
        LS_MGR->setBestScore(value);
        
        // post to game center
        if (_gameCenter != nullptr) {
            _gameCenter->postScore("LB_GrubbyWorm", value);
        }
    }
}

bool GameManager::isNewer()
{
    return LS_MGR->isNewer();
}

void GameManager::pause()
{
    setGameStatus(GAME_STATUS_PAUSE);
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.15f);
    
    auto layer = (GameScene*)UI_MGR->find(LAYER_GAME);
    if (layer != nullptr) {
        layer->pause();
    }
}

void GameManager::play()
{
    setGameStatus(GAME_STATUS_RUNNING);
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
    
    auto layer = (GameScene*)UI_MGR->find(LAYER_GAME);
    if (layer != nullptr) {
        layer->play();
    }
}

void GameManager::over()
{
    setGameStatus(GAME_STATUS_OVER);
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.15f);
    
    auto layer = (GameScene*)UI_MGR->find(LAYER_GAME);
    if (layer != nullptr) {
        layer->over();
    }
}

void GameManager::restart()
{
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
    
    auto scene = TransitionFadeTR::create(0.45f, GameScene::createScene());
    Director::getInstance()->replaceScene(scene);
    
    GAME_MGR->resetScore(false);
}