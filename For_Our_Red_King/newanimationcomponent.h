#ifndef NEWANIMATIONCOMPONENT_H
#define NEWANIMATIONCOMPONENT_H

#include "animationComponent.h"
#include "game.h"

class NewAnimationComponent : public AnimationComponent
{
public:
    explicit NewAnimationComponent(class GameObject* gameObject=nullptr,int drawOrder = 200,Game* game = nullptr);
    ~NewAnimationComponent();
    //相比于animationComponent有以下更改：初始化的时候可以设置相对于原先位置的偏移量、设置画的Width与Height而不是由GameObject决定
    //图片非连续的动画，为了制作连续的效果而通过改变绘画的透明度实现动画效果
    //其余部分保持一致

    void Draw()override;
    void setOffset(float xoffset,float yoffset);//设置偏移量
    void setRect(int w,int h);//设置宽高
    void Update()override;
    void setTransformDirection(bool dir);//设置渐变方向

private:
    Game* mGame;
    short TICKS_PER_FRAME = SYSTEM::durationPerFrame;
    bool transformDirection = 1;   //!<不透明度渐变方向 1为逐渐出现，0为逐渐消失
    int mWidth,mHeight;//!<单独的绘制区域大小
    float xOffset,yOffset;//!<绘制相比于GameObject原先的offset
};

#endif // NEWANIMATIONCOMPONENT_H
