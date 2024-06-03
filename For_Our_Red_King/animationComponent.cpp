#include "animationComponent.h"
#include "gameobject.h"
#include "game.h"
#include <QTransform>

AnimationComponent::AnimationComponent(GameObject *gameObject, int drawOrder):
    spriteComponent(gameObject, drawOrder),
    currentTick(0),
    currentFrame(0),
    isPlaying(false),
    isRepeating(false),
    willReStart(true),
    isDisplaying(true),
    opacity(1.0)
{

}

AnimationComponent::~AnimationComponent()
{
    mGameObject->getGame()->removeSprite(this);
}

void AnimationComponent::Draw()
{
    if(this->isDisplaying)
    {
        this->mGameObject->mGame->mWindow->mPainter->setOpacity(this->opacity);
        QRect target1(this->mGameObject->getPosition().x(),
                      this->mGameObject->getPosition().y(),
                      mGameObject->mWidth * mGameObject->getScale().x(),
                      mGameObject->mHeight * mGameObject->getScale().y());

        QRect source(this->animation.GetpixX() * this->currentFrame,
                     0,
                     this->animation.GetpixX(),
                     this->animation.GetpixY());

        QPixmap frame = this->spriteSheet.copy(source);
        if (this->mGameObject->getDrawDirection() != 1){
            // 创建一个水平翻转的变换矩阵
            QTransform transform;
            transform.scale(-1, 1);  // 水平翻转
            frame = frame.transformed(transform);
            QRect target2(this->mGameObject->getPosition().x()-15,
                          this->mGameObject->getPosition().y(),
                          mGameObject->mWidth * mGameObject->getScale().x(),
                          mGameObject->mHeight * mGameObject->getScale().y());
            //这里-15是因为我们的图片是有透明区域的，翻转过后人物会翻转到另一边，我们通过平移绘画位置解决这一点（经过尝试，-15是比较合理的值）
            this->mGameObject->mGame->mWindow->mPainter->drawPixmap(target2, frame);
        }
        else{
            this->mGameObject->mGame->mWindow->mPainter->drawPixmap(target1, frame);
        }
    }

    if(this->isPlaying)
    {
        this->nextTick();
    }
}

void AnimationComponent::resetAnimation(const AnimationLoader &animation)
{
    this->animation = animation;
    this->stop();
    this->spriteSheet = QPixmap(animation.GetpixAddress());
}

void AnimationComponent::show(bool do_repeat)
{
    this->setDisplay(true);
    this->play(do_repeat);
}

void AnimationComponent::play(bool do_repeat)
{
    this->isRepeating = do_repeat;
    if (this->willReStart) this->backToStart();
    this->isPlaying = true;
}

void AnimationComponent::stop()
{
    this->isPlaying = false;
    this->willReStart = true;
}

void AnimationComponent::pause()
{
    this->isPlaying = false;
    this->willReStart = false;
}

void AnimationComponent::backToStart()
{
    this->currentFrame = 0;
    this->currentTick = 0;
}

void AnimationComponent::setRepeat(bool do_repeat)
{
    this->isRepeating = do_repeat;
}

void AnimationComponent::setDisplay(bool do_display)
{
    this->isDisplaying = do_display;
}

void AnimationComponent::setOpacity(bool opa)
{
    this->opacity = opa;
}

void AnimationComponent::TickPerFrame(short durationPerFrame)
{
    this->TICKS_PER_FRAME = durationPerFrame;
}

short AnimationComponent::TickPerFrame()
{
    return this->TICKS_PER_FRAME;
}

void AnimationComponent::nextTick()
{
    this->currentTick++;
    if (this->currentTick == this->TICKS_PER_FRAME)
    {
        this->currentTick = 0;
        this->currentFrame = (this->currentFrame + 1) % this->animation.GetpixFrame();
    }

    if(this->currentFrame == 0 && this->currentTick == 0 && !this->isRepeating)
    {
        this->isPlaying = false;
        this->currentFrame = this->animation.GetpixFrame() - 1;
        this->currentTick = this->TICKS_PER_FRAME - 1;
    }
}



