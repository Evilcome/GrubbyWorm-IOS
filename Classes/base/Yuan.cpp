//
//  Yuan.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-21.
//
//

#include "Yuan.h"
USING_NS_CC;

Yuan::Yuan()
:_grid(nullptr)
{
    
}

Yuan::~Yuan()
{
    _grid = nullptr;
}

bool Yuan::init()
{
    if (!Node::init()) {
        return false;
    }
    
    _grid = Sprite::create("base.png");
    if (_grid != nullptr) {
        this->addChild(_grid);
    }
    
    _nowPos = {0, 0};
    _fromPos = {0, 0};
    
    return true;
}

void Yuan::setGridColor(const cocos2d::Color3B &color)
{
    if (_grid != nullptr) {
        _grid->setColor(color);
    }
}

const Color3B& Yuan::getGridColor()
{
    if (_grid != nullptr) {
        return _grid->getColor();
    }
    
    return Color3B::WHITE;
}

void Yuan::setGridStartPos(row_col pos)
{
    setFromPos(pos);
    setNowPos(pos);
}

void Yuan::setGridPos(row_col pos)
{
    setFromPos(_nowPos);
    setNowPos(pos);
}