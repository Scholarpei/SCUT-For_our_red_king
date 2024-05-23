#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "spritecomponent.h"
#include "animationloader.h"


class AnimationComponent: public spriteComponent
{
public:
    explicit AnimationComponent(class GameObject* gameObject=nullptr,int drawOrder=100);
    ~AnimationComponent();

    // 绘制函数
    virtual void Draw();
    // 重置并传入动画雪碧图。调用后会自动停止播放！如有需要请再次调用 play
    virtual void resetAnimation(const AnimationLoader& animation);

    // 开始播放动图，第一次播放前确保已设置 AnimationLoader
    void play(bool do_repeat);
    // 停止动图在这一帧，但是下次播放会从头开始！
    void stop();
    // 暂停动图在这一帧，下次播放会继续播放
    void pause();
    // 设置动图回到初始帧， 不会影响正在播放与否
    void backToStart();
    // 设置是否重复动画
    void setRepeat(bool do_repeat);






private:
    //以下都是实现切换动画所用


    static const int TICKS_PER_FRAME = 6;


    QPixmap spriteSheet;        // 雪碧图
    int currentTick;            // 积累到切换下一帧动图的帧数
    int currentFrame;           // 当前在第几帧
    bool isPlaying;             // 是否继续播放
    bool isRepeating;           // 是否重复播放
    bool willReStart;           // 播放时是否重新开始

    AnimationLoader animation;  // 动画本尊哒

    //下一帧
    void nextTick();

};


#endif // ANIMATIONCOMPONENT_H
