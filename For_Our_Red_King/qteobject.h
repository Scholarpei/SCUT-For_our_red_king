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
    void startQTEfrom3();
    virtual void win();//斩杀怪物
    virtual void lose_typeone();//未击打
    virtual void lose_typetwo();//重复击打|击打错键
    virtual void inputMousePressProcess(QMouseEvent * key);
    virtual void inputKeyPressProcess(int key);//test use;
    //测试用 z键打开盘 x关掉盘 c从颜色开始 v暂停 m使下一轮继续出现红色 n直接从round3开始
protected:
    Monster* enermy;

};

#endif // QTEOBJECT_H
