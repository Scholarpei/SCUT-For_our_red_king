#include "player.h"
#include "movecomponent.h"
#include "game.h"
#include "gameobject.h"
#include "playerstatesset.h"
#include "standard.h"
#include "monster.h"
Player::Player(QObject *parent,Game* game):
    GameObject(parent,game)
{
    mGame = game;//赋值game对象

    mWidth = PLAYER::Player_Width;
    mHeight = PLAYER::Player_Height;

    this->setPosition(QVector2D(50,50));
    mSoundPlayer = new MusicPlayer;
    changeTheFightingAnimation = 0;
    gameObjectType = GameObject::Type::Player;
    mPlayerState = playerState::IDLE;   //初始化player状态为idle
    _playerStateSet = new PlayerStatesSet(this,this);

    this-> moveCom = new MoveComponent(this);
    this-> fallCom = new FallComponent(this);
    this->animation= new AnimationComponent(this, DRAWORRDER::Player);
                      //设置player精灵drawOrder = standard常量

    animation->resetAnimation(PLAYER::idle);    //预设播放器图片为空闲状态
    animation->play(true);

}

Player::~Player()
{
    qDebug()<<"Player";
    delete mSoundPlayer;
}

// Player::Player(QObject *parent,class Game* game,InterfacePlayer i):
//     GameObject(parent,game)
// {
//     this->setPosition(QVector2D(i.x,i.y));   //通过interface设置Player位置

//     //下面与原默认的不含Interface构造函数内容相同

//     mGame = game;//赋值game对象


//     mWidth = PLAYER::Player_Width;
//     mHeight = PLAYER::Player_Height;

//     gameObjectType = GameObject::Type::Player;
//     mPlayerState = playerState::IDLE;   //初始化player状态为idle
//     _playerStateSet = new PlayerStatesSet(this,this);

//     this-> moveCom = new MoveComponent(this);
//     this-> fallCom = new FallComponent(this);
//     this->animation= new AnimationComponent(this, DRAWORRDER::Player);
//         //设置player精灵drawOrder = standard常量

//     animation->resetAnimation(PLAYER::idle);    //预设播放器图片为空闲状态
//     animation->play(true);

//     this->addComponent(moveCom);
//     this->addComponent(fallCom);
//     this->addComponent(animation);
//     //添加组件到组件数组中
// }

// InterfacePlayer Player::intoInterface()
// {
//     return InterfacePlayer(this->getPosition().x(),this->getPosition().y(),this->getHP());
// }

void Player::Update(){

    loseHP_timeCount ++ ;   //扣血限制计时器更新
    if(this->mPlayerState == playerState::FIGHTING)
        changeTheFightingAnimation++;      //对是否战斗播放做特判
    if(mState == State::EDead)
        return;
    //物体标定为消亡就不再更新了

    for(auto component:mComponents){
        component->Update();
    }
    //按照组件数组更新

}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Player::movecollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Monster){
        //玩家碰到怪物
        Monster* MonsterPtr = dynamic_cast<Monster*>(d);
        // loseHPEvent();   还没确定扣多少血
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行
    // this->mSpeedX = 0;

}

//!碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
void Player::fallcollideOthers(GameObject* d,QVector2D& lastposition)
{
    //to be written
    if(d->gameObjectType == GameObject::Type::Monster){
        //玩家碰到怪物
        Monster* MonsterPtr = dynamic_cast<Monster*>(d);
        // loseHPEvent();
    }

    this->setPosition(lastposition);
    //若发生碰撞，让移动不执行
    this->mSpeedY = 0;
    if(this->mPlayerState == playerState::JUMPING){
        // this->mSpeedX = 0;
        if(!this->jumpFinalStateDecision)
             this->changePlayerState(playerState::WALKING);
        else{
            this->changePlayerState(playerState::IDLE);
            this->mSpeedX = 0;
        }
        this->jumpFinalStateDecision = 1;
    }
}

//!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
void Player::beingCollide(GameObject* s)
{
    //to be written
    if(s->gameObjectType == GameObject::Type::Monster){
        //玩家碰到怪物
        Monster* MonsterPtr = dynamic_cast<Monster*>(s);
        // loseHPEvent();
    }
}

//!碰撞其他gameobject的事件movecomponent处理(d是this碰撞到的GameObject)
void Player::movenotCollide(QVector2D& lastposition)
{
    if(changeTheFightingAnimation>=32){
        changePlayerState(playerState::IDLE);
    }
    //to be written
    //似乎什么都不用做
}

//!碰撞其他gameobject的事件fallcomponent处理(d是this碰撞到的GameObject)
void Player::fallnotCollide(QVector2D& lastposition)
{
    //to be written
    //似乎什么都不用做
}

int Player::getDrawDirection()
{
    return this->moveDirection;
}


void Player::changePlayerState(playerState state)
{
    this->mSoundPlayer->stop();
    if(this->mPlayerState == playerState::FIGHTING){
        changeTheFightingAnimation = 0;
    }

    switch (state)
    {
        case playerState::IDLE:
            this->mPlayerState = playerState::IDLE;
            break;
        case playerState::JUMPING:
            this->mSoundPlayer->play(PLAYER::jumpSoundURL,false);
            if(this->mPlayerState == playerState::WALKING)
                jumpFinalStateDecision = 0;
            this->mPlayerState = playerState::JUMPING;
            break;
        case playerState::WALKING:
            this->mSoundPlayer->play(PLAYER::walkSoundURL,true);
            this->mPlayerState = playerState::WALKING;
            break;
        case playerState::DYING:
            //还需插入音效
            this->mPlayerState = playerState::DYING;
            break;
        case playerState::FIGHTING:
            this->mPlayerState = playerState::FIGHTING;
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
        else if(mPlayerState == playerState::DYING){
            animation->resetAnimation(PLAYER::dead);
            animation->play(false);
            }
        else if(mPlayerState == playerState::FIGHTING){
            animation->resetAnimation(PLAYER::attack);
            animation->play(false);
        }
        //动画播放内容根据当前状态决定
}

void Player::loseHPEvent(int num)
{
    if(loseHP_timeCount < PLAYER::loseHPTimePeriod)
        return ;
    //用于限制扣血的时间间隔

    loseHP_timeCount = 0;  //扣血计时归零

    this->mGame->mStatistic.maxCombos = 0;//combo归零

    if (this->HP <= num)
    {
        HP = 0;
        this->mGame->mStatistic.maxPassLevelNumber = 0;//过关归零
        if(mPlayerState == playerState::DYING){
            return;
        }
        changePlayerState(playerState::DYING);
        QTimer::singleShot(1000,this,[=](){
            this->mGame->mGoToNextLevel = 1;
        });
    }
    else if(this->HP - num > PLAYER::MaxHP)
    {
        HP = PLAYER::MaxHP;
    }
    else
    {
        this->HP -= num;
    }
}

int Player::getDirection()
{
    return this->moveDirection;
}

int Player::getHP()
{
    return this->HP;
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

void Player::setHP(int hp){
    this->HP = hp;
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

void Player::initialByInterface(InterfacePlayer mplayer){
    this->setPosition(QVector2D(mplayer.x,mplayer.y));
    this->setHP(mplayer.HP);
}


