#include "spritecomponent.h"
#include "gameobject.h"
#include "game.h"


spriteComponent::spriteComponent(GameObject* gameObject,int drawOrder):
    Component(gameObject),
    mDrawOrder(drawOrder)
{
    mGameObject->getGame()->createSprite(this);
    mWidth = mGameObject->mWidth;
    mHeight = mGameObject->mHeight;
}

spriteComponent::~spriteComponent()
{
    mGameObject->getGame()->removeSprite(this);
}

//!绘画
void spriteComponent::Draw()
{
    mGameObject->mGame->mPainter->drawPixmap(mGameObject->getPosition().x(),mGameObject->getPosition().y(),mWidth * mGameObject->getScale().x(),mHeight * mGameObject->getScale().y(),QPixmap(this->imageLocation));
    //positonx positiony mwidth * Scalex mHeight*Scaley
    //考虑位置，缩放，矩阵大小
}

int spriteComponent::getDrawOrder()const
{
    return mDrawOrder;
}

void spriteComponent::setDrawOrder(int o)
{
    this->mDrawOrder = o;
}

//! 宽度的get
int spriteComponent::getWidth() const
{
    return this->mWidth;
}
//! 高度的get
int spriteComponent::getHeight() const
{
    return this->mHeight;
}

void spriteComponent::SetTexture(QString imageLocation)
{
    this->imageLocation = imageLocation;
}

void spriteComponent::Update()
{
    //不用写，因为一张不变的图片不会更新
}


