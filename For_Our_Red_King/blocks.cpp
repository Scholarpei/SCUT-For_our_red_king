#include "blocks.h"
#include "standard.h"
#include "game.h"
#include <math.h>

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

    // for(const std::vector<Brick*> &bs: this->bricks)
    // {
    //     for (Brick* b : bs)
    //     {
    //         delete b;
    //     }
    // }
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
    std::vector<AnimationLoader> animes = InterfaceBlock::toAnime(id);
    animes.resize(9, TILES::masuTile);
    this->bricks = std::array<AnimationLoader, 9>();
    for(int i = 0; i < 9; i++)
    {
        this->bricks[i] = animes[i];
    }
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

BlockRock::BlockRock(QObject *parent, Game *game):
    Block(parent, game)
{

}

void BlockRock::initialize(RockSpawner::RockSpawner spawner, QVector2D posi)
{
    this->gridPosition = posi;
    this->gridSize = QVector2D(spawner.getWidth(), spawner.getHeight());
    this->setPosition(QVector2D(this->getX(), this->getY()));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(spawner.getWidth(), std::vector<Brick*>(spawner.getHeight()));

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

void BlockRock::update()
{

}

std::vector<AnimationLoader> InterfaceBlock::toAnime(short ID)
{
    std::map<short, std::vector<AnimationLoader>> mapping =
    {
        {1, {BACKGROUND::bg1}},
        {11, {TILES::industrialTile1,
              TILES::industrialTile2,
              TILES::industrialTile3,
              TILES::industrialTile4,
              TILES::industrialTile5,
              TILES::industrialTile6,
              TILES::industrialTile7,
              TILES::industrialTile8,
              TILES::industrialTile9}},
        {21, {TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile}},
        {31, {TILES::door1}}
    };
    return mapping[ID];
}

void InterfaceBlock::initializeRock(short textureID, QVector2D posi, QVector2D inSize, bool up, bool down, bool left, bool right)
{
    this->category = 0;
    this->textureID = textureID;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
    this->position[2] = inSize.x();
    this->position[3] = inSize.y();
    this->status[0] = up;
    this->status[1] = down;
    this->status[2] = left;
    this->status[3] = right;
}

void InterfaceBlock::initializeBackGround(short textureID)
{
    this->category = 1;
    this->textureID = textureID;
}

void InterfaceBlock::initializeDoor(short texturID, QVector2D posi, short type)
{
    this->category = 2;
    this->textureID = texturID;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
    this->status[0] = type;
}

BlockBack::BlockBack(QObject *parent, Game *game):
    Block(parent, game)
{
    this->attendCollision = false;
}

void BlockBack::initialize(const AnimationLoader &anime)
{
    this->gridPosition = QVector2D(0, 0);
    this->gridSize = QVector2D(SYSTEM::windowWidth / SYSTEM::tileSide, SYSTEM::windowHeight / SYSTEM::tileSide);
    this->setPosition(QVector2D(0, 0));
    this->mWidth = SYSTEM::windowWidth;
    this->mHeight = SYSTEM::windowHeight;

    this->bricks.resize(1, std::vector<Brick*>(1));

    Brick* b = new Brick(this, mGame, DRAWORRDER::backGround);
    b->initialize(anime, this->gridPosition, this->gridSize);
    this->bricks[0][0] = b;
}

void BlockBack::initialize(const InterfaceBlock &interface)
{
    this->initialize(interface.toAnime(interface.textureID)[0]);
}

void BlockBack::update()
{

}

void BlockDoor::openDoor()
{
    this->isOpen = true;
    this->bricks[0][0]->animation->play(false);
}

BlockDoor::BlockDoor(QObject *parent, Game *game):
    Block(parent, game)
{
    this->attendCollision = false;  // 是否要参与碰撞
}

void BlockDoor::initialize(const AnimationLoader &anime, QVector2D posi, short type)
{
    this->gridPosition = posi;
    this->gridSize = QVector2D(floor(anime.GetpixX()), floor(anime.GetpixY()));
    this->setPosition(QVector2D(this->getX(), this->getY()));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(1, std::vector<Brick*>(1));

    Brick* b = new Brick(this, mGame, DRAWORRDER::door);
    b->initialize(anime, this->gridPosition, this->gridSize);
    this->bricks[0][0] = b;

    this->type = type;
}

void BlockDoor::initialize(const InterfaceBlock &interface)
{
    this->initialize(interface.toAnime(interface.textureID)[0],
                     QVector2D(interface.position[0],
                               interface.position[1]),
                     interface.status[0]);
}

void BlockDoor::update()
{
    // TODO 检测怪物数量，检测玩家位置，发送下一关信号
}
