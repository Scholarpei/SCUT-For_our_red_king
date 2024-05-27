#include "standard.h"
#include "brick.h"
#include "game.h"


Brick::Brick(QObject *parent, Game *game, int drawOrder):
    GameObject(parent, game)
{
    this->attendCollision = false;
    this->mGame = game;
    this->gameObjectType = GameObject::Type::Building;

    this->animation = new AnimationComponent(this, drawOrder);

    this->addComponent(animation);
    this->mGame->createSprite(this->animation);
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

void Brick::setDurationPerFrame(short dpf)
{
    if(dpf != 0)
    {
        this->animation->TickPerFrame(dpf);
        this->animation->play(true);
    }
}

int Brick::getX()
{
    return this->gridPosition.x() * SYSTEM::tileSide;
}

int Brick::getY()
{
    return this->gridPosition.y() * SYSTEM::tileSide;
}

int Brick::getWidth()
{
    return this->gridSize.x() * SYSTEM::tileSide;
}

int Brick::getHeight()
{
    return this->gridSize.y() * SYSTEM::tileSide;
}
