//
//  ClassicWorm.h
//  DigitalWorm
//
//  Created by Wayne on 14-7-18.
//
//

#ifndef __DigitalWorm__ClassicWorm__
#define __DigitalWorm__ClassicWorm__

#include "Worm.h"

#define WORM_CLASSIC_YUAN_COUNT     5

class Yuan;
class ClassicWorm : public Worm
{
public:
    ClassicWorm();
    ~ClassicWorm();
    
    CREATE_FUNC(ClassicWorm);
    
    virtual bool    init();
    virtual void    update(float delta) override;
    
public:
    virtual void    born(PlayGround* playGround, start_point start);
    virtual void    die();
    virtual void    doDie();
    virtual void    doCrawl();
    virtual row_col getPos();
    
    virtual void    colorRule();
    virtual void    changeColor();
    virtual void    colorChangeRule();
    
    virtual void    onTrigger(Trigger* trigger);
    virtual void    refreshView();
    virtual void    addGrubby();
    virtual void    showColorTip();
    
    virtual void    showAdd(int add);
    
protected:
    void            _playComboEffect(float speed);
    void            _comboEffect();
    void            _removeMark(Yuan* yuan);
    void            _notifyComboLave();
    void            _notifyCrazyLave();
    void            _supplementSugarFormation(cocos2d::Color3B color);
    void            _setCombo();
    void            _warningEffect();
    
    void            _prepareRunaway();
    void            _runawayPrepared();
    
    Yuan*           _yuans[WORM_CLASSIC_YUAN_COUNT];

    CC_SYNTHESIZE(short, _grubby, Grubby);
    
    bool            _warning;
    
};

#endif /* defined(__DigitalWorm__ClassicWorm__) */
