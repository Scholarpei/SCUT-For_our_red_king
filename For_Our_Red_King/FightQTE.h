#ifndef FIGHTQTE_H
#define FIGHTQTE_H
#include "player.h"
#include "TimerComponent.h"
#include "newspritecomponent.h"
#include <array>

class TimerComponent;
class FightQTE : public GameObject
{
public:
    void initial();
    FightQTE(QObject *parent = nullptr, Game *game = nullptr);
    ~FightQTE();
    virtual void inputMousePressProcess(int key) override;
    void centralFunction();
    void Update() override;
    void rotation(int addAngle);
    void startQTE();
    void endQTE();
    void nextRound(); // 继续第三轮之后的轮数

    virtual void win();
    virtual void lose_typeone(); // 未击打的type
    virtual void lose_typetwo(); // 打错或者重复打
    bool roundIncre = 0;

protected:
    int angle; // 0-360
    int round; // 通过roundtype来设置round
    // float scale;//color用的缩放
    // int scalecnt;

    inline int changeKeyToNumber(int key);
    inline int drawAngle(int angle);
    void round2Judge(int key);
    void round3Judge(int key);
    void RoundInitial();
    NewspriteComponent *sprite_Point;
    NewspriteComponent *sprite_Plate;
    TimerComponent *timer;

    std::array<int, 4> hit_type;                       // 击打的类型
    std::array<NewspriteComponent *, 4> sprite_colors; // 四个color
    int cnt = 0;                                       // 当前为第几个点需要打击
    bool neednextRound = 0;                            // 表示是否继续斩杀
    bool isHit = 0;                                    // 本轮是否已经打击过
    int TargetAngle = 0;                               // round3的目标
    bool state_INHIT = 0;                              // 状态，表示hit正在判定
    bool colorInitial = 0;                             // 表示大于等于三轮是否初始化成功
};

#endif
