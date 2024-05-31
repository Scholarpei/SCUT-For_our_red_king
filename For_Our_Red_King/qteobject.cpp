#include "qteobject.h"
#include "FightQTE.h"
//QTEObject::QTEObject() {}
#include "game.h"
QTEObject::QTEObject(QObject *parent,Game* game,Monster* enermy)
    :FightQTE(parent,game){
    this->enermy=enermy;
    QTEshowGraph(0);
}
void QTEObject::setMonster(Monster* monster){
    this->enermy=monster;
}
void QTEObject::QTEBegin(){
    this->startQTE();
    this->timer->startRun();
    RoundInitial();
}
void QTEObject::QTEEnd(){
    this->timer->EndRun();
}
void QTEObject::QTEshowGraph(bool isOrnot){
    this->sprite_Plate->setNeedDraw(isOrnot);
    this->sprite_Point->setNeedDraw(isOrnot);
    if(!isOrnot)
    {
        for(auto i:this->sprite_colors)
            i->setNeedDraw(0);
    }
}

void QTEObject::setContinue(bool isContinue){
    neednextRound=isContinue;
}
void QTEObject::inputKeyPressProcess(int key){
    if(key=='Z')
        this->QTEshowGraph(1);
    if(key=='X')
        this->QTEshowGraph(0);
    if(key=='C')
        this->QTEBegin();
    if(key=='V')
        this->QTEEnd();
    // FightQTE* pa=this;
    // pa->inputKeyPressProcess(key);
}

//自己写。
void QTEObject::win(){

}
void QTEObject::lose_typeone(){

}
void QTEObject::lose_typetwo(){

}
