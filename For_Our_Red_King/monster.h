#ifndef MONSTER_H
#define MONSTER_H
#include "game.h"
#include "gameobject.h"
#include"fallcomponent.h"
#include"movecomponent.h"
#include"animationComponent.h"
#include<QDebug>
#include"standard.h"
class GameObject;
class Monster : public GameObject
{
public:

    explicit Monster(QObject *parent = nullptr,class Game* game = nullptr);

    class MonsterStateSet* _monsterStateSet;     //!<怪物状态集合
    enum class MonsterState{WALKING};//!怪物状态集合（判断,怪物应该只存在walking跟fighting的两种状态）
    MonsterState mMonsterState;
    virtual void changeMonsterState(MonsterState state);//!改变怪物状态

    void Update()override;                          //!<每帧更新

    float getSpeedX()override;   //!<获得X速度
    float getSpeedY()override;   //!<获得Y速度
    int getDirection()override; //!<获得运动方向
    void setMoveDirection(int dir)override;    //!<设置运动方向
    void setSpeedX(float s)override;   //!<设置X速度
    void setSpeedY(float s)override;   //!<设置Y速度
    int getDrawDirection()override;    //!<获得绘画方向（正常1，镜像-1）

    void movecollideOthers(GameObject* d,QVector2D& lastposition)override;        //!<在moveComponent中碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    void fallcollideOthers(GameObject* d,QVector2D& lastposition)override;        //!<在fallComponent中碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    void beingCollide(GameObject* s)override;         //!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
    void movenotCollide(QVector2D& lastposition)override;                        //!<如果movecomponent没有发生碰撞后该Object的处理(用于monster)
    void fallnotCollide(QVector2D& lastposition)override;                        //!<如果fallcomponent没有发生碰撞后该Object的处理(用于monster)

    FallComponent * fallCom;       //掉落组件
    MoveComponent * moveCom;        //移动组件
    AnimationComponent* animation;           //动画组件

private:
    int moveDirection;     //!< 运动方向 1为右，-1为左
    int HP;                //!< 血量
    long long loseHP_timeCount;  //!< 距离上一次扣血已经经过的时间
    float mSpeedX ,mSpeedY;     //!< 移动速度 X横,Y竖
};

#endif // MONSTER_H
