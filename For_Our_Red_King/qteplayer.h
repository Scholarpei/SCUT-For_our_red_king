#ifndef QTEPLAYER_H
#define QTEPLAYER_H

#include "spriteobject.h"
#include "standard.h"
#include "animationComponent.h"
#include "animationloader.h"

class QTEPlayer : public SpriteObject
{
public:
    explicit QTEPlayer(QObject *parent = nullptr, Game *game = nullptr,int draworder=DRAWORRDER::QTE);
    void attack1();//击打一遍，完了会回到idle
    void attack2();
    void attack3();
    void idle();//强制回到idle
    void Update();
    virtual void inputKeyPressProcess(int key)override;
protected:
    bool isAttack;
};

#endif // QTEPLAYER_H
