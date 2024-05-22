#include "mytimer.h"
#include "game.h"

myTimer::myTimer(QObject *parent,Game* game)
    : QObject{parent}
{
    deltaTime = 0;
    ticksCount = 0;
    recordTime = new QElapsedTimer();
    mGame = game;
}

myTimer::~myTimer()
{
    mGame->removeMyTimer(this);
}
