#include "fallcomponent.h"
#include "game.h"
#include "player.h"
FallComponent::FallComponent(GameObject* gameObject):
    Component(gameObject)
{

}

void FallComponent::Update()
{
    if(mGameObject->gameObjectType == GameObject::Type::Player){
        //如果这是player
        Player* playerPtr = dynamic_cast<Player*>(mGameObject);
        if(playerPtr->mPlayerState == Player::playerState::JUMPING){
            if(playerPtr->getSpeedY()+ACTIONCONST::jump_gravityAcceleration < ACTIONCONST::maxSpeed)
                playerPtr->setSpeedY(playerPtr->getSpeedY()+ACTIONCONST::jump_gravityAcceleration);
        }
        else{
            //player其他状态
            if(playerPtr->getSpeedY()+ACTIONCONST::gravityAcceleration < ACTIONCONST::maxSpeed)
                playerPtr->setSpeedY(playerPtr->getSpeedY()+ACTIONCONST::gravityAcceleration);
        }
    }
    else{
        if(mGameObject->getSpeedY()+ACTIONCONST::gravityAcceleration < ACTIONCONST::maxSpeed)
            mGameObject->setSpeedY(mGameObject->getSpeedY()+ACTIONCONST::gravityAcceleration);
        //其他类型
    }
    QVector2D curPos = mGameObject->getPosition();
    QVector2D currentPosition = mGameObject->getPosition();     //备份前一个位�?
    mGameObject->setPosition(QVector2D(curPos.x(), curPos.y() + mGameObject->getSpeedY()));//设置为下一个位�?

    if(mGameObject->attendCollision)
        for(auto s_gameObject : mGameObject->mGame->mGameObjects)
            if(s_gameObject!=mGameObject&&s_gameObject->attendCollision){//对应的s_gameObject要参与碰�?
                if(mGameObject->mGame->collisionDetection(mGameObject,s_gameObject)){
                    //碰撞检测为true
                    mGameObject->fallcollideOthers(s_gameObject,curPos);

                    s_gameObject->beingCollide(mGameObject);
                    mGameObject->setPosition(currentPosition);
                }
                else{
                    //碰撞检测为false
                    mGameObject->fallnotCollide();
                    //由于已经改变了mGameObject位置，此处没有操�?
                }
            }
    //碰撞检测部�?
}
