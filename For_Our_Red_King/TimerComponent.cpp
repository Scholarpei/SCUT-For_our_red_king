#include "TimerComponent.h"
#include "FightQTE.h"
#include <QDebug>
#include "standard.h"
const int TIMEWIDTH = 1;
TimerComponent::TimerComponent(GameObject *object, FightQTE *mQTE) : Component(object)
{
    //    qDebug()<<"TimerComponentconstructor";
    father_Object = object;

    //?œZ???????width
    TimeWidth = TIMEWIDTH;
    this->mQTE = mQTE;
    isRun = true;
}

TimerComponent::~TimerComponent()
{
}

void TimerComponent::startRun()
{
    isRun = true;
}

void TimerComponent::EndRun()
{
    isRun = false;
}

void TimerComponent::Update()
{
    // qDebug()<<"timercomponent,update";
    if (isRun)
    {
        // qDebug()<<"enter if";

        if (NowTime >= TimeWidth)
        {
            // qDebug()<<"enter now";
            mQTE->centralFunction();
            NowTime = 0;
        }
        else
        { // qDebug()<<"nowtime++";
            NowTime++;
        }
    }
}

void TimerComponent::setTimeWidth(int width)
{
    if (width >= 0)
    {
        TimeWidth = width;
    }
}

// void TimerComponent::setFunction(fptr thisFunction)
//{
//     TimeFunction = thisFunction;
// }
