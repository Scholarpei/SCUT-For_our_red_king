#ifndef TIMERCOMPONENT_H
#define TIMERCOMPONENT_H
#include "component.h"
#include "qtmetamacros.h"

//!< ���ĵ���Ŀȫ�� ר��Ϊqte�õ�
//typedef void (*fptr)();
class FightQTE;
class TimerComponent 
	:public Component
{
public:

    TimerComponent(GameObject* object = nullptr,FightQTE* mQTE=nullptr);
	~TimerComponent();
	//startRun��ʼÿ֡�����ź�
	void startRun();
	void EndRun();
	//updateһ��nowtime+1
	//nowtime=timewidth�����ź�
	void Update();//����
	void setTimeWidth(int width);//����ʱ�����ʱʹ���¼�����
    //void setFunction(fptr = nullptr);//����ѭ�����¼�����

protected:
//	void (*TimeFunction)();//��Ҫѭ�����¼�����X ʧ�ܵĺ���ָ���÷���
	GameObject* father_Object;
	int TimeWidth = 0;//�ܼ��η����¼�
	bool isRun = 0;//�Ƿ�����
	int NowTime = 0;
	FightQTE* mQTE;

signals:
};
#endif // TIMERCOMPONENT_H
