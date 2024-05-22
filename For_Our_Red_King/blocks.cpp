#include "blocks.h"
#include "standard.h"
#include "game.h"

Block::Block(QObject *parent, Game *game):
    GameObject(parent, game)
{
    this->attendCollision = true;
    this->mGame  =game;
    this->gameObjectType = GameObject::Type::Building;

    // 有什么需要的component吗
}

Block::~Block()
{
    mGame->removeGameObject(this);
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }

    for(const std::vector<Brick*> &bs: this->bricks)
    {
        for (Brick* b : bs)
        {
            delete b;
        }
    }
}

void Block::update()
{

}

int Block::getX()
{
    return this->gridPosition.x() * Brick::SIDE;
}

int Block::getY()
{
    return this->gridPosition.y() * Brick::SIDE;
}

int Block::getWidth()
{
    return this->gridSize.x() * Brick::SIDE;
}

int Block::getHeight()
{
    return this->gridSize.y() * Brick::SIDE;
}


void RockSpawner::RockSpawner::fromID(short id)
{
    std::map<short, std::array<AnimationLoader, 9>> mapping =
    {
        {0, {TILES::industrialTile1,
             TILES::industrialTile2,
             TILES::industrialTile3,
             TILES::industrialTile4,
             TILES::industrialTile5,
             TILES::industrialTile6,
             TILES::industrialTile7,
             TILES::industrialTile8,
             TILES::industrialTile9}},
        {11, {TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile}}
    };
    this->bricks = mapping[id];
}

RockSpawner::RockSpawner::RockSpawner(short id, bool up, bool down, bool left, bool right, int inWidth, int inHeight):
    up(up),down(down),left(left),right(right),inWidth(inWidth),inHeight(inHeight)
{
    this->fromID(id);
}

int RockSpawner::RockSpawner::getWidth()
{
    return this->left + this->inWidth + this->right;
}

int RockSpawner::RockSpawner::getHeight()
{
    return this->up + this->inHeight + this->down;
}

AnimationLoader RockSpawner::RockSpawner::getAnime(int x, int y)
{
    short i;
    short j;

    if(this->left && x == 0)
    {
        i = 0;
    }
    else if(this->right && x == this->getWidth() - 1)
    {
        i = 2;
    }
    else
    {
        i = 1;
    }

    if(this->up && y==0)
    {
        j = 0;
    }
    else if(this->down && y == this->getHeight() - 1)
    {
        j = 2;
    }
    else
    {
        j = 1;
    }

    return this->bricks[3 * j + i];
}

void BlockRock::initialize(RockSpawner::RockSpawner spawner, QVector2D posi)
{
    this->gridPosition = posi;
    this->gridSize = QVector2D(spawner.getWidth(), spawner.getHeight());
    this->setPosition(QVector2D(this->getX(), this->getY()));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    for (int i = 0; i < spawner.getWidth(); i++)
    {
        for (int j = 0; j < spawner.getHeight(); j++)
        {
            Brick* b = new Brick(this, mGame, DRAWORRDER::ground);
            int x = this->gridPosition.x() + i;
            int y = this->gridPosition.y() + j;
            b->initialize(spawner.getAnime(i, j),
                          QVector2D(x, y),
                          QVector2D(1, 1));

            this->bricks[i][j] = b;
        }
    }
}


void BlockRock::initialize(const InterfaceBlock &interface)
{
    RockSpawner::RockSpawner spawner(interface.textureID,
                                     interface.status[0],
                                     interface.status[1],
                                     interface.status[2],
                                     interface.status[3],
                                     interface.position[2],
                                     interface.position[3]);
    this->initialize(spawner, QVector2D(interface.position[0], interface.position[1]));
}

void InterfaceBlock::initializeRock(short textureID, QVector2D size, QVector2D inSize, bool up, bool down, bool left, bool right)
{
    this->category = 0;
    this->textureID = textureID;
    this->position[0] = size.x();
    this->position[1] = size.y();
    this->position[2] = inSize.x();
    this->position[3] = inSize.y();
    this->status[0] = up;
    this->status[1] = down;
    this->status[2] = left;
    this->status[3] = right;
}
