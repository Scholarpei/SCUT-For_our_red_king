#ifndef JUMPINGSTATE_H
#define JUMPINGSTATE_H

#include "statebase.h"
#include "gameobject.h"
#include "player.h"
class JumpingState : public StateBase
{
public:
    explicit JumpingState();
    void onEnter()override;//!<进入该状态调用方法
    void onKeyDown(int key,GameObject* gameObject)override;//!<该状态监听的键盘输入事件
    void onKeyUp(int key,GameObject* gameObject)override;//!<该状态监听的键盘弹起事件
    void onExit()override;//!<离开状态调用方法


};

#endif // JUMPINGSTATE_H
