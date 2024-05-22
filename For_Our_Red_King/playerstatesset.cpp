#include "playerstatesset.h"

PlayerStatesSet::PlayerStatesSet(QObject *parent,GameObject* gameObject)
    : QObject{parent}
{
    mGameObject = gameObject;
    _idleState = new IdleState;
    _jumpingState = new JumpingState;
    _walkingState = new WalkingState;
}
