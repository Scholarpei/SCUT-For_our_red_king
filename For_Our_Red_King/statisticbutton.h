#ifndef STATISTICBUTTON_H
#define STATISTICBUTTON_H

#include "buttons.h"

class StatisticButton : public Buttons
{
public:
    explicit StatisticButton(QObject *parent = nullptr,Game* game = nullptr);
    virtual void buttonFunction()override;
};

#endif // STATISTICBUTTON_H
