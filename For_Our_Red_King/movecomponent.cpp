#include "movecomponent.h"
#include "game.h"

MoveComponent::MoveComponent(GameObject* gameObject):
    Component(gameObject)
{

}

void MoveComponent::Update()
{
    //只考虑横向的运动
    int dir = mGameObject->getDirection();
    int speedX = mGameObject->getSpeedX();
    QVector2D curPos = mGameObject->getPosition();
    //获得gameObject各个数值
    QVector2D nxtPosition = QVector2D(curPos.x() + speedX*dir, curPos.y());//计算下一个位置
    QVector2D currentPosition = mGameObject->getPosition();     //备份前一个位置
    mGameObject->setPosition(nxtPosition);

    if(mGameObject->attendCollision)
        for(auto s_gameObject : mGameObject->mGame->mGameObjects)
            if(s_gameObject->attendCollision){//对应的s_gameObject要参与碰撞
            if(mGameObject->mGame->collisionDetection(mGameObject,s_gameObject)){
                //碰撞检测为true
                mGameObject->collideOthers(s_gameObject);
                s_gameObject->beingCollide(mGameObject);
                mGameObject->setPosition(currentPosition);
            }
            else{
                //碰撞检测为false
                mGameObject->notCollide();
                //由于已经改变了mGameObject位置，此处没有操作
            }
        }
    //碰撞检测部分

}

