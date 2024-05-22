#include "jumpingstate.h"

#include"standard.h"
JumpingState::JumpingState()
{

}
//!进入该状态调用方法
void JumpingState::onEnter()
{
}

//!该状态监听的键盘输入事件
void JumpingState::onKeyDown(int key,GameObject* gameObject)
{
    if(gameObject->gameObjectType == GameObject::Type::Player){
        Player* playerPtr = dynamic_cast<Player*>(gameObject);
        switch(key)
        {
        case Qt::Key_Right:

            playerPtr->setMoveDirection(1);//设置向右
            playerPtr->setSpeedX(ACTIONCONST::playerMoveXSpeed);

            break;
        case Qt::Key_Left:
            playerPtr->setMoveDirection(-1);//设置向左
            playerPtr->setSpeedX(ACTIONCONST::playerMoveXSpeed);

            break;
        }
    }


}

//!该状态监听的键盘弹起事件
void JumpingState::onKeyUp(int key,GameObject* gameObject)
{
    if(gameObject->gameObjectType == GameObject::Type::Player){
        Player* playerPtr = dynamic_cast<Player*>(gameObject);
        switch(key)
        {
        case Qt::Key_Right:
            playerPtr->setSpeedX(0);

            break;
        case Qt::Key_Left:
            playerPtr->setSpeedX(0);
            break;
        }
    }
}

//!离开状态调用方法
void JumpingState::onExit()
{

}
