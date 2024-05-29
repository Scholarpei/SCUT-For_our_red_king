#include "walkingstate.h"
#include "player.h"

WalkingState::WalkingState()
{

}

//!进入该状态调用方法
void WalkingState::onEnter()
{

}

//!该状态监听的键盘输入事件
void WalkingState::onKeyDown(int key,GameObject* gameObject)
{
    if(gameObject->gameObjectType == GameObject::Type::Player){
        qDebug()<<"walking-keydown";
        Player* playerPtr = dynamic_cast<Player*>(gameObject);
        switch(key)
        {
        case Qt::Key_Space:
            // qDebug()<<"jump空格";
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
void WalkingState::onKeyUp(int key,GameObject* gameObject)
{
    if(gameObject->gameObjectType == GameObject::Type::Player){
        qDebug()<<"walking-keyup";
        Player* playerPtr = dynamic_cast<Player*>(gameObject);
        switch(key)
        {
        case Qt::Key_Right:
            // qDebug()<<"向右停止";
            playerPtr->setSpeedX(0);
            playerPtr->changePlayerState(Player::playerState::IDLE);//停止
            break;
        case Qt::Key_Left:
            // qDebug()<<"向左停止";
            playerPtr->setSpeedX(0);
            playerPtr->changePlayerState(Player::playerState::IDLE);//停止
            break;

        }
    }

}

//!离开状态调用方法
void WalkingState::onExit()
{

}

