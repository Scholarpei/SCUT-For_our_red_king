#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QVector2D>
#include <vector>
#include "component.h"
#include <QEvent>
#include "statebase.h"
#include  <QDebug>
#include <QMouseEvent>
class GameObject : public QObject
{
    Q_OBJECT
public:

    bool attendCollision = 1;    //!<gameObject对象是否参与碰撞
    float mWidth;         //!<贴图宽度
    float mHeight;        //!<贴图高度


    enum class State{EActive,EDead};   //!物体状态
    enum class Type{Player,Monster,Building,SpecialEffect}; //!gameObject的类型

    class Game* mGame;   //!<从属Game类
    State mState;        //!<当前状态(已消亡、仍存在)
    Type gameObjectType; //!<当前gameObject的类型(怪物、player...)

    explicit GameObject(QObject *parent = nullptr,class Game* game = nullptr);
    virtual ~GameObject();

    virtual void Update();        //每帧更新

    void	addComponent(class Component* component);//添加组件
    void	removeComponent(class Component* component);//移除组件

    virtual void inputKeyPressProcess(int key);   //处理键盘输入按下
    virtual void inputKeyReleaseProcess(int key);   //处理键盘输入松开
    virtual void inputMousePressProcess(QMouseEvent * key);   //处理鼠标按下
    virtual void inputMouseReleaseProcess(QMouseEvent * key); //处理鼠标松开

    QVector2D getScale();
    QVector2D getPosition();
    void setPosition(const QVector2D p);
    void setScale(const QVector2D s);
    //缩放scale、位置position的设置、获得函数

    float getWidth();
    float getHeight();
    //获得TexWidth TexHeight函数

    virtual float getSpeedX();   //!<获得X速度
    virtual float getSpeedY();   //!<获得Y速度
    virtual int getDirection(); //!<获得运动方向
    virtual void setMoveDirection(int dir);    //!<设置运动方向
    virtual void setSpeedX(float s);   //!<设置X速度
    virtual void setSpeedY(float s);   //!<设置Y速度
    //以上几条为拥有speedX,speedY,moveDirection变量的对象的虚函数，在如player.cpp中实现
    virtual int getDrawDirection();     //!<获得绘画方向（正常1、镜像-1）

    virtual void movecollideOthers(GameObject* d,QVector2D& lastposition);        //!<在moveComponent中碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    virtual void fallcollideOthers(GameObject* d,QVector2D& lastposition);        //!<在fallComponent中碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    virtual void beingCollide(GameObject* s);         //!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
    virtual void movenotCollide(QVector2D& lastposition);                        //!<如果movecomponent没有发生碰撞后该Object的处理(用于monster)
    virtual void fallnotCollide(QVector2D& lastposition);                        //!<如果fallcomponent没有发生碰撞后该Object的处理(用于monster)

    State getState();          //!<获取当前状态
    Game* getGame();           //!<获取Game对象

    //! 获取特定类型的组件，并得到该组件类型的指针
    template<typename T> T* GetComponent()
    {
        for (auto com : mComponents)
        {
            T* component = dynamic_cast<T*>(com);
            if (component != nullptr)
            {
                return component;
            }
        }
        return nullptr;
    }

private:
    QVector2D mPosition;   //!<当前位置坐标
    QVector2D mScale = QVector2D(1.0,1.0);      //!<缩放    注意：第一维x.()是宽度,第二维y.()是高度
protected:
    std::vector<class Component*> mComponents;    //组件数组

signals:
};

#endif // GAMEOBJECT_H
