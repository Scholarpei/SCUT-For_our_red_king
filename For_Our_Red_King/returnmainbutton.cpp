#include "returnmainbutton.h"
#include "standard.h"
#include "game.h"
ReturnMainButton::ReturnMainButton(QObject *parent,Game* game)
    : Buttons{parent,game}
{
    this->setPosition(BUTTONS::returnMainButtonPOS);
    this->setOffPicture(BUTTONS::returnMainButtonTYPE1);
    this->setOnPicture(BUTTONS::returnMainButtonTYPE2);
    this->sprite->reload();
}
void ReturnMainButton::buttonFunction()
{
    qDebug()<<"returnMain";
    this->mGame->mGoToNextLevel = 1;
}
