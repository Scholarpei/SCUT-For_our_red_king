#include "buttons.h"
#include <QMouseEvent>
#include <cmath>
Buttons::Buttons(QObject *parent,Game* game,int draworder)
    : GameObject{parent,game}
{
    isButtonOn=0;
    isPressed=0;
    attendCollision = 0;
    sprite=new NewspriteComponent(this,draworder);
    sprite->setNeedDraw(1);
}

void Buttons::setOnPicture(QString onpicture)
{
    this->onPicture=onpicture;
}
void Buttons::setOffPicture(QString offpicture)
{
    this->offPicture=offpicture;
    sprite->SetTexture(offPicture);
}
void Buttons::buttonFunction(){
    //按下后触发的函数
}
void Buttons::inputMousePressProcess(QMouseEvent *event){
    int posx=event->pos().x();
    int posy=event->pos().y();
    if(std::abs(posx-this->getPosition().x())<=this->mWidth/2&&std::abs(posy-this->getPosition().y())<=this->mHeight/2)
    {
        this->sprite->SetTexture(onPicture);
        isPressed=1;
    }
}
void Buttons::inputMouseReleaseProcess(QMouseEvent *event){
    if(isPressed)
    {
        if(std::abs(event->pos().x()-this->getPosition().x())<=this->mWidth/2&&std::abs(event->pos().y()-this->getPosition().y())<=this->mHeight/2)
        {
            isButtonOn=!isButtonOn;
            buttonFunction();
        }
        this->sprite->SetTexture(offPicture);
        isPressed=0;
    }
}
void Buttons::Update(){
    //啥也没有
}
