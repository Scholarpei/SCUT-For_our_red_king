#ifndef JUMPCOMPONENT_H
#define JUMPCOMPONENT_H
#include <QVector2D>
#include "component.h"
#include "gameobject.h"
class JumpComponent : public Component
{
public:
    explicit JumpComponent(QObject *parent = nullptr,GameObject* gameObject = nullptr);

    void Update() override;
private:
    float mSpeed;
    GameObject* mGameObject;
};

#endif // JUMPCOMPONENT_H
