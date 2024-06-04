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
    mMonsterType = MonsterType::Cyborg;      //注意怪物类型
    changeTheFightingAnimation = 0;
    deathFrime = 0;

    this-> moveCom = new MoveComponent(this);
    this-> fallCom = new FallComponent(this);
    this->animation= new AnimationComponent(this, DRAWORRDER::Monster);

    this->exclamationAnimation = new NewAnimationComponent(this,DRAWORRDER::Exclamation);
    exclamationAnimation->resetAnimation(MONSTER::exclamation);
    exclamationAnimation->setDisplay(false);    //感叹号flag要设置刚开始不可见
    exclamationAnimation->setOffset(MONSTER::exclamationXOffset,MONSTER::exclamationYOffset);
    exclamationAnimation->setRect(MONSTER::ExclamationWidth,MONSTER::ExclamationHeight);

    this->mSpeedX = ACTIONCONST::monsterMoveXSpeed;
        //设置player精灵drawOrder = standard常量

    this->chooseAnimation(mMonsterType,mMonsterState);       //预设播放器图片为行走

    this->addComponent(moveCom);
    this->addComponent(fallCom);
    this->addComponent(animation);
    this->addComponent(exclamationAnimation);
    //添加组件到组件数组中
}

InterfaceMonster Monster::intoInterface()
{
    return InterfaceMonster(this->getPosition().x(),this->getPosition().y());
}

void Monster::Update(){
    loseHP_timeCount ++;  //扣血限制计时器更新
    if(mMonsterState == MonsterState::DYING){
        deathFrime++;
        if(deathFrime == 30){
            this->mState = State::EDead;                //优化人物死亡不再攻击，将player移除
        }
    }
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
            this->exclamationAnimation->setTransformDirection(1);
            this->exclamationAnimation->show(false);
            //生成
        }
    }
    else{
        //超出可进行qte的范围之外
        if(setQteFlag){
            setQteFlag = false;
            this->exclamationAnimation->setTransformDirection(0);
            this->exclamationAnimation->show(false);
            // this->exclamationAnimation->setDisplay(false);
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
        this->moveDirection = (PlayerPtr->getPosition().x()-this->getPosition().x()<0)?-1:1;    //让怪物朝向人物，发动攻击
        changeMonsterState(MonsterState::FIGHTING);
        this->mGame->mPlayer->loseHPEvent(5);        //玩家掉血，在Player类中实现
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行并切换运动方向
    if(d->gameObjectType != GameObject::Type::Player)
        this->moveDirection = -this->moveDirection;
}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Monster::fallcollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Player){
        //玩家碰到怪物
        Player* PlayerPtr = dynamic_cast<Player*>(d);
        this->mGame->mPlayer->loseHPEvent(5);        //玩家掉血
    }

    this->initialGroundFlag = true;//已经落地的flag要设置为true

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行
    this->mSpeedY = 4;
}

//!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
void Monster::beingCollide(GameObject* s)
{
    //to be written
    if(s->gameObjectType == GameObject::Type::Player){
        //玩家碰到怪物
        Player* PlayerPtr = dynamic_cast<Player*>(s);
        changeTheFightingAnimation =0;
        this->moveDirection = (PlayerPtr->getPosition().x()-this->getPosition().x()<0)?-1:1;    //让怪物朝向人物，发动攻击
        changeMonsterState(MonsterState::FIGHTING);
        this->mGame->mPlayer->loseHPEvent(5);        //玩家掉血
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
    if(this->initialGroundFlag){
        this->setPosition(lastposition);
        this->moveDirection = - this->moveDirection;
    }
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
        this->chooseAnimation(mMonsterType,mMonsterState);
    }
    else if(mMonsterState == MonsterState::FIGHTING){
        this->setSpeedX(0);
        this->chooseAnimation(mMonsterType,mMonsterState);
    }
    else if(mMonsterState == MonsterState::IDLE){
        this->chooseAnimation(mMonsterType,mMonsterState);
    }
    else if(mMonsterState == MonsterState::DYING){
        this->chooseAnimation(mMonsterType,mMonsterState);
    }
    //动画播放内容根据当前状态决定
}

void Monster::loseHPEvent(int num)
{
    qDebug("time%d",loseHP_timeCount);
    if(loseHP_timeCount < MONSTER::loseHPTimePeriod)
        return ;
    //用于限制扣血的时间间隔
    qDebug()<<"monster loseHP";
    loseHP_timeCount = 0;  //扣血计时归零

    if (this->HP <= num)
    {
        HP = 0;
        if(mMonsterState == MonsterState::DYING){
            return;
        }
        changeMonsterState(MonsterState::DYING);
        // 触发Monster死亡
    }
    else if(this->HP - num > MONSTER::MaxHP)
    {
        HP = MONSTER::MaxHP;
    }
    else
    {
        this->HP -= num;
    }
}

void Monster:: chooseAnimation(MonsterType type,MonsterState state){
    switch(type)
    {
    case MonsterType::Biker:

        if(mMonsterState == MonsterState::IDLE){
        animation->resetAnimation(MONSTER::Bikeridle);
        animation->play(true);
        }
        else if(mMonsterState == MonsterState::WALKING){
            animation->resetAnimation(MONSTER::Bikerwalking);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::FIGHTING){
            animation->resetAnimation((MONSTER::Bikerfighting));
            animation->pause();
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::DYING){
            animation->resetAnimation(MONSTER::Bikerdead);
            animation->play(false);
        }
        break;
    case MonsterType::Batman:

        if(mMonsterState == MonsterState::IDLE){
            animation->resetAnimation(MONSTER::Batmanidle);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::WALKING){
            animation->resetAnimation(MONSTER::Batmanwalking);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::FIGHTING){
            animation->resetAnimation(MONSTER::Batmanfighting);
            animation->pause();
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::DYING){
            animation->resetAnimation(MONSTER::Batmandead);
            animation->play(false);
        }
        break;
    case MonsterType::Cyborg:

        if(mMonsterState == MonsterState::IDLE){
            animation->resetAnimation(MONSTER::Cyborgidle);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::WALKING){
            animation->resetAnimation(MONSTER::Cyborgwalking);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::FIGHTING){
            animation->resetAnimation(MONSTER::Cyborgfighting);
            animation->pause();
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::DYING){
            animation->resetAnimation(MONSTER::Cyborgdead);
            animation->play(false);
        }
        break;
    case MonsterType::Robot:
        if(mMonsterState == MonsterState::IDLE){
            animation->resetAnimation(MONSTER::Robotidle);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::WALKING){
            animation->resetAnimation(MONSTER::Robotwalking);
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::FIGHTING){
            animation->resetAnimation(MONSTER::Robotfighting);
            animation->pause();
            animation->play(true);
        }
        else if(mMonsterState == MonsterState::DYING){
            animation->resetAnimation(MONSTER::Robotdead);
            animation->play(false);
        }
        break;

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


