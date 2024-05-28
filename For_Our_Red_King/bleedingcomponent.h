#ifndef BLEEDINGCOMPONENT_H
#define BLEEDINGCOMPONENT_H

#include "qvectornd.h"
#include "spritecomponent.h"
#include "standard.h"

class BleedingComponent : public spriteComponent
{
public:
    BleedingComponent(class GameObject* gameObject=nullptr,int drawOrder=DRAWORRDER::item);
    ~BleedingComponent();

    void setTecture(AnimationLoader plate, AnimationLoader blood, AnimationLoader hurting, AnimationLoader healing, AnimationLoader shocked_plate);

    virtual void Draw();    // 画图

    void changeHP(int HP);  // 改变 HP




protected:
    AnimationLoader plate;
    AnimationLoader blood;
    AnimationLoader hurting;
    AnimationLoader healing;
    AnimationLoader shocked_plate;

    AnimationLoader drawn_plate;

    enum class State{ILDE, SHOCKED, RECOVERING};

    int SHOECKED_TICKS = 60;            // 表示shocked阶段维持时间
    int RECOVERING_TICKS = 60;          // 表示recovering阶段维持时间

    int FLASHING_TICKS = 27;            // 表示血条槽闪光时间，必须小于shocked_ticks
    int FLASHING_DURATION = 9;          // 表示闪光时每一帧时长，前者除以这个必须得到奇数

    int MAX_HP = PLAYER::MaxHP;         // 最大血量

    double hpCurrent = PLAYER::MaxHP;      // 表示当前移动到的HP
    double hpAfter = PLAYER::MaxHP;        // 表示将要到达的HP

    double changePerTick = 0;                  // 表示每帧变化多少血量以对齐

    void next_tick();                   // 下一刻

    void draw_value(int value, QString add);    // 根据血量画对应的柱子


private:
    QVector2D BLOOD_RELATIVE_POSI;
    QPainter* painter;

public:

    State state;
    int currentTick = 0;
};

#endif // BLEEDINGCOMPONENT_H
