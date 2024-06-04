#ifndef RETURNMAINBUTTON_H
#define RETURNMAINBUTTON_H

#include "buttons.h"

class ReturnMainButton : public Buttons
{
public:
    explicit ReturnMainButton(QObject *parent = nullptr,Game* game=nullptr);
    virtual void buttonFunction()override;
};

#endif // RETURNMAINBUTTON_H
