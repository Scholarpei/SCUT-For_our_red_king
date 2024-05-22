#ifndef FALLCOMPONENT_H
#define FALLCOMPONENT_H
#include <QVector2D>
#include "component.h"
#include "gameobject.h"
#include"standard.h"
class FallComponent : public Component
{
public:
   explicit FallComponent(GameObject* gameObject = nullptr);
    void Update() override;

};

#endif // FALLCOMPONENT_H
