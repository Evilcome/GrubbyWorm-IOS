//
//  PropertyStruct.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-25.
//
//

#ifndef DigitalWorm_PropertyStruct_h
#define DigitalWorm_PropertyStruct_h

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

/////////////////////////////////////////////////////////
class WormProperty : public Ref
{
public:
	WormProperty() {
        _speed = 0;
        _energy = 0;
        _comboLave = 0.0f;
        _runawayLave = 0.0f;
        _direction = 0;
    };
	~WormProperty() {};
    
public:
    CC_SYNTHESIZE(short, _speed, Speed);
    CC_SYNTHESIZE(short, _energy, Energy);
    CC_SYNTHESIZE(float, _comboLave, ComboLave);
    CC_SYNTHESIZE(float, _runawayLave, RunawayLave);
    CC_SYNTHESIZE(short, _direction, Direction);
    
};

#endif
