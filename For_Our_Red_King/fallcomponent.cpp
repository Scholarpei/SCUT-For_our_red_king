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
        //濡傛灉杩欐槸player
        Player* playerPtr = dynamic_cast<Player*>(mGameObject);
        if(playerPtr->mPlayerState == Player::playerState::JUMPING){
            if(playerPtr->getSpeedY()+ACTIONCONST::jump_gravityAcceleration < ACTIONCONST::maxSpeed)
                playerPtr->setSpeedY(playerPtr->getSpeedY()+ACTIONCONST::jump_gravityAcceleration);
        }
        else{
            //player鍏朵粬鐘舵€�
            if(playerPtr->getSpeedY()+ACTIONCONST::gravityAcceleration < ACTIONCONST::maxSpeed)
                playerPtr->setSpeedY(playerPtr->getSpeedY()+ACTIONCONST::gravityAcceleration);
        }
    }
    else{
        if(mGameObject->getSpeedY()+ACTIONCONST::gravityAcceleration < ACTIONCONST::maxSpeed)
            mGameObject->setSpeedY(mGameObject->getSpeedY()+ACTIONCONST::gravityAcceleration);
        //鍏朵粬绫诲瀷
    }
    QVector2D curPos = mGameObject->getPosition();
    QVector2D currentPosition = mGameObject->getPosition();     //澶囦唤鍓嶄竴涓綅缃?
    mGameObject->setPosition(QVector2D(curPos.x(), curPos.y() + mGameObject->getSpeedY()));//璁剧疆涓轰笅涓€涓綅缃?

    if(mGameObject->attendCollision)
        for(auto s_gameObject : mGameObject->mGame->mGameObjects)
            if(s_gameObject!=mGameObject&&s_gameObject->attendCollision){//瀵瑰簲鐨剆_gameObject瑕佸弬涓庣鎾?
                if(mGameObject->mGame->collisionDetection(mGameObject,s_gameObject)){
                    //纰版挒妫€娴嬩负true
                    mGameObject->fallcollideOthers(s_gameObject,curPos);

                    s_gameObject->beingCollide(mGameObject);
                    mGameObject->setPosition(currentPosition);
                }
                else{
                    //纰版挒妫€娴嬩负false
                    mGameObject->fallnotCollide();
                    //鐢变簬宸茬粡鏀瑰彉浜唌GameObject浣嶇疆锛屾澶勬病鏈夋搷浣?
                }
            }
    //纰版挒妫€娴嬮儴鍒?
}
