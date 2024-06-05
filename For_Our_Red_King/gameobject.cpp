#include "gameobject.h"
#include "game.h"
#include "component.h"

GameObject::GameObject(QObject *parent,Game *game):
    QObject{parent},
    mState(State::EActive),
    mPosition(QVector2D(0,0)),
    mScale(QVector2D(1,1))
{

    //注意这里默认设置了物体参与碰撞
    mGame = game;
}

GameObject::~GameObject()
{
    // this->mState = State::EDead;
    // qDebug("gameobject destructor");
    while (!mComponents.empty())
    {
        Component* tmp = mComponents.back();
        delete tmp;
        this->removeComponent(mComponents.back());
        // mComponents.pop_back();
    }
}

void GameObject::Update()
{
    // qDebug()<<"大基类的Update()实际上不应该运行到这里";
    if(mState == State::EActive){
        for(auto component:mComponents){
            component->Update();
        }
    }
}

void GameObject::addComponent(Component* component)
{
    // 获取该组件的更新顺序
    int order = component->getUpdateOrder();
    std::vector<Component*>::iterator iter = mComponents.begin();
    // 新组件需要按顺序插入到对应位置
    if(!mComponents.empty())
        for (; iter != mComponents.end(); ++iter)
         {
             if (order < (*iter)->getUpdateOrder())
             {
                 break;
             }
         }
    mComponents.insert(iter, component);
}

void GameObject::removeComponent(Component* component)
{
    std::vector<Component*>::iterator iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

//!获得mScale
QVector2D GameObject::getScale()
{
    return this->mScale;
}

//!获得mPosition
QVector2D GameObject::getPosition()
{
    return this->mPosition;
}

void GameObject::setScale(const QVector2D s)
{
    this->mScale = s;
}

void GameObject::setPosition(const QVector2D p)
{
    this->mPosition = p;
}

//!获取当前状态
GameObject::State GameObject::getState()
{
    return this->mState;
}

//!获取Game对象
Game* GameObject::getGame()
{
    return this->mGame;
}
void GameObject::inputKeyPressProcess(int key){
    //不需要键盘事件的Object执行这个空函数
}
void GameObject::inputKeyReleaseProcess(int key){
    //不需要键盘事件的Object执行这个空函数
}

void GameObject::inputMousePressProcess(QMouseEvent * key)
{
    //不需要鼠标事件的Object执行这个空函数
}
void GameObject::inputMouseReleaseProcess(QMouseEvent * key)
{
    //不需要鼠标事件的Object执行这个空函数
}

float GameObject::getWidth()
{
    return this->mWidth;
}
float GameObject::getHeight()
{
    return this->mHeight;
}

//下面为没有什么用的虚函数内容，只是为了防止报错写的

int GameObject::getDirection()
{
    // qDebug()<<"调用了getDirection来自GameObject基类的函数，发生错误！\n";
    return 1;
}

void GameObject::setMoveDirection(int dir)
{
    qDebug()<<"调用了setMoveDirection来自GameObject基类的函数，发生错误！\n";
}

float GameObject::getSpeedX()
{
    qDebug()<<"调用了getSpeedX来自GameObject基类的函数，发生错误！\n";
    return -1;
}
float GameObject::getSpeedY()
{
    qDebug()<<"调用了getSpeedY来自GameObject基类的函数，发生错误！\n";
    return -1;
}

void GameObject::setSpeedX(float s)
{
    qDebug()<<"调用了setSpeedX来自GameObject基类的函数，发生错误！\n";
}
void GameObject::setSpeedY(float s)
{
    qDebug()<<"调用了setSpeedY来自GameObject基类的函数，发生错误！\n";
}

void GameObject::movecollideOthers(GameObject* d,QVector2D& lastposition)
{
    qDebug()<<"调用了movecollideOthers来自GameObject基类的函数，发生错误！\n";
}
void GameObject::fallcollideOthers(GameObject* d,QVector2D& lastposition)
{
    qDebug()<<"调用了fallcollideOthers来自GameObject基类的函数，发生错误！\n";
}
void GameObject::beingCollide(GameObject* s)
{
    qDebug()<<"调用了beingCollide来自GameObject基类的函数，发生错误！\n";
}

void GameObject::movenotCollide(QVector2D& lastposition)
{
    qDebug()<<"调用了movenotCollide来自GameObject基类的函数，发生错误！\n";
}

void GameObject::fallnotCollide(QVector2D& lastposition)
{
    qDebug()<<"调用了fallnotCollide来自GameObject基类的函数，发生错误！\n";
}

//!获得绘画方向（正常1、镜像-1）
int GameObject::getDrawDirection()
{
    return 1;
    //默认基类返回1
}

