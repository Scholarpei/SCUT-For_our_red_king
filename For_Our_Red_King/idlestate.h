#ifndef IDLESTATE_H
#define IDLESTATE_H

#include "statebase.h"
#include "gameobject.h"
#include "player.h"
class IdleState : public StateBase
{
public:
    explicit IdleState();
    void onEnter()override;//!<进入该状态调用方法
    void onKeyDown(int key,GameObject* gameObject)override;//!<该状态监听的键盘输入事件
    void onKeyUp(int key,GameObject* gameObject)override;//!<该状态监听的键盘弹起事件
    void onExit()override;//!<离开状态调用方法
};

#endif // IDLESTATE_H
