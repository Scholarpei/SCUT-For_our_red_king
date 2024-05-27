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
    willReStart(true)
{

}

AnimationComponent::~AnimationComponent()
{
    mGameObject->getGame()->removeSprite(this);
}

void AnimationComponent::Draw()
{
    QRect target(this->mGameObject->getPosition().x(),
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
    }
    this->mGameObject->mGame->mWindow->mPainter->drawPixmap(target, frame);

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



