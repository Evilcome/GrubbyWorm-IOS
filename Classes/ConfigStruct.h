//
//  ConfigStruct.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-25.
//
//

#ifndef DigitalWorm_ConfigStruct_h
#define DigitalWorm_ConfigStruct_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

/////////////////////////////////////////////////////////
class WormConfig : public Ref
{
public:
	WormConfig() {
        _normalSpeed = 0;
        _comboSpeed = 0;
        _runawaySpeed = 0;
        _comboLast = 0;
        _consume = 0;
        _energy = 0;
        _runawayCount = 0;
        _runawayLast = 0;
    };
	~WormConfig() {};
    
public:
    CC_SYNTHESIZE(short, _normalSpeed, NormalSpeed);
    CC_SYNTHESIZE(short, _comboSpeed, ComboSpeed);
    CC_SYNTHESIZE(short, _comboLast, ComboLast);
    CC_SYNTHESIZE(short, _runawaySpeed, RunawaySpeed);
    CC_SYNTHESIZE(short, _consume, Consume);
    CC_SYNTHESIZE(short, _energy, Energy);
    CC_SYNTHESIZE(short, _runawayCount, RunawayCount);
    CC_SYNTHESIZE(short, _runawayLast, RunawayLast);
    
};

#endif
