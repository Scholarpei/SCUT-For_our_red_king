#ifndef BUTTONS_H
#define BUTTONS_H

#include "gameobject.h"
#include "newspritecomponent.h"
#include <QString>
class Buttons : public GameObject
{
public:
    explicit Buttons(QObject *parent = nullptr,class Game* game = nullptr,int draworder=110);
    virtual void buttonFunction();
    void inputMousePressProcess(QMouseEvent * event);
    void inputMouseReleaseProcess(QMouseEvent * event);
    void setOnPicture(QString onpicture);
    void setOffPicture(QString offpicture);
    void Update();
protected:
    bool isButtonOn;
    bool isPressed;
    QString onPicture;
    QString offPicture;
    NewspriteComponent* sprite;

};

#endif // BUTTONS_H
