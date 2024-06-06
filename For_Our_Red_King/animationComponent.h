#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "spritecomponent.h"
#include "animationloader.h"
#include "standard.h"


class AnimationComponent: public spriteComponent
{
public:
    explicit AnimationComponent(class GameObject* gameObject=nullptr,int drawOrder=200);
    virtual ~AnimationComponent();

    // 绘制函数
    virtual void Draw();
    // 重置并传入动画雪碧图。调用后会自动停止播放！如有需要请再次调用 play
    virtual void resetAnimation(const AnimationLoader& animation);

    // 开始显示并播放动图，参数设置是否重复播放。若只想显示不想播放，请调用 setDisplay
    void show(bool do_repeat);
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
    // 设置是否显示
    void setDisplay(bool do_display);
    // 设置不透明度
    void setOpacity(double opa);
    // 多少刻切换一帧动画
    void TickPerFrame(short durationPerFrame);
    short TickPerFrame();

    //下面为令子类访问数据的辅助函数
    void setCurrentTick(int val);//用来子类设置CurrentTick
    int getCurrentTick();//子类获取CurrentTick
    int getCurrentFrame();//子类获取
    bool getIsRepeating();//子类获取
    void setCurrentFrame(int val);//子类设置

    bool isPlaying;             // 是否继续播放
    AnimationLoader animation;  // 动画本尊哒
protected:
    //以下都是实现切换动画所用
    short TICKS_PER_FRAME = SYSTEM::durationPerFrame;

    QPixmap spriteSheet;        // 雪碧图
    int currentTick;            // 积累到切换下一帧动图的帧数
    int currentFrame;           // 当前在第几帧

    bool isRepeating;           // 是否重复播放
    bool willReStart;           // 播放时是否重新开始
    bool isDisplaying;          // 图片是否显示
    double opacity;             // 不透明度

    //下一帧
    void nextTick();

private:


};


#endif // ANIMATIONCOMPONENT_H
