#ifndef WALKINGSTATE_H
#define WALKINGSTATE_H

#include "statebase.h"
#include "gameobject.h"
#include "player.h"
class WalkingState : public StateBase
{
public:
    explicit WalkingState();
    void onEnter()override;//!<进入该状态调用方法
    void onKeyDown(int key,GameObject* gameObject)override;//!<该状态监听的键盘输入事件
    void onKeyUp(int key,GameObject* gameObject)override;//!<该状态监听的键盘弹起事件
    void onExit()override;//!<离开状态调用方法


};


#endif // WALKINGSTATE_H
