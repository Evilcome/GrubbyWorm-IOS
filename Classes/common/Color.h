//
//  Color.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-27.
//
//

#ifndef DigitalWorm_Color_h
#define DigitalWorm_Color_h

#include "cocos2d.h"
USING_NS_CC;

static const Color3B C3_DARK_GREEN      = Color3B(30,  104,  35);

static const Color4B C4_DARK_GREEN      = Color4B(30,  104,  35, 255);
static const Color4B C4_LIGHT_GREEN     = Color4B(140, 198, 101, 160);


enum SUGAR_COLORS {
    SGUAR_COLOR_INVLID = -1,
    SUGAR_COLOR_DARK_GREEN = 0,
    SUGAR_COLOR_GREEN,
    SUGAR_COLOR_LIGHT_GREEN,
    SUGAR_COLOR_LIGHT_YELLOW,
    SUGAR_COLOR_GRAY,
    SUGAR_COLOR_MAX
};

static const int     COLORS_INDEX               = SUGAR_COLOR_MAX;
static const Color3B C3_COLORS[COLORS_INDEX]    = {
    Color3B(30, 104, 35),
    Color3B(68, 163, 64),
    Color3B(140, 198, 101),
    Color3B(214, 230, 133),
    Color3B(208, 208, 208)
};

#endif
