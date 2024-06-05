#include "qteobject.h"
#include "FightQTE.h"
#include "playerteleportationcomponent.h"
//QTEObject::QTEObject() {}
#include "game.h"
QTEObject::QTEObject(QObject *parent,Game* game,Monster* enermy)
    :FightQTE(parent,game){
    this->enermy=enermy;
    QTEshowGraph(0);
}
QTEObject::~QTEObject()
{

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
    this->QTEEnd();
    qDebug() << "win";
    this->QTEshowGraph(false);
    this->mGame->qteWinPeriodFlag = true;  //设置追击flag
    this->mGame->qteWintimer = 0;   //追击计时器归零
    enermy->changeMonsterState(Monster::MonsterState::DYING);//改变为死亡状态

    //瞬移动画

    QVector2D targetPosition;//目标位置
    int enermydir = enermy->getDirection();
    targetPosition.setX(enermy->getPosition().x() + (-enermydir * this->mGame->mPlayer->getWidth()));
    targetPosition.setY(enermy->getPosition().y() - this->mGame->mPlayer->getHeight());
    this->mGame->mPlayer->teleportation = new PlayerTeleportationComponent(this->mGame->mPlayer,targetPosition);

    //瞬移动画
}
void QTEObject::lose_typeone(){
    this->QTEEnd();
    qDebug() << "type1";
    this->QTEshowGraph(false);
    this->mGame->mPlayer->loseHPEvent(this->enermy->getMonsterATK());//减怪物的攻击力的血量
    mbgmPlayer->stop();//停止鼓点
    this->mGame->mMusicPlayer->setVolumeProportion(0.8f);//设置背景音乐恢复音量
    this->mGame->nowIsQTE = false;//结束qte,flag设置为false
}
void QTEObject::lose_typetwo(){
    this->QTEEnd();
    qDebug() << "type2";
    this->QTEshowGraph(false);
    this->mGame->mPlayer->loseHPEvent(this->enermy->getMonsterATK());//减怪物的攻击力的血量
    mbgmPlayer->stop();//停止鼓点
    this->mGame->mMusicPlayer->setVolumeProportion(0.8f);//设置背景音乐恢复音量
    this->mGame->nowIsQTE = false;//结束qte,flag设置为false
}

Monster* QTEObject::getEnermy()
{
    return this->enermy;
}
