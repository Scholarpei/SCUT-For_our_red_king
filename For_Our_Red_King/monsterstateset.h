#ifndef MONSTERSTATESET_H
#define MONSTERSTATESET_H

#include <QObject>
#include "gameobject.h"

class MonsterStateSet: public QObject
{
    Q_OBJECT
public:
    explicit MonsterStateSet(QObject* parent = nullptr,GameObject* gameObject = nullptr);
    //解释一下为什么不需要新写一个Monster的walkingstate类：因为不需要监测键盘跟鼠标的输入
private:
    GameObject* mGameObject;
};

#endif // MONSTERSTATESET_H
