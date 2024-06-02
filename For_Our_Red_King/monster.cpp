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

    gameObjectType = GameObject::Type::Monster;
    mMonsterState = MonsterState::WALKING;   //初始化Monster状态为walking
    mWidth = MONSTER::Monster_Width;
    mHeight = MONSTER::Monster_Height;
    this->setPosition(QVector2D(100,320));   //怪物位置也需要确定好
    changeTheFightingAnimation = 0;


    this-> moveCom = new MoveComponent(this);
    this-> fallCom = new FallComponent(this);
    this->animation= new AnimationComponent(this, DRAWORRDER::Monster);
    this->mSpeedX = ACTIONCONST::monsterMoveXSpeed;
        //设置player精灵drawOrder = standard常量

    animation->resetAnimation(MONSTER::walking);    //预设播放器图片为行走
    animation->play(true);

    this->addComponent(moveCom);
    this->addComponent(fallCom);
    this->addComponent(animation);
    //添加组件到组件数组中
}

void Monster::Update(){
    loseHP_timeCount ++;  //扣血限制计时器更新
    if(this->mMonsterState == MonsterState::FIGHTING)
        changeTheFightingAnimation++;      //对是否战斗播放做特判
    if(mState == State::EDead)
        return;
    //物体标定为消亡就不再更新

    QVector2D playerPosition = mGame->mPlayer->getPosition();
    float deltaDistance = std::sqrt(std::pow(playerPosition.x() - this->getPosition().x(),2)+std::pow(playerPosition.y() - this->getPosition().y(),2));
    if(deltaDistance <= QTE::leastQTEDistance){
        //在可进行qte的范围之内
        if(!setQteFlag){
            setQteFlag = true;
            //生成
        }
    }
    else{
        //超出可进行qte的范围之外
        if(setQteFlag){
            setQteFlag = false;

        }
    }
    //判断怪物跟玩家距离并以此为依据决定是否可以进行qte

    for(auto component:mComponents){
        component->Update();
    }
    //按照组件数组更新
}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Monster::movecollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Player){
        //玩家碰到怪物
        Player* PlayerPtr = dynamic_cast<Player*>(d);
        changeTheFightingAnimation =0;
        this->moveDirection =  -(PlayerPtr->getDirection());    //让怪物朝向人物，发动攻击
        changeMonsterState(MonsterState::FIGHTING);
        this->mGame->mPlayer->loseHPEvent(5);        //玩家掉血，在Player类中实现
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行并切换运动方向
    this->moveDirection = -this->moveDirection;
}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Monster::fallcollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Player){
        //玩家碰到怪物
        Player* PlayerPtr = dynamic_cast<Player*>(d);
        this->mGame->mPlayer->loseHPEvent(5);        //玩家掉血，在Player类中实现
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行
    this->mSpeedY = 0;
}

//!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
void Monster::beingCollide(GameObject* s)
{
    //to be written
    if(s->gameObjectType == GameObject::Type::Player){
        //玩家碰到怪物
        Player* PlayerPtr = dynamic_cast<Player*>(s);
        this->moveDirection =  -(PlayerPtr->getDirection());    //让怪物朝向人物，发动攻击
        changeMonsterState(MonsterState::FIGHTING);
        //loseHPEvent();                                //玩家掉血，在Player类中实现
    }
}

//!碰撞其他gameobject的事件movecomponent处理(d是this碰撞到的GameObject)
void Monster::movenotCollide(QVector2D& lastposition)
{
    if(changeTheFightingAnimation>=32){
        changeMonsterState(MonsterState::WALKING);
    }

}

//!碰撞其他gameobject的事件fallcomponent处理(d是this碰撞到的GameObject)
void Monster::fallnotCollide(QVector2D& lastposition)
{
    //说明要脱离平台、地面了，阻止发生
    this->setPosition(lastposition);
    this->mSpeedY = 0;
}

int Monster::getDrawDirection()
{
    return this->moveDirection;
}

void Monster::changeMonsterState(MonsterState state)
{

    if(this->mMonsterState == MonsterState::FIGHTING){
        changeTheFightingAnimation = 0;
    }

    switch (state)
    {
    case MonsterState::IDLE:
        this->mMonsterState = MonsterState::IDLE;
        break;
    case MonsterState::WALKING:
            this->mMonsterState = MonsterState::WALKING;
        break;
    case MonsterState::FIGHTING:
        this->mMonsterState = MonsterState::FIGHTING;
        break;
    }


    if(mMonsterState == MonsterState::WALKING){
        changeTheFightingAnimation = 0;
        this->setSpeedX(ACTIONCONST::monsterMoveXSpeed);
        animation->resetAnimation(MONSTER::walking);
        animation->play(true);
    }
    else if(mMonsterState == MonsterState::FIGHTING){
        this->setSpeedX(0);
        animation->resetAnimation((MONSTER::fighting));
        animation->pause();
        animation->play(true);
    }
    else if(mMonsterState == MonsterState::IDLE){
        animation->resetAnimation((MONSTER::idle));
        animation->play(true);
    }
    //动画播放内容根据当前状态决定
}

void Monster::loseHPEvent(int num)
{
    if(loseHP_timeCount < MONSTER::loseHPTimePeriod)
        return ;
    //用于限制扣血的时间间隔

    loseHP_timeCount = 0;  //扣血计时归零

    if(this->HP  > num)
        this->HP -= num;
    else{
        HP = 0;

        //触发Monster死亡
    }
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


