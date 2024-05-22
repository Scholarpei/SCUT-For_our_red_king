#ifndef STATEBASE_H
#define STATEBASE_H

class GameObject;

class StateBase
{
public:
    explicit StateBase();

    //下面为virtual function
    virtual void onEnter();//!<进入该状态调用方法
    virtual void onKeyDown(int key,GameObject* gameObject);//!<该状态监听的键盘输入事件
    virtual void onKeyUp(int key,GameObject* gameObject);//!<该状态监听的键盘弹起事件
    virtual void onExit();//!<离开状态调用方法

private:

};

#endif // STATEBASE_H
