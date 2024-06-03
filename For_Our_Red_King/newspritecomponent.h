#ifndef NEWSPRITECOMPONENT_H
#define NEWSPRITECOMPONENT_H

#include "spritecomponent.h"
//这是个新的spritecomponent 能够实现旋转，缩放，透明度，以及设定绘画的位置
class NewspriteComponent : public spriteComponent
{
public:
    NewspriteComponent(GameObject *gameObject = nullptr, int drawOrder = 200);
    void Draw()override;
    void setAngle(int angle);
    void setScale(float scale);
    void setPos(int x,int y);
    void setNeedDraw(bool yesOrno);
    bool getNeedDraw()const;
    ~NewspriteComponent();
    // void setAlpha(int alpha);
protected:
    int drawAngle;//旋转角度
    float scale;//缩放倍率
    int posX;//绘画的x位置
    int posY;//绘画的y位置
    bool needDraw;
    //int alpha;//透明度 0-255
};

#endif // NEWSPRITECOMPONENT_H
