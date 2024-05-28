#include "rotationcomponent.h"
#include "game.h"
#include "gameobject.h"
#include "component.h"
#include <qdebug.h>
#include <standard.h>
void rotationComponent::initial()
{
    posX=this->getGameObject()->getPosition().x()+this->getWidth()/2;
    posY=this->getGameObject()->getPosition().y()+this->getHeight()/2;
    alpha=std::atan(posY/posX);
    R=std::sqrt(posX*posX+posY);
}
rotationComponent::rotationComponent(GameObject* gameObject,int drawOrder):
    spriteComponent(gameObject,drawOrder)
{
    DrawAngle=0;
    initial();
}
void rotationComponent::Draw(){
    QPainter* Painter=this->getGameObject()->getGame()->mWindow->mPainter;
    setHW();
    Painter->translate(posX, posY);
    Painter->rotate(DrawAngle);
    //draw

    Painter->drawPixmap(0,0,mWidth * mGameObject->getScale().x(),mHeight * mGameObject->getScale().y(),QPixmap(this->imageLocation));
    //
    Painter->rotate(-DrawAngle);
    Painter->translate(-posX, -posY);
}
void rotationComponent::setAngle(int angle)
{
    DrawAngle=angle;
}
inline void rotationComponent::setHW()
{
    CenWidth=R*std::cos(0.5*DrawAngle-alpha)+posX;
    CenHeight=R*std::sin(0.5*DrawAngle-alpha)+posY;
}
