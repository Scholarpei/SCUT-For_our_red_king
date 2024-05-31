#ifndef FIGHTQTE_H
#define FIGHTQTE_H
#include "player.h"
#include "TimerComponent.h"
#include "newspritecomponent.h"
#include <array>

class TimerComponent;
class FightQTE :
    public GameObject
{
public:
    void initial();
    FightQTE(QObject *parent=nullptr,Game* game=nullptr);
    ~FightQTE();
    virtual void inputKeyPressProcess(int key)override;
    void centralFunction();
    void Update()override;
    void rotation(int addAngle);
    void startQTE();
    void endQTE();
    void nextRound();//����������֮�������

    virtual void win();
    virtual void lose_typeone();//δ�����type
    virtual void lose_typetwo();//�������ظ���
    bool roundIncre=0;
protected:

    int angle;//0-360
    int round;//ͨ��roundtype������round
    // float scale;//color�õ�����
    // int scalecnt;

    inline int changeKeyToNumber(int key);
    inline int drawAngle(int angle);
    void round2Judge(int key);
    void round3Judge(int key);
    void RoundInitial();
    NewspriteComponent* sprite_Point;
    NewspriteComponent* sprite_Plate;
    TimerComponent* timer;

    std::array<int,4> hit_type;//���������
    std::array<NewspriteComponent*,4>sprite_colors;//�ĸ�color
    int cnt=0;//��ǰΪ�ڼ�������Ҫ���
    bool neednextRound=0;//��ʾ�Ƿ����նɱ
    bool isHit=0;//�����Ƿ��Ѿ������
    int TargetAngle=0;//round3��Ŀ��
    bool state_INHIT=0;//״̬����ʾhit�����ж�
    bool colorInitial=0;//��ʾ���ڵ��������Ƿ��ʼ���ɹ�
};

#endif
