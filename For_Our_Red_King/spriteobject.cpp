#include "spriteobject.h"
SpriteObject::SpriteObject(QObject *parent, Game *game,int draworder)
    : GameObject{parent,game}
{
    this->attendCollision=0;
    direction=1;
    drawPosX=0;
    drawPosY=0;
    realPosX=0;
    realPosY=0;
    opacity=0;
    this->sprite=new AnimationComponent(this,draworder);
}

SpriteObject::~SpriteObject()
{
    delete this->sprite;
}

void SpriteObject::setDirection(int dir){
    if(dir==1||dir==-1)
        this->direction=dir;
}
void SpriteObject::setPosition(int x,int y){
    this->realPosX=x;
    this->realPosY=y;
    this->drawPosX=x-this->mWidth/2;
    this->drawPosY=y-this->mHeight/2;
    this->GameObject::setPosition(QVector2D(drawPosX,drawPosY));
}
void SpriteObject::setOpacity(double opa){
    this->opacity=opa;
    sprite->setOpacity(opacity);
}

void SpriteObject::setNeedDraw(bool needOrNot){
    this->needDraw=needOrNot;
    sprite->setDisplay(needDraw);
    sprite->pause();
}
void SpriteObject::setWidth(int width){
    this->mWidth=width;
    this->drawPosX=this->realPosX-width/2;
}
void SpriteObject::setHeight(int height){
    this->mHeight=height;
    this->drawPosY=this->realPosY-height/2;
}
void SpriteObject::reload(){
    this->drawPosX=this->realPosX-this->mWidth/2;
    this->drawPosY=this->realPosY-this->mHeight/2;
    sprite->setOpacity(opacity);
    sprite->setDisplay(needDraw);
}
int SpriteObject::getDrawDirection()
{
    return this->direction;
}
void SpriteObject::playOrstop(bool isPlay)
{
    if(isPlay)
    this->sprite->play(1);
    else this->sprite->pause();
}
