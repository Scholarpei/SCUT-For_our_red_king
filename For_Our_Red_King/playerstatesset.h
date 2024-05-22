#ifndef PLAYERSTATESSET_H
#define PLAYERSTATESSET_H

#include <QObject>
#include "gameobject.h"
#include "idlestate.h"
#include"jumpingstate.h"
#include"walkingstate.h"

class PlayerStatesSet : public QObject
{
    Q_OBJECT
public:
    explicit PlayerStatesSet(QObject *parent = nullptr,GameObject* gameObject = nullptr);
    IdleState* _idleState;
    JumpingState* _jumpingState;
    WalkingState* _walkingState;
    //存储player所有的状态，用以指向新的状态
private:
    GameObject* mGameObject;
signals:
};

#endif // PLAYERSTATESSET_H
