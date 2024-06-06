#include "qteenermy.h"
#include "monster.h"
QTEEnermy::QTEEnermy(QObject *parent, Game *game,int draworder)
    :SpriteObject(parent,game,draworder)
{
    this->kindOfenermy=Monster::MonsterType::Batman;

    this->isAttack=0;
    this->setNeedDraw(0);
    this->setDirection(-1);

    this->setWidth(QTE::enermyWidth);
    this->setHeight(QTE::enermyHeight);
    this->setPositionX(QTE::enermyPositionX);
    this->setOpacity(0.3);
    reload();

    this->sprite->resetAnimation(searchAnimation(this->kindOfenermy,EnermyType::idle));//初始值
    this->setPositionY(QTE::Ground-sprite->animation.GetpixY()*QTE::DrawScale/2);
    this->setWidth(this->sprite->animation.GetpixX()*QTE::DrawScale);
    this->setHeight(this->sprite->animation.GetpixY()*QTE::DrawScale);
    this->sprite->setRepeat(1);
}

const AnimationLoader& QTEEnermy::searchAnimation(Monster::MonsterType typeKind,EnermyType typeState){
        switch (typeKind) {
        case Monster::MonsterType::Batman:

            if(typeState==EnermyType::attack)
                return MONSTER::Batmanfighting;
            else if(typeState==EnermyType::idle)
                return MONSTER::Batmanidle;
            else return MONSTER::Batmandead;

            break;
        case Monster::MonsterType::Biker:
            if(typeState==EnermyType::attack)
                return MONSTER::Bikerfighting;
            else if(typeState==EnermyType::idle)
                return MONSTER::Bikeridle;
            else return MONSTER::Bikerdead;
            break;
        case Monster::MonsterType::Cyborg:
            if(typeState==EnermyType::attack)
                return MONSTER::Cyborgfighting;
            else if(typeState==EnermyType::idle)
                return MONSTER::Cyborgidle;
            else return MONSTER::Cyborgdead;
            break;
        case Monster::MonsterType::Robot:
            if(typeState==EnermyType::attack)
                return MONSTER::Robotfighting;
            else if(typeState==EnermyType::idle)
                return MONSTER::Robotidle;
            else return MONSTER::Robotdead;
            break;
        default:
            break;
        }

}
void QTEEnermy::attack(){
    this->sprite->resetAnimation(searchAnimation(this->kindOfenermy,EnermyType::attack));
    this->setPositionY(QTE::Ground-sprite->animation.GetpixY()*QTE::DrawScale/2);
    this->setWidth(this->sprite->animation.GetpixX()*QTE::DrawScale);
    this->setHeight(this->sprite->animation.GetpixY()*QTE::DrawScale);
    isAttack=1;
    this->sprite->play(0);
}
void QTEEnermy::dead(){
    this->sprite->resetAnimation(searchAnimation(this->kindOfenermy,EnermyType::dead));
    this->setPositionY(QTE::Ground-sprite->animation.GetpixY()*QTE::DrawScale/2);
    this->setWidth(this->sprite->animation.GetpixX()*QTE::DrawScale);
    this->setHeight(this->sprite->animation.GetpixY()*QTE::DrawScale);
    this->sprite->play(0);
}
void QTEEnermy::idle(){
    this->isAttack=0;
    this->sprite->resetAnimation(searchAnimation(this->kindOfenermy,EnermyType::idle));
    this->setPositionY(QTE::Ground-sprite->animation.GetpixY()*QTE::DrawScale/2);
    this->setWidth(this->sprite->animation.GetpixX()*QTE::DrawScale);
    this->setHeight(this->sprite->animation.GetpixY()*QTE::DrawScale);
    this->sprite->play(1);
}
void QTEEnermy::Update(){
    if(isAttack)
    {
        if(!this->sprite->isPlaying)
        {
            this->sprite->resetAnimation(searchAnimation(this->kindOfenermy,EnermyType::idle));
            this->setPositionY(QTE::Ground-sprite->animation.GetpixY()*QTE::DrawScale/2);
            this->setWidth(this->sprite->animation.GetpixX()*QTE::DrawScale);
            this->setHeight(this->sprite->animation.GetpixY()*QTE::DrawScale);
            this->sprite->play(1);
        }
    }
    if(mState == State::EActive){
        for(auto component:mComponents){
            component->Update();
        }
    }
}
