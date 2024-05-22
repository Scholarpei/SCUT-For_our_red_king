#include "player.h"
#include "spritecomponent.h"
#include "movecomponent.h"
#include "game.h"
#include "gameobject.h"
#include "playerstatesset.h"
#include "standard.h"
Player::Player(QObject *parent,Game* game):
    GameObject(parent,game)
{
    mGame = game;//赋值game对象

    this->mWidth = 48;
    this->mHeight = 60;

    gameObjectType = GameObject::Type::Player;
    mPlayerState = playerState::IDLE;   //初始化player状态为idle
    _playerStateSet = new PlayerStatesSet(this,this);

    this-> moveCom = new MoveComponent(this);
    this-> fallCom = new FallComponent(this);
    this->animation= new AnimationComponent(this, DRAWORRDER::Player);
                      //设置player精灵drawOrder = standard常量

    animation->resetAnimation(PLAYER::idle);    //预设播放器图片为空闲状态
    animation->play(true);

    this->addComponent(moveCom);
    this->addComponent(fallCom);
    this->addComponent(animation);
    //添加组件到组件数组中
}

void Player::Update(){

    if(mState == State::EDead)
        return;
    //物体标定为消亡就不再更新了

    for(auto component:mComponents){
        component->Update();
    }
    //按照组件数组更新


}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Player::collideOthers(GameObject* d)
{
    //to be written
}

//!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
void Player::beingCollide(GameObject* s)
{
    //to be written
}

void Player::changePlayerState(playerState state)
{
    switch (state)
    {
        case playerState::IDLE:
            this->mPlayerState = playerState::IDLE;
            break;
        case playerState::JUMPING:
            this->mPlayerState = playerState::JUMPING;
            break;
        case playerState::WALKING:
            this->mPlayerState = playerState::WALKING;
            break;
    }

        if(mPlayerState == playerState::IDLE){
            animation->resetAnimation(PLAYER::idle);  //输入空闲状态的动画
            animation->play(true);      //开播放
        }
        else if(mPlayerState == playerState::JUMPING){
            animation->resetAnimation(PLAYER::jumping);
            animation->play(false);
        }
        else if(mPlayerState == playerState::WALKING){
            animation->resetAnimation(PLAYER::walking);
            animation->play(true);
        }
        //动画播放内容根据当前状态决定
}

int Player::getDirection()
{
    return this->moveDirection;
}

void Player::setMoveDirection(int dir)
{
    if(dir == 1)
        moveDirection = 1;
    else if(dir == -1)
        moveDirection = -1;
    else qDebug()<<"错误的player方向设置";
}

float Player::getSpeedX()
{
    return this->mSpeedX;
}
float Player::getSpeedY()
{
    return this->mSpeedY;
}

void Player::setSpeedX(float s)
{
    this->mSpeedX = s;
}
void Player::setSpeedY(float s)
{
    this->mSpeedY = s;
}

void Player::notCollide()
{
    //没有发生碰撞啥都不做
}

//!键盘按下事件处理
void Player::inputKeyPressProcess(int key)
{
    if(mPlayerState == playerState::IDLE){
        _playerStateSet->_idleState->onKeyDown(key,this);
    }
    else if(mPlayerState == playerState::JUMPING){
        _playerStateSet->_jumpingState->onKeyDown(key,this);
    }
    else if(mPlayerState == playerState::WALKING){
        _playerStateSet->_walkingState->onKeyDown(key,this);
    }

}

//!键盘松开事件处理
void Player::inputKeyReleaseProcess(int key)
{
    if(mPlayerState == playerState::IDLE){
        _playerStateSet->_idleState->onKeyUp(key,this);
    }
    else if(mPlayerState == playerState::JUMPING){
        _playerStateSet->_jumpingState->onKeyUp(key,this);
    }
    else if(mPlayerState == playerState::WALKING){
        _playerStateSet->_walkingState->onKeyUp(key,this);
    }
}


