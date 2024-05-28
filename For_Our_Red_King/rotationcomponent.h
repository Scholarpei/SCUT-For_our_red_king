#ifndef ROTATIONCOMPONENT_H
#define ROTATIONCOMPONENT_H

#include "spritecomponent.h"

class rotationComponent : public spriteComponent
{
public:
    explicit rotationComponent(class GameObject* gameObject=nullptr,int drawOrder=100);
    virtual void Draw()override;
    void setAngle(int=0);//!< 改变旋转的角度

    void initial();
protected:
    double R;
    double alpha;
    double DrawAngle;
    int CenWidth;
    int CenHeight;
    double posX;
    double posY;
    void setHW();
};

#endif // ROTATIONCOMPONENT_H
