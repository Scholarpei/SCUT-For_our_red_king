#include "statisticbutton.h"
#include "game.h"
#include "mainwindow.h"

StatisticButton::StatisticButton(QObject *parent,Game* game)
    : Buttons{parent,game}
{
    this->setPosition(BUTTONS::statisticButtonPOS);
    this->setOffPicture(BUTTONS::statisticButtonTYPE1);
    this->setOnPicture(BUTTONS::statisticButtonTYPE2);
    this->sprite->reload();
}

void StatisticButton::buttonFunction()
{
    qDebug()<<"show Statistic";
    this->mGame->stop = true;

    this->mGame->updateStatistic();
    this->mGame->mWindow->showStatisticWidget();
}
