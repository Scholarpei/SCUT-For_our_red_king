#ifndef QTEOBJECT_H
#define QTEOBJECT_H
#include "FightQTE.h"
#include "gameobject.h"
#include "monster.h"
class QTEObject:public FightQTE
{
public:
    QTEObject(QObject *parent=nullptr,Game* game=nullptr,Monster* enermy=nullptr);
    void setMonster(Monster* monster);
    void QTEBegin();//设置qte开始
    void QTEEnd();//设置qte结束
    void QTEshowGraph(bool isOrnot);//设置qte可以展示
    void setContinue(bool isContinue);//设置qte连击
    virtual void win();//斩杀怪物
    virtual void lose_typeone();//未击打
    virtual void lose_typetwo();//重复击打|击打错键

    virtual void inputKeyPressProcess(int key);//test use;
protected:
    Monster* enermy;

};

#endif // QTEOBJECT_H
