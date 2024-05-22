#ifndef PLAYER_H
#define PLAYER_H
#include "game.h"
#include "gameobject.h"
#include"fallcomponent.h"
#include"movecomponent.h"
#include"animationComponent.h"
#include<QDebug>
#include"standard.h"
class GameObject;
class Player : public GameObject
{
public:

    explicit Player(QObject *parent = nullptr,class Game* game = nullptr);

    class PlayerStatesSet* _playerStateSet;    //!<玩家状态集合
    enum class playerState{IDLE,JUMPING,WALKING};//!玩家状态集合（判断）
    playerState mPlayerState;
    virtual void changePlayerState(playerState state);//!改变玩家状态

    void Update()override;                          //!<每帧更新

    void inputKeyPressProcess(int key)override;   //!<处理键盘输入按下
    void inputKeyReleaseProcess(int key)override;   //!<处理键盘输入松开

    float getSpeedX()override;   //!<获得X速度
    float getSpeedY()override;   //!<获得Y速度
    int getDirection()override; //!<获得运动方向
    void setMoveDirection(int dir)override;    //!<设置运动方向
    void setSpeedX(float s)override;   //!<设置X速度
    void setSpeedY(float s)override;   //!<设置Y速度

    void collideOthers(GameObject* d)override;        //!<碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    void beingCollide(GameObject* s)override;         //!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
    void notCollide()override;                        //!<如果没有发生碰撞后该Object的处理

    FallComponent * fallCom;       //掉落组件
    MoveComponent * moveCom;        //移动组件
    AnimationComponent* animation;           //动画组件

private:
    int moveDirection;     //!< 运动方向 1为右，-1为左
    int HP;                //!< 血量
    long long loseHP_timeCount;  //!< 距离上一次扣血已经经过的时间
    float mSpeedX,mSpeedY;     //!< 移动速度 X横,Y竖
};

#endif // PLAYER_H
