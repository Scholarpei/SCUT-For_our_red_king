#include "monsterstateset.h"
#include <QObject>

MonsterStateSet::MonsterStateSet(QObject *parent,GameObject* gameObject)
    :QObject{parent}
{
    mGameObject = gameObject;
}
