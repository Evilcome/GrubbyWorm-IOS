//
//  FontConfig.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-27.
//
//

#ifndef DigitalWorm_FontConfig_h
#define DigitalWorm_FontConfig_h

#include "cocos2d.h"
USING_NS_CC;

static const TTFConfig FC_ICON = TTFConfig("font/icons.ttf", 40, GlyphCollection::ASCII, nullptr, true, 1);
static const TTFConfig FC_ICON_BIG = TTFConfig("font/icons.ttf", 100, GlyphCollection::ASCII, nullptr, true, 2);

static const TTFConfig FC_NUMBER_SMALL = TTFConfig("font/Stiff Staff.otf", 44, GlyphCollection::ASCII, nullptr, true, 1);
static const TTFConfig FC_NUMBER_NO_BORDER = TTFConfig("font/Stiff Staff.otf", 84, GlyphCollection::ASCII, nullptr, true, 0);
static const TTFConfig FC_NUMBER_NORMAL = TTFConfig("font/Stiff Staff.otf", 84, GlyphCollection::ASCII, nullptr, true, 1);
static const TTFConfig FC_NUMBER_TITLE = TTFConfig("font/Stiff Staff.otf", 100, GlyphCollection::ASCII, nullptr, true, 2);
static const TTFConfig FC_NUMBER_MIDDLE = TTFConfig("font/Stiff Staff.otf", 110, GlyphCollection::ASCII, nullptr, true, 3);
static const TTFConfig FC_NUMBER_BIG = TTFConfig("font/Stiff Staff.otf", 160, GlyphCollection::ASCII, nullptr, true, 5);
static const TTFConfig FC_NUMBER_LOGO = TTFConfig("font/Stiff Staff.otf", 110, GlyphCollection::ASCII, nullptr, true, 6);

#endif
