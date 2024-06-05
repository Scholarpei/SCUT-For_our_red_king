#ifndef QTEENERMY_H
#define QTEENERMY_H

#include "spriteobject.h"
#include "standard.h"
#include "animationComponent.h"
#include "animationloader.h"
#include "monster.h"
class QTEEnermy : public SpriteObject
{
public:
    enum class EnermyType{idle,attack,dead};
    explicit QTEEnermy(QObject *parent = nullptr, Game *game = nullptr,int draworder=DRAWORRDER::QTE);
    void attack();//击打一遍，完了会回到idle
    void idle();//强制回到idle
    void dead();
    void Update();
    Monster::MonsterType kindOfenermy;

protected:
    bool isAttack;
    const AnimationLoader& searchAnimation(Monster::MonsterType typeKind,EnermyType typeState);
};

#endif // QTEENERMY_H
