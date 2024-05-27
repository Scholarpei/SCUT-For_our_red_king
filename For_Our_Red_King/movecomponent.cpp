#include "movecomponent.h"
#include "game.h"

MoveComponent::MoveComponent(GameObject* gameObject):
    Component(gameObject)
{

}

void MoveComponent::Update()
{
    // qDebug()<<"MoveComponent update启动";
    //只考虑横向的运动
    int dir = mGameObject->getDirection();
    float speedX = mGameObject->getSpeedX();
    QVector2D curPos = mGameObject->getPosition();//备份前一个位置
    //获得gameObject各个数值
    const QVector2D nxtPosition = QVector2D(float(curPos.x() + speedX*dir*0.2), curPos.y());//计算下一个位置
    mGameObject->setPosition(nxtPosition);

    bool isCollide = false;   //当前gameObject是否跟其他Object发生碰撞

    if(mGameObject->attendCollision)
        for(auto s_gameObject : mGameObject->mGame->mGameObjects)
            if(s_gameObject!=mGameObject&&s_gameObject->attendCollision){//对应的s_gameObject要参与碰撞
            if(mGameObject->mGame->collisionDetection(mGameObject,s_gameObject)){
                //碰撞检测为true
                isCollide = true;
                mGameObject->movecollideOthers(s_gameObject,curPos);
                s_gameObject->beingCollide(mGameObject);
                mGameObject->setPosition(curPos);
            }
        }

    if(!isCollide){
        mGameObject->movenotCollide(curPos);
    }
    //碰撞检测部分
}

