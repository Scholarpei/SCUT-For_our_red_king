#ifndef TIMERCOMPONENT_H
#define TIMERCOMPONENT_H
#include "component.h"
#include "qtmetamacros.h"

//!< 被改得面目全非 专门为qte用的
// typedef void (*fptr)();
class FightQTE;
class TimerComponent
	: public Component
{
public:
	TimerComponent(GameObject *object = nullptr, FightQTE *mQTE = nullptr);
	~TimerComponent();
	// startRun开始每帧发送信号
	void startRun();
	void EndRun();
	// update一次nowtime+1
	// nowtime=timewidth发送信号
	void Update();				  // 更新
	void setTimeWidth(int width); // 设置时间多少时使用事件函数
	// void setFunction(fptr = nullptr);//设置循环的事件函数

protected:
	//	void (*TimeFunction)();//需要循环的事件函数X 失败的函数指针用法。
	GameObject *father_Object;
	int TimeWidth = 0; // 跑几次发送事件
	bool isRun = 0;	   // 是否启动
	int NowTime = 0;
	FightQTE *mQTE;

signals:
};
#endif // TIMERCOMPONENT_H
