#include "monster.h"
#include "spritecomponent.h"
#include "movecomponent.h"
#include "game.h"
#include "gameobject.h"
#include "standard.h"
Monster::Monster(QObject *parent,Game* game):
    GameObject(parent,game)
{
    mGame = game;//赋值game对象

    this->mWidth = 48;
    this->mHeight = 60;

    gameObjectType = GameObject::Type::Monster;
    mMonsterState = MonsterState::IDLE;   //初始化Monster状态为idle

    this-> moveCom = new MoveComponent(this);
    this-> fallCom = new FallComponent(this);
    this->animation= new AnimationComponent(this, DRAWORRDER::Monster);
        //设置player精灵drawOrder = standard常量

    animation->resetAnimation(MONSTER::idle);    //预设播放器图片为空闲状态
    animation->play(true);

    this->addComponent(moveCom);
    this->addComponent(fallCom);
    this->addComponent(animation);
    //添加组件到组件数组中
}

void Monster::Update(){

    if(mState == State::EDead)
        return;
    //物体标定为消亡就不再更新了

    for(auto component:mComponents){
        component->Update();
    }
    //按照组件数组更新
}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Monster::collideOthers(GameObject* d)
{
    //to be written
}

//!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
void Monster::beingCollide(GameObject* s)
{
    //to be written
}

void Monster::changePlayerState(MonsterState state)
{


    if(mMonsterState == MonsterState::IDLE){
        animation->resetAnimation(MONSTER::idle);  //输入空闲状态的动画
        animation->play(true);      //开播放
    }
    else if(mMonsterState == MonsterState::JUMPING){
        animation->resetAnimation(MONSTER::jumping);
        animation->play(false);
    }
    else if(mMonsterState == MonsterState::WALKING){
        animation->resetAnimation(MONSTER::walking);
        animation->play(true);
    }
    //动画播放内容根据当前状态决定
}

int Monster::getDirection()
{
    return this->moveDirection;
}

void Monster::setMoveDirection(int dir)
{
    if(dir == 1)
        moveDirection = 1;
    else if(dir == -1)
        moveDirection = -1;
    else qDebug()<<"错误的monster方向设置";
}

float Monster::getSpeedX()
{
    return this->mSpeedX;
}
float Monster::getSpeedY()
{
    return this->mSpeedY;
}

void Monster::setSpeedX(float s)
{
    this->mSpeedX = s;
}
void Monster::setSpeedY(float s)
{
    this->mSpeedY = s;
}

void Monster::notCollide()
{

}


