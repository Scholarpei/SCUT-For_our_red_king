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

void QTEObject::startQTEfrom3(){
    this->neednextRound=1;
    this->QTEBegin();
    this->round=3;
}
void QTEObject::setContinue(bool isContinue){
    neednextRound=isContinue;
}
void QTEObject::inputMousePressProcess(QMouseEvent * e){
    this->FightQTE::inputMousePressProcess(e);
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
    if(key=='M')
        this->neednextRound=1;
    if(key=='N')
        this->startQTEfrom3();
    this->FightQTE::inputKeyPressProcess(key);
}

//自己写。
void QTEObject::win(){
    qDebug() << "win";
}
void QTEObject::lose_typeone(){
    qDebug() << "type1";
}
void QTEObject::lose_typetwo(){
    qDebug() << "type2";
}
