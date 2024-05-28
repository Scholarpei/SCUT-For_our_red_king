#ifndef FIGHTQTE_H
#define FIGHTQTE_H
#include "player.h"
#include "TimerComponent.h"
#include "rotationcomponent.h"
#include <array>
const int HIT_TIME = 4;

class TimerComponent;
class FightQTE :
    public GameObject
{
public:
    void initial();
    FightQTE(QObject *parent=nullptr,Game* game=nullptr);//!<ȱ��enermy��
    ~FightQTE();
    virtual void inputKeyPressProcess(int key)override;
    void centralFunction();
    void Update()override;
    void rotation(int addAngle);
    void startQTE();//!< start QTE from round 1; is already show picture.

protected:

    std::array<int,4> hit_type;
    int angle;//0-360
    int round;

    inline int changeKeyToNumber(int key);\
    inline int drawAngle(int angle);
    void round2Judge(int key);
    void round3Judge(int key);

    rotationComponent* sprite_Point;
    spriteComponent* sprite_Plate;
    TimerComponent* timer;

    int cnt=0;//��ǰΪ�ڼ�������Ҫ���

    bool isHit=0;//�����Ƿ��Ѿ������
    int TargetAngle=0;//round3��Ŀ��
    bool state_INHIT;//״̬����ʾhit�����ж�
signals:
    void fight_Win();
    void fight_Lose();
};

#endif
