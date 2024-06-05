#include "qteplayer.h"
#include "standard.h"
#include "animationComponent.h"
QTEPlayer::QTEPlayer(QObject *parent, Game *game,int draworder)
    :SpriteObject(parent,game,draworder)
{
    this->isAttack=0;
    this->setNeedDraw(0);
    this->setDirection(1);

    this->setWidth(QTE::playerWidth);
    this->setHeight(QTE::playerHeight);
    this->setPosition(QTE::playerPosistion.x(),QTE::playerPosistion.y());
    this->setOpacity(0.3);
    reload();

    this->sprite->resetAnimation(PLAYER::idle);
    this->sprite->setRepeat(1);
}
//击打一遍，完了会回到idle
void QTEPlayer::attack1(){
    this->sprite->resetAnimation(PLAYER::attack1);
    isAttack=1;
    this->sprite->play(0);
}
void QTEPlayer::attack2(){
    this->sprite->resetAnimation(PLAYER::attack2);
    isAttack=1;
    this->sprite->play(0);
}
void QTEPlayer::attack3(){
    this->sprite->resetAnimation(PLAYER::attack3);
    isAttack=1;
    this->sprite->play(0);
}


void QTEPlayer::idle(){
    this->isAttack=0;
    this->sprite->resetAnimation(PLAYER::idle);
    this->sprite->play(1);
}
void QTEPlayer::inputKeyPressProcess(int key){
    switch(key){
    case 'J':
        attack1();
        break;
    case 'K':
        attack2();
        break;
    case 'L':
        attack3();
        break;
    case 'O':
        idle();
        break;
    case 'U':
        this->setNeedDraw(1);
        break;
        }
}
void QTEPlayer::Update(){
    if(isAttack)
    {
        if(!this->sprite->isPlaying)
        {
            this->sprite->resetAnimation(PLAYER::idle);
            this->sprite->play(1);
        }
    }
    if(mState == State::EActive){
        for(auto component:mComponents){
            component->Update();
        }
    }
}
