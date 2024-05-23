#include "monster.h"
#include "spritecomponent.h"
#include "movecomponent.h"
#include "game.h"
#include "gameobject.h"
#include "standard.h"
#include "player.h"
Monster::Monster(QObject *parent,Game* game):
    GameObject(parent,game),
    mSpeedX(ACTIONCONST::monsterMoveXSpeed),
    moveDirection(1)
{
    mGame = game;//赋值game对象

    this->mWidth = 48;
    this->mHeight = 60;

    gameObjectType = GameObject::Type::Monster;
    mMonsterState = MonsterState::WALKING;   //初始化Monster状态为idle

    this-> moveCom = new MoveComponent(this);
    this-> fallCom = new FallComponent(this);
    this->animation= new AnimationComponent(this, DRAWORRDER::Monster);
        //设置player精灵drawOrder = standard常量

    animation->resetAnimation(MONSTER::walking);    //预设播放器图片为行走
    animation->play(true);

    this->addComponent(moveCom);
    this->addComponent(fallCom);
    this->addComponent(animation);
    //添加组件到组件数组中
}

void Monster::Update(){

    if(mState == State::EDead)
        return;
    //物体标定为消亡就不再更新�?
    for(auto component:mComponents){
        component->Update();
    }
    //按照组件数组更新
}

//!碰撞其他gameobject的事件处�?(d是this碰撞到的GameObject)
void Monster::movecollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Monster){
        //玩家碰到怪物
        Monster* MonsterPtr = dynamic_cast<Monster*>(d);
        // loseHPEvent();   还没确定扣多少血
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行
    this->mSpeedX = 0;
}

//!碰撞其他gameobject的事件处�?(d是this碰撞到的GameObject)
void Monster::fallcollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Player){
        //玩家碰到怪物
        Player* PlayerPtr = dynamic_cast<Player*>(d);
        // loseHPEvent();
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行
    this->mSpeedY = 0;
}

//!<被碰撞后发生的事件处�?(s是碰撞this的GameObject)
void Monster::beingCollide(GameObject* s)
{
    //to be written
    if(s->gameObjectType == GameObject::Type::Monster){
        //玩家碰到怪物
        Monster* MonsterPtr = dynamic_cast<Monster*>(s);
        // loseHPEvent();
    }
}

//!碰撞其他gameobject的事件movecomponent处理(d是this碰撞到的GameObject)
void Monster::movenotCollide()
{
    //to be written
    //似乎什么都不用�?

}

//!碰撞其他gameobject的事件fallcomponent处理(d是this碰撞到的GameObject)
void Monster::fallnotCollide()
{
    //to be written
    //似乎什么都不用�?
}

int Monster::getDrawDirection()
{
    return this->moveDirection;
}

void Monster::changeMonsterState(MonsterState state)
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
    //动画播放内容根据当前状态决�?
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


