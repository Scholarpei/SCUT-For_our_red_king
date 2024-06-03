#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include "buttons.h"

class StopButton : public Buttons
{
public:
    explicit StopButton(QObject *parent = nullptr,class Game* game = nullptr);
    virtual void buttonFunction()override;
};

#endif // STOPBUTTON_H
