#include "playerteleportationcomponent.h"
#include "gameobject.h"
#include "game.h"
#include "player.h"

PlayerTeleportationComponent::PlayerTeleportationComponent(GameObject* gameObject,QVector2D tp)
    :Component(gameObject)
{
    this->tarPos = tp;
    QVector2D startPos = this->mGameObject->mGame->mPlayer->getPosition();
    SpeedX = PLAYER::PlayerTeleportationMovingProportion*(tarPos.x() - startPos.x())/(float)PLAYER::PlayerTeleportationTime;
    SpeedY = PLAYER::PlayerTeleportationMovingProportion*(tarPos.y() - startPos.y())/(float)PLAYER::PlayerTeleportationTime;
}

PlayerTeleportationComponent::~PlayerTeleportationComponent()
{
    this->mGameObject->removeComponent(this);
}

void PlayerTeleportationComponent::Update()
{
    ++nowtime;
    if(nowtime > PLAYER::PlayerTeleportationTime){
        //要瞬移了
        this->mGameObject->setPosition(tarPos);
        delete this;//析构
    }
    else{
        QVector2D p = this->mGameObject->getPosition();
        this->mGameObject->setPosition(QVector2D(p.x() + SpeedX,p.y() + SpeedY));
    }
}
