#include "stopbutton.h"
#include "standard.h"
#include "game.h"
StopButton::StopButton(QObject *parent,Game* game)
    : Buttons{parent,game}
{
    this->setPosition(BUTTONS::stopButtonPOS);
    this->setOffPicture(BUTTONS::stopButtonTYPE1);
    this->setOnPicture(BUTTONS::stopButtonTYPE2);
    this->sprite->reload();
}

void StopButton::buttonFunction()
{
    if(this->isButtonOn)
    {
        this->setOffPicture(BUTTONS::stopButtonTYPE3);
        this->setOnPicture(BUTTONS::stopButtonTYPE4);
        this->getGame()->stop=1;
    }else
    {
        this->setOffPicture(BUTTONS::stopButtonTYPE1);
        this->setOnPicture(BUTTONS::stopButtonTYPE2);
        this->getGame()->stop=0;
    }
}
