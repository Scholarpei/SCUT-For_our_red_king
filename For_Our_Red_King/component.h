#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    //! 构造函数
    explicit Component(class GameObject* gameObject=nullptr);
    //! 析构函数
    virtual ~Component();

    //! 每帧更新
    virtual void Update();
    //! 处理键盘输入
    virtual void inputProcess(int key);

    //!获取mUpdateOrder
    int getUpdateOrder();
    //!设置mUpdateOrder
    void setUpdateOrder(int order);

    //!获得gameobject
    GameObject* getGameObject();

protected:
    class GameObject* mGameObject;        //!<    自身附着的游戏物体
    int mUpdateOrder;        //!<    更新顺序

};

#endif // COMPONENT_H
