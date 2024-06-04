#include "newanimationcomponent.h"
#include "gameobject.h"
#include "game.h"

NewAnimationComponent::NewAnimationComponent(GameObject * gameObject,int drawOrder,Game* game):
    AnimationComponent(gameObject,drawOrder)
{
    mGame = game;
    xOffset = 0;
    yOffset = 0;
}

NewAnimationComponent::~NewAnimationComponent()
{
    //执行父类的即可
    qDebug("new destr");
}

void NewAnimationComponent::Update()
{
    if(this->transformDirection)
        setOpacity((double)this->getCurrentFrame()/(this->animation.GetpixFrame()-1));
    else
        setOpacity(1-((double)this->getCurrentFrame()/(this->animation.GetpixFrame()-1)));
    //设置透明度
}

void NewAnimationComponent::setOffset(float xoffset,float yoffset)
{
    this->xOffset = xoffset;
    this->yOffset = yoffset;
}

void NewAnimationComponent::setRect(int w,int h)
{
    this->mWidth = w;
    this->mHeight = h;
}

void NewAnimationComponent::Draw()
{
    if(this->isDisplaying)
    {
            this->mGameObject->mGame->mWindow->mPainter->setOpacity(this->opacity);
            QRect target1(this->mGameObject->getPosition().x() + this->xOffset,
                          this->mGameObject->getPosition().y()+this->yOffset,
                          this->mWidth,
                          this->mHeight);

            QRect source(0,
                         0,
                         this->animation.GetpixX(),
                         this->animation.GetpixY());

            QPixmap frame = this->spriteSheet.copy(source);
            if (this->mGameObject->getDrawDirection() != 1){
                // 创建一个水平翻转的变换矩阵
                QTransform transform;
                transform.scale(-1, 1);  // 水平翻转
                frame = frame.transformed(transform);
                QRect target2(this->mGameObject->getPosition().x() + this->xOffset-15,
                              this->mGameObject->getPosition().y()+this->yOffset,
                              this->mWidth,
                              this->mHeight);
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

void NewAnimationComponent::setTransformDirection(bool dir)
{
    this->transformDirection = dir;
}






