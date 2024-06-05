#ifndef PLAYERTELEPORTATIONCOMPONENT_H
#define PLAYERTELEPORTATIONCOMPONENT_H

#include "component.h"
#include <QVector2D>

class PlayerTeleportationComponent : public Component
{
public:
    PlayerTeleportationComponent(class GameObject* gameObject=nullptr,QVector2D targetPosition = QVector2D(0,0));
    ~PlayerTeleportationComponent();
    void Update()override;
private:
    int nowtime = 0;
    QVector2D tarPos = QVector2D(0,0),startPos = QVector2D(0,0);
    float SpeedX = 0, SpeedY = 0;
};

#endif // PLAYERTELEPORTATIONCOMPONENT_H
