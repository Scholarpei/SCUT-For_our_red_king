#include "component.h"
#include "gameobject.h"
#include<QDebug>
Component::Component(GameObject* gameObject):
    mUpdateOrder(100)
{
    mGameObject = gameObject;
    mGameObject->addComponent(this);
}

Component::~Component()
{
    mGameObject->removeComponent(this);
}

int Component::getUpdateOrder()
{
    return this->mUpdateOrder;
}

void Component::setUpdateOrder(int o)
{
    this->mUpdateOrder = o;
}

GameObject* Component::getGameObject()
{
    return mGameObject;
}
void Component::inputProcess(int key){
    qDebug()<<"Component中或子类的inputProcess未完成。";
}
void Component::Update()
{
    qDebug()<<"Component中或子类的Update未完成。";
}

