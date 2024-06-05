#include "fallcomponent.h"
#include "game.h"
#include "player.h"
FallComponent::FallComponent(GameObject* gameObject):
    Component(gameObject)
{

}

void FallComponent::Update()
{
    if(this->mGameObject->mGame->nowIsQTE)
        return;
    //qte下不参与fall，也不考虑碰撞

    if(mGameObject->gameObjectType == GameObject::Type::Player){
        //player类型的判定
        Player* playerPtr = dynamic_cast<Player*>(mGameObject);
        if(playerPtr->mPlayerState == Player::playerState::JUMPING){
            if(playerPtr->getSpeedY()+ACTIONCONST::jump_gravityAcceleration < ACTIONCONST::maxSpeed)
                playerPtr->setSpeedY(playerPtr->getSpeedY()+ACTIONCONST::jump_gravityAcceleration);
        }
        else{
            //player其他状态下
            if(playerPtr->getSpeedY()+ACTIONCONST::gravityAcceleration < ACTIONCONST::maxSpeed)
                playerPtr->setSpeedY(playerPtr->getSpeedY()+ACTIONCONST::gravityAcceleration);
        }
    }
    else{
        if(mGameObject->getSpeedY()+ACTIONCONST::gravityAcceleration < ACTIONCONST::maxSpeed){
            mGameObject->setSpeedY(mGameObject->getSpeedY()+ACTIONCONST::gravityAcceleration);
            //其他type的gameObject
        }
    }
    QVector2D curPos = mGameObject->getPosition();
    QVector2D currentPosition = mGameObject->getPosition();     //备份上一帧的位置
    mGameObject->setPosition(QVector2D(curPos.x(), curPos.y() + mGameObject->getSpeedY()));//设置新位置

    //以下为Monster的平台纠正处理
    bool isCollideMonster = false; //纠正怪物移动过度超出平台的特殊处理flag
    if(mGameObject->gameObjectType == GameObject::Type::Monster){
        QVector2D tempPos = mGameObject->getPosition();
        mGameObject->setPosition(QVector2D(curPos.x()+this->mGameObject->getDirection()*32, curPos.y() + mGameObject->getSpeedY()));//设置新位置
        if(mGameObject->attendCollision)
            for(auto s_gameObject : mGameObject->mGame->mGameObjects)
                if(s_gameObject!=mGameObject&&s_gameObject != mGameObject->mGame->mPlayer &&s_gameObject->gameObjectType!=GameObject::Type::Monster&&s_gameObject->attendCollision){//要参与碰撞且不为自身且不考虑Player
                    if(mGameObject->mGame->collisionDetection(mGameObject,s_gameObject)){
                        //与其他物体发生碰撞
                        isCollideMonster = true;
                    }
                }
        if(!isCollideMonster)
            mGameObject->fallnotCollide(tempPos);
        //fall碰撞检测
        mGameObject->setPosition(tempPos);
    }

    //以下为正常碰撞检测

    bool isCollide = false;   //当前gameObject是否跟其他Object发生碰撞
    if(mGameObject->attendCollision)
        for(auto s_gameObject : mGameObject->mGame->mGameObjects)
            if(s_gameObject!=mGameObject&&s_gameObject->attendCollision){//要参与碰撞且不为自身
                if(mGameObject->mGame->collisionDetection(mGameObject,s_gameObject)){
                    //与其他物体发生碰撞
                    mGameObject->fallcollideOthers(s_gameObject,curPos);
                    isCollide = true;
                    s_gameObject->beingCollide(mGameObject);
                    mGameObject->setPosition(currentPosition);
                }
            }
    if(!isCollide)
        mGameObject->fallnotCollide(curPos);
    //fall碰撞检测

}
