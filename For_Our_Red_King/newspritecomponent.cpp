#include "newspritecomponent.h"
#include "game.h"
#include "gameobject.h"
#include "QColor"
NewspriteComponent::NewspriteComponent(GameObject* gameObject,int drawOrder):
    spriteComponent(gameObject,drawOrder) {
    drawAngle=0;
    scale=1;
    posX=this->getGameObject()->getPosition().x()-this->getGameObject()->getWidth()/2;
    posY=this->getGameObject()->getPosition().y()-this->getGameObject()->getHeight()/2;
    needDraw=1;
}

void NewspriteComponent::Draw(){
    if(needDraw){
    QPainter* Painter=this->getGameObject()->getGame()->mWindow->mPainter;
    Painter->translate(posX,posY);
    Painter->rotate(drawAngle);
    // Painter->fillRect(QColor(0,0,0,alpha));
    Painter->drawPixmap(0,0,mWidth * scale,mHeight * scale,QPixmap(this->imageLocation));
    Painter->rotate(-drawAngle);
    Painter->translate(-posX,-posY);
    }
}
void NewspriteComponent::setAngle(int angle){
    this->drawAngle=angle;
}
// void NewspriteComponent::setAlpha(int alpha){
//     if(alpha>=255)alpha=255;
//     this->alpha=alpha;
// }
void NewspriteComponent::setScale(float scale){
    this->scale=scale;
}
void NewspriteComponent::setPos(int x,int y){
    posX=x;posY=y;
}
void NewspriteComponent::setNeedDraw(bool yesOrno){
    needDraw=yesOrno;
    //qDebug()<<"setneeddraw"<<needDraw;
}
NewspriteComponent::~NewspriteComponent()
{
    mGameObject->getGame()->removeSprite(this);
}
bool NewspriteComponent::getNeedDraw()const{
    return needDraw;
}
