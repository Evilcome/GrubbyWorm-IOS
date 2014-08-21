#include "AppDelegate.h"
#include "MenuScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("Digital Worm", Rect(0, 0, 568, 320), 1);
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();

    // run
    director->runWithScene(scene);
    
    // init game
    initGame();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    
    if (GAME_MGR->getGameStatus() == GAME_STATUS_RUNNING) {
        GAME_MGR->pause();
    }
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initGame() {
    GAME_MGR->init();
    
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.2f);
}
