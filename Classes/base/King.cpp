//
//  King.cpp
//  DigitalWorm
//
//  Created by Wayne on 14-7-24.
//
//

#include "King.h"
#include "Observer.h"
#include "PlayGround.h"
#include "TriggerHeaders.h"
#include <algorithm>
USING_NS_CC;

King::King()
:_add(0.0f)
,_observer(nullptr)
{
}

King::~King()
{
}

bool King::init()
{
    // init sugar refresh formation.
    _initSugarFormation();
    
    return true;
}

void King::monitor(float delta)
{
    if (_observer->getSugerCount() < expectSugarCount()) {
        
        _add += (delta * 1000);
        if (_add >= CREATE_TRIGGER_DELAY)
        {
            _add = 0.0f;
            addSuger();
        }
    }
}

bool King::createTrigger(short type, row_col point)
{
    if (_observer == nullptr) return false;
    
    PlayGround* playGround = _observer->getPlayGround();
    if (playGround == nullptr) return false;
    
    //log("----- row : %d, col : %d ----- %d", point.row, point.col, type);
    
    if (isEmptyPos(point)) {
        
        switch (type) {
            case TRIGGER_TYPE_SUGAR:
            {
                auto sugar = SugarTrigger::create();
                colorRule(sugar);
                sugar->addTo(playGround, point);
            }
                break;
            case TRIGGER_TYPE_HONEY:
            {
                auto honey = HoneyTrigger::create();
                honey->addTo(playGround, point);
            }
                break;
            case TRIGGER_TYPE_GRUBBY:
            {
                auto grubby = GrubbyTrigger::create();
                grubby->addTo(playGround, point);
            }
                break;
            default:
                break;
        }
        
        return true;
    }
    
    return false;
}

bool King::isEmptyPos(row_col point)
{
    if (point.row == -1 || point.col == -1) {
        return false;
    }
    
    if (_observer != nullptr) {
        
        std::vector<row_col> excludePos;
        Vector<Trigger* >& triggers = _observer->getTriggers();
        
        for(auto each : triggers)
        {
            row_col pos = each->getPos();
            if (pos.row == point.row && pos.col == point.col) {
                return false;
            }
        }
        
        return true;
    }
    
    return false;
}

short King::expectSugarCount()
{
//    PlayGround* playGround = _observer->getPlayGround();
//    row_col size = playGround->getPlayGroundSize();
//    
//    return (size.row * size.col / EXIST_TRIGGER_DENSITY);

    return SUGAR_TRIGGER_COUNT;
}

void King::addSuger()
{
    short type = TRIGGER_TYPE_SUGAR;
    
    // sugar weight
    int weight = int(CCRANDOM_0_1() * 100);
    if (weight < 20) {
        type = TRIGGER_TYPE_HONEY;
    }
    
    createTrigger(type, getRandomEmptyPos());
}

void King::colorRule(SugarTrigger* sugar)
{
    Color3B color;
    
    if (_sugarFormation.size() > 0) {
        color = C3_COLORS[_sugarFormation.at(0)];
        _sugarFormation.erase(_sugarFormation.begin());
    } else {
        short random = CCRANDOM_0_1() * COLORS_INDEX;
        random >= COLORS_INDEX ? random = 0 : random = random;
        color = C3_COLORS[random];
    }
    
    sugar->setSugarColor(color);
}

row_col King::getRandomEmptyPos()
{
    if (_observer != nullptr) {
        
        short count = _observer->getSugerCount();
        
        if (count <= 2) {
            
            std::vector<row_col> excludePos;
            row_col focusPoint = _observer->getFocusPoint();
            excludePos.push_back(focusPoint);
            
            row_col_range range = _getFixSize(focusPoint);
            return _getRandomValue(excludePos, range.to, range.from);
            
            
        } else {
            
            std::vector<row_col> excludePos;
            Vector<Trigger* >& triggers = _observer->getTriggers();
            
            for(auto each : triggers)
            {
                row_col pos = each->getPos();
                excludePos.push_back(pos);
            }
            
            excludePos.push_back(_observer->getFocusPoint());
            
            PlayGround* playGround = _observer->getPlayGround();
            if (playGround != nullptr) {
                row_col size = playGround->getPlayGroundSize();
                return _getRandomValue(excludePos, size);
            }
        }
    }
    
    return {-1, -1};
}

void King::supplementSugarFormation(cocos2d::Color3B& color)
{
    for (short i = 0; i != SUGAR_COLOR_MAX; ++i) {
        if (C3_COLORS[i] == color) {
            _sugarFormation.push_back(i);
            return;
        }
    }
}

row_col King::_getRandomValue(std::vector<row_col> &points, row_col &size, row_col from /* = {0, 0} */)
{
    int randomRow = from.row + CCRANDOM_0_1() * (size.row - 1 - from.row);
    int randomCol = from.col + CCRANDOM_0_1() * (size.col - 1 - from.col);
    
    std::vector<row_col>::iterator ite = points.begin();
    for (; ite != points.end(); ++ite) {
        row_col point = *ite;
        
        if (point.row == randomRow && point.col == randomCol) {
            return _getRandomValue(points, size, from);
        }
    }
    
    return {randomRow, randomCol};
}

void King::_initSugarFormation()
{
    for (short i = 0; i != SUGAR_COLOR_MAX; ++i) {
        _sugarFormation.push_back(i);
    }
    
    std::vector<short> vect;
    
    short count = expectSugarCount() - SUGAR_COLOR_MAX;
    short times = count / SUGAR_COLOR_MAX;
    
    for (short i = 0; i != times; ++i) {
        for(int j = 0; j < SUGAR_COLOR_MAX; ++j)
        {
            vect.push_back(j);
        }
    }
    random_shuffle(vect.begin(), vect.end());
    
    for (short i = 0; i != vect.size(); ++i) {
        _sugarFormation.push_back(vect.at(i));
    }
}

row_col_range King::_getFixSize(row_col point)
{
    row_col wrapSize = _observer->getPlayGround()->getPlayGroundSize();
    
    row_col_range range;
    
    range.to.row = point.row + 6;
    range.to.col = point.col + 4;
    
    range.to.row > wrapSize.row ? range.to.row = wrapSize.row : range.to.row = range.to.row;
    range.to.col > wrapSize.col ? range.to.col = wrapSize.col : range.to.col = range.to.col;
    
    range.from.row = point.row - 6;
    range.from.col = point.col - 4;
    
    range.from.row < 0 ? range.from.row = 0 : range.from.row = range.from.row;
    range.from.col < 0 ? range.from.col = 0 : range.from.col = range.from.col;
    
    if (range.from.row == 0) {
        range.to.row += (6 - point.row);
    }
    
    if (range.from.col == 0) {
        range.to.col += (4 - point.col);
    }
    
//    log("from row: %d  to row: %d", range.from.row, range.to.row);
//    log("from col: %d  to col: %d", range.from.col, range.to.col);
    
    return range;
}