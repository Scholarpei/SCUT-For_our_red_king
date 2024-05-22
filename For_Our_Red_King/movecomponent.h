#ifndef MOVECOMPONENT_H
#define MOVECOMPONENT_H
#include <QVector2D>
#include "component.h"
#include "gameobject.h"
class MoveComponent : public Component
{
public:
    explicit MoveComponent(GameObject* gameObject = nullptr);

    //!每帧更新
    void Update() override;

private:
};

#endif // MOVECOMPONENT_H
