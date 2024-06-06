#ifndef MONSTER_H
#define MONSTER_H
#include "game.h"
#include "gameobject.h"
#include"fallcomponent.h"
#include"movecomponent.h"
#include"animationComponent.h"
#include<QDebug>
#include"standard.h"
#include "newanimationcomponent.h"

struct InterfaceMonster;

class GameObject;
class Monster : public GameObject
{
public:

    explicit Monster(QObject *parent = nullptr,class Game* game = nullptr);
    virtual ~Monster();

    enum class MonsterState{WALKING,FIGHTING,IDLE,DYING};//!怪物状态集合（判断,怪物应该只存在walking跟fighting的两种状态）
    MonsterState mMonsterState;
    virtual void changeMonsterState(MonsterState state);//!改变怪物状态
    // 加monstertype的时候记得补一下QTEEnermy类的searchAnimation函数
    enum class MonsterType{Cyborg,Biker,Batman,Robot};
    // 加monstertype的时候记得补一下QTEEnermy类的searchAnimation函数
    MonsterType mMonsterType = MonsterType::Batman;
    InterfaceMonster intoInterface();        //!<从player转为Interface函数

    void Update()override;                          //!<每帧更新

    float getSpeedX()override;   //!<获得X速度
    float getSpeedY()override;   //!<获得Y速度
    int getDirection()override; //!<获得运动方向
    void setMoveDirection(int dir)override;    //!<设置运动方向
    void setSpeedX(float s)override;   //!<设置X速度
    void setSpeedY(float s)override;   //!<设置Y速度
    void setHP(int hp);                 //设置hp
    int getDrawDirection()override;    //!<获得绘画方向（正常1，镜像-1）
    int getMonsterType();              //获取怪物种类
    int getHP();                // 获得血量

    void movecollideOthers(GameObject* d,QVector2D& lastposition)override;        //!<在moveComponent中碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    void fallcollideOthers(GameObject* d,QVector2D& lastposition)override;        //!<在fallComponent中碰撞其他gameobject的事件处理(d是this碰撞到的GameObject)
    void beingCollide(GameObject* s)override;         //!<被碰撞后发生的事件处理(s是碰撞this的GameObject)
    void movenotCollide(QVector2D& lastposition)override;                        //!<如果movecomponent没有发生碰撞后该Object的处理(用于monster)
    void fallnotCollide(QVector2D& lastposition)override;        //!<如果fallcomponent没有发生碰撞后该Object的处理(用于monster)

    void loseHPEvent(int HPlost);       //掉血量事件，传入的是每帧扣的血量
    void chooseAnimation(MonsterType type,MonsterState state);

    FallComponent * fallCom;       //掉落组件
    MoveComponent * moveCom;        //移动组件
    AnimationComponent* animation;           //动画组件

    void initialByInterface(InterfaceMonster mmonster);                           //通过interface初始化

    int changeTheFightingAnimation;              //是否对打玩家图片特殊处理
    int deathFrime = 0;                         //死亡特殊处理

    NewAnimationComponent* exclamationAnimation;   //感叹号的动画组件

    int getMonsterATK();//获得ATK

private:
    bool initialGroundFlag = false;  //!<刚开始怪物用于落地用的flag
    int moveDirection = 1;     //!< 运动方向 1为右，-1为左
    int HP = MONSTER::MaxHP;                //!< 血量
    int ATK = 30;                //!<攻击力，默认为30
    long long loseHP_timeCount = 0;  //!< 距离上一次扣血已经经过的时间
    float mSpeedX = ACTIONCONST::monsterMoveXSpeed ,mSpeedY =  0;     //!< 移动速度 X横,Y竖
    bool setQteFlag;         //!<是否以及设置可进行qte表示图标的flag

};

#endif // MONSTER_H
