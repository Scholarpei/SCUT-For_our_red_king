#include "idlestate.h"
#include "player.h"

IdleState::IdleState()
{

}

//!进入该状态调用方法
void IdleState::onEnter()
{

}

//!该状态监听的键盘输入事件
void IdleState::onKeyDown(int key,GameObject* gameObject)
{
    if(gameObject->gameObjectType == GameObject::Type::Player){
        Player* playerPtr = dynamic_cast<Player*>(gameObject);
        // qDebug()<<"Idle";
        switch(key)
        {
            case Qt::Key_Right:
                // qDebug()<<"向右";
                playerPtr->setMoveDirection(1);//设置向右
                playerPtr->setSpeedX(ACTIONCONST::playerMoveXSpeed);
                playerPtr->changePlayerState(Player::playerState::WALKING);
                break;
            case Qt::Key_Left:
                // qDebug()<<"向左";
                playerPtr->setMoveDirection(-1);//设置向左
                playerPtr->setSpeedX(ACTIONCONST::playerMoveXSpeed);
                playerPtr->changePlayerState(Player::playerState::WALKING);
                break;
            case Qt::Key_Space:
                // qDebug()<<"跳跃space";
                playerPtr->setSpeedY(ACTIONCONST::playerMoveYSpeed);
                playerPtr->changePlayerState(Player::playerState::JUMPING);
                break;
            case Qt::Key_Up:
                playerPtr->setSpeedY(ACTIONCONST::playerMoveYSpeed);
                playerPtr->changePlayerState(Player::playerState::JUMPING);
                break;
        }
    }


}

//!该状态监听的键盘弹起事件
void IdleState::onKeyUp(int key,GameObject* gameObject)
{

}

//!离开状态调用方法
void IdleState::onExit()
{

}
