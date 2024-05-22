
#include "brick.h"

Brick::Brick(QObject *parent, Game *game, int drawOrder):
    GameObject(parent, game)
{
    this->attendCollision = false;
    this->mGame = game;
    this->gameObjectType = GameObject::Type::Building;

    this->animation = new AnimationComponent(this, drawOrder);

    this->addComponent(animation);
}

void Brick::initialize(const AnimationLoader &anime, QVector2D posi, QVector2D size)
{
    this->animation->resetAnimation(anime);
    this->gridPosition = posi;
    this->gridSize = size;

    this->setPosition(QVector2D(this->getX(),
                                this->getY()));

    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();
}

int Brick::getX()
{
    return this->gridPosition.x() * this->SIDE;
}

int Brick::getY()
{
    return this->gridPosition.y() * this->SIDE;
}

int Brick::getWidth()
{
    return this->gridSize.x() * this->SIDE;
}

int Brick::getHeight()
{
    return this->gridSize.y() * this->SIDE;
}
