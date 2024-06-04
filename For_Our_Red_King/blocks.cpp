#include "blocks.h"
#include "standard.h"
#include "game.h"
#include "player.h"
#include <math.h>

Block::Block(QObject *parent, Game *game):
    GameObject(parent, game)
{
    this->attendCollision = true;
    this->mGame  =game;
    this->gameObjectType = GameObject::Type::Building;

    // 有什么需要的component吗
}

void Block::Update()
{

}

int Block::getX()
{
    return this->gridPosition.x() * SYSTEM::tileSide;
}

int Block::getY()
{
    return this->gridPosition.y() * SYSTEM::tileSide;
}

int Block::getWidth()
{
    return this->gridSize.x() * SYSTEM::tileSide;
}

int Block::getHeight()
{
    return this->gridSize.y() * SYSTEM::tileSide;
}

void Block::beingCollide(GameObject *s)
{

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

RockSpawner::RockSpawner::RockSpawner(short id, bool up, bool down, bool left, bool right, int inWidth, int inHeight, short durationPerFrame):
    up(up),down(down),left(left),right(right),inWidth(inWidth),inHeight(inHeight),durationPerFrame(durationPerFrame)
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
            b->setDurationPerFrame(spawner.durationPerFrame);

            this->bricks[i][j] = b;
            // this->mGame->removeGameObject(b);
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
                                     interface.position[3],
                                     interface.durationPerFrame);
    this->initialize(spawner, QVector2D(interface.position[0], interface.position[1]));
}

void BlockRock::Update()
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
        {12, {TILES::redP1,
              TILES::redP2,
              TILES::redP3,
              TILES::redP1,
              TILES::redP2,
              TILES::redP3,
              TILES::redP1,
              TILES::redP2,
              TILES::redP3}},
        {21, {TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile,
              TILES::masuTile}},
        {22,{TILES::air,
             TILES::air,
             TILES::air,
             TILES::air,
             TILES::air,
             TILES::air,
             TILES::air,
             TILES::air,
             TILES::air}},
        {23, {TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile,
              TILES::pftTile}},
        {31, {TILES::door1}},
        {41, {TILES::money}},
        {42, {TILES::broken}},
        {43, {TILES::screen2}},
        {44, {TILES::bench}},
        {45, {TILES::flag}},
        {46, {TILES::ladder1}},
        {47, {TILES::ladder2}},
        {48, {TILES::ladder3}},
        {49, {TILES::barrel}},
        {50, {TILES::plate1}}
    };
    return mapping[ID];
}

void InterfaceBlock::initializeRock(short textureID, QVector2D posi, QVector2D inSize, bool up, bool down, bool left, bool right, short durationPerFrame)
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
    this->durationPerFrame = durationPerFrame;
}

void InterfaceBlock::initializeBackGround(short textureID, short durationPerFrame)
{
    this->category = 1;
    this->textureID = textureID;
    this->durationPerFrame = durationPerFrame;
}

void InterfaceBlock::initializeDoor(short texturID, QVector2D posi, short type, short durationPerFrame)
{
    this->category = 2;
    this->textureID = texturID;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
    this->status[0] = type;
    this->durationPerFrame = durationPerFrame;
}

void InterfaceBlock::initializeDecoration(short texturID, QVector2D posi, short type, short durationPerFrame)
{
    this->category = 3;
    this->textureID = texturID;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
    this->status[0] = type;
    this->durationPerFrame = durationPerFrame;
}

void InterfaceBlock::initializeBar(short textureID, QVector2D posi)
{
    this->category = 4;
    this->textureID = textureID;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
}

void InterfaceBlock::initializeDamage(short texturID, QVector2D posi, short type, short interval, short damage, QVector2D size, short durationPerFrame)
{
    this->category = 5;
    this->textureID = texturID;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
    this->position[2] = size.x();
    this->position[3] = size.y();
    this->status[0] = type;
    this->durationPerFrame = durationPerFrame;
    this->status[1] = interval;
    this->status[2] = damage;
}

void InterfaceBlock::initializeLine(short id, QVector2D posi, bool isHorizontal, bool attendCollision, short scale, short dpf)
{
    this->category = 6;
    this->textureID = id;
    this->position[0] = posi.x();
    this->position[1] = posi.y();
    this->status[0] = isHorizontal;
    this->status[1] = attendCollision;
    this->status[2] = scale;
    this->durationPerFrame = dpf;
}

Block *InterfaceBlock::cateToPointer(int cate, Game *game)
{
    Block* block = nullptr;
    switch (cate) {
    case 0:
    {
        block = new BlockRock(game, game);
        break;
    }
    case 1:
    {
        block = new BlockBack(game, game);
        break;
    }
    case 2:
    {
        block = new BlockDoor(game, game);
        break;
    }
    case 3:
    {
        block = new BlockDecoration(game, game);
        break;
    }
    case 4:
    {
        block = new BlockBar(game, game);
        break;
    }
    case 5:
    {
        block = new BlockDamage(game, game);
        break;
    }
    case 6:
    {
        block = new BlockLine(game, game);
        break;
    }
    default:
    {
        qDebug()<<"wrong category in block interface!!!!";
        block = new BlockDecoration(game, game);
        break;
    }
    }
    return block;
}

void InterfaceBlock::createBlock(Game *game)
{
    Block* block = this->cateToPointer(this->category, game);
    game->createGameObject(block);
    block->initialize(*this);
}

BlockBack::BlockBack(QObject *parent, Game *game):
    Block(parent, game)
{
    this->attendCollision = false;
}

void BlockBack::initialize(const AnimationLoader &anime, short dpf)
{
    this->gridPosition = QVector2D(0, 0);
    this->gridSize = QVector2D(SYSTEM::windowWidth / SYSTEM::tileSide,
                               SYSTEM::windowHeight / SYSTEM::tileSide);
    this->setPosition(QVector2D(0, 0));
    this->mWidth = SYSTEM::windowWidth;
    this->mHeight = SYSTEM::windowHeight;

    this->bricks.resize(1, std::vector<Brick*>(1));

    Brick* b = new Brick(this, mGame, DRAWORRDER::backGround);
    b->initialize(anime, this->gridPosition, this->gridSize);
    b->setDurationPerFrame(dpf);
    this->bricks[0][0] = b;
}

void BlockBack::initialize(const InterfaceBlock &interface)
{
    this->initialize(interface.toAnime(interface.textureID)[0],
                     interface.durationPerFrame);
}


void BlockDoor::openDoor()
{
    this->isOpen = true;
    this->bricks[0][0]->animation->play(false);
}

BlockDoor::BlockDoor(QObject *parent, Game *game):
    Block(parent, game)
{
    this->attendCollision = true;  // 是否要参与碰撞
}

void BlockDoor::initialize(const AnimationLoader &anime, QVector2D posi, short type, short dpf)
{
    this->gridPosition = posi;
    this->gridSize = QVector2D(ceil((double)anime.GetpixX() / SYSTEM::imgSide),
                               ceil((double)anime.GetpixY() / SYSTEM::imgSide));
    this->setPosition(QVector2D(this->getX(), this->getY()));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(1, std::vector<Brick*>(1));

    Brick* b = new Brick(this, mGame, DRAWORRDER::door);
    b->initialize(anime, this->gridPosition, this->gridSize);
    b->setDurationPerFrame(dpf);
    this->bricks[0][0] = b;

    this->type = type;
    switch(this->type)
    {
    case 1:
    {
        break;
    }
    case 2:     // 退出游戏
    {
        this->isOpen = true;
        break;
    }
    case 3:
    {
        break;
    }
    }
}

void BlockDoor::initialize(const InterfaceBlock &interface)
{
    this->initialize(interface.toAnime(interface.textureID)[0],
                     QVector2D(interface.position[0],
                               interface.position[1]),
                     interface.status[0],
                     interface.durationPerFrame);
}

void BlockDoor::Update()
{
    // TODO 检测怪物数量，检测玩家位置，发送下一关信号
    switch(this->type)
    {
    case 1:
    {
        break;
    }
    case 2:
    {
        break;
    }
    case 3:
    {
        break;
    }
    }
}

void BlockDoor::beingCollide(GameObject *s)
{
    // TODO 检测怪物数量，检测玩家位置，发送下一关信号
    if (this->isOpen)
    {
        switch(this->type)
        {
        case 1:
        {
            break;
        }
        case 2:
        {
            this->isOpen = false;
            this->mGame->ExitGame();//退出游戏
            break;
        }
        case 3:
        {
            break;
        }
        }
    }
}

BlockDecoration::BlockDecoration(QObject *parent, Game *game):
    Block(parent, game)
{
    this->attendCollision = false;
}

void BlockDecoration::initiialize(const AnimationLoader &anime, QVector2D posi, short type, short dpf)
{
    this->gridPosition = posi;
    this->gridSize = QVector2D(ceil((double)anime.GetpixX() / SYSTEM::imgSide),
                               ceil((double)anime.GetpixY() / SYSTEM::imgSide));
    this->setPosition(QVector2D(this->getX(), this->getY()));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(1, std::vector<Brick*>(1));

    Brick* b = new Brick(this, mGame, DRAWORRDER::door);
    b->initialize(anime, this->gridPosition, this->gridSize);
    b->setDurationPerFrame(dpf);
    this->bricks[0][0] = b;

    this->type = type;
}

void BlockDecoration::initialize(const InterfaceBlock &interface)
{
    this->initiialize(interface.toAnime(interface.textureID)[0],
                      QVector2D(interface.position[0],
                                interface.position[1]),
                      interface.status[0],
                      interface.durationPerFrame);
}

BlockBar::BlockBar(QObject *parent, Game *game):
    Block(parent, game)
{
    this->attendCollision = false;
}

void BlockBar::initialize(BleedingComponent *bar, int posX, int posY)
{
    this->gridPosition = QVector2D(0, 0);
    this->gridSize = QVector2D(0, 0);
    this->setPosition(QVector2D(posX, posY));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(0, std::vector<Brick*>(0));

    this->HPbar = bar;
    this->addComponent(this->HPbar);
}

void BlockBar::initialize(const InterfaceBlock &interface)
{
    BleedingComponent *bar = new BleedingComponent(this);

    this->initialize(bar,
                     interface.position[0],
                     interface.position[1]);


}

void BlockBar::Update()
{
    int hp = this->mGame->mPlayer->getHP();
    if (hp != this->hp)
    {
        this->HPbar->changeHP(hp);
        this->hp = hp;
    }
}

BlockDamage::BlockDamage(QObject *parent, Game *game):
    Block(parent, game)
{

}

void BlockDamage::initialize(const AnimationLoader &anime, QVector2D posi, short type, short dpf,  short interval, short damage, QVector2D size)
{
    QVector2D singleSize = QVector2D(ceil((double)anime.GetpixX() / SYSTEM::imgSide),
                                     ceil((double)anime.GetpixY() / SYSTEM::imgSide));

    this->gridPosition = posi;
    this->gridSize = QVector2D(singleSize.x() * size.x(),
                               singleSize.y() * size.y());
    this->setPosition(QVector2D(this->getX(), this->getY()));
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(size.x(), std::vector<Brick*>(size.y()));

    for(int i = 0; i < size.x(); i++)
    {
        for ( int j = 0; j < size.y(); j++)
        {
            Brick* b = new Brick(this, mGame, DRAWORRDER::door);
            b->initialize(anime,
                          QVector2D(this->gridPosition.x() + i * singleSize.x(),
                                    this->gridPosition.y() + j * singleSize.y()),
                          singleSize);
            b->setDurationPerFrame(dpf);

            this->bricks[i][j] = b;
        }
    }

    // Brick* b = new Brick(this, mGame, DRAWORRDER::door);
    // b->initialize(anime, this->gridPosition, this->gridSize);
    // b->setDurationPerFrame(dpf);
    // this->bricks[0][0] = b;

    this->HURT_INTERVAL = interval;
    this->current_tick = 0;
    this->damage = damage;

    switch(type)
    {
    case 1:
    {
        this->attendCollision = false;
        break;
    }
    case 2:
    {
        this->attendCollision = true;
        break;
    }
    default:
        break;
    }
}

void BlockDamage::initialize(const InterfaceBlock &interface)
{
    this->initialize(interface.toAnime(interface.textureID)[0],
                     QVector2D(interface.position[0],
                               interface.position[1]),
                     interface.status[0],
                     interface.durationPerFrame,
                     interface.status[1],
                     interface.status[2],
                     QVector2D(interface.position[2],
                               interface.position[3]));
}

void BlockDamage::Update()
{
    if(this->current_tick != 0)
    {
        this->current_tick--;
    }
}

void BlockDamage::beingCollide(GameObject *s)
{
    if(s->gameObjectType != GameObject::Type::Player)
    {
        return;
    }
    if(this->current_tick == 0)
    {
        this->mGame->mPlayer->loseHPEvent(this->damage);
        this->current_tick = this->HURT_INTERVAL;
    }
}


BlockLine::BlockLine(QObject *parent, Game *game):
    Block(parent, game)
{

}

void BlockLine::initialize(short id, QVector2D posi, bool isHorizontal, bool attendCollision, short dpf, short scale)
{
    this->attendCollision = attendCollision;
    std::vector<AnimationLoader> animes = this->getAnime(id);
    short length = animes.size();

    short i,j;

    this->gridPosition = posi;
    this->setPosition(QVector2D(this->getX(), this->getY()));

    if (isHorizontal)
    {
        this->gridSize = QVector2D(length * scale,
                                   1 * scale);
        j = 0;
        i = scale;
    }
    else
    {
        this->gridSize = QVector2D(1 * scale,
                                   length * scale);
        i = 0;
        j = scale;
    }
    this->mWidth = this->getWidth();
    this->mHeight = this->getHeight();

    this->bricks.resize(1, std::vector<Brick*>(length));

    for (int var = 0; var < length; ++var)
    {
        Brick* b = new Brick(this, mGame, DRAWORRDER::item);
        b->initialize(animes[var],
                      QVector2D(posi.x() + var * i,
                                posi.y() + var * j),
                      QVector2D(scale, scale));
        b->setDurationPerFrame(dpf);

        this->bricks[0][var] = b;
    }
}

void BlockLine::initialize(const InterfaceBlock &interface)
{
    this->initialize(interface.textureID,
                     QVector2D(interface.position[0],
                               interface.position[1]),
                     interface.status[0],
                     interface.status[1],
                     interface.durationPerFrame,
                     interface.status[2]);
}

std::vector<AnimationLoader> BlockLine::getAnime(short id)
{
    std::map<short, std::vector<AnimationLoader>> mapping =
    {
        {1, {TILES::q,
             TILES::u,
             TILES::i,
             TILES::t}},
        {2, {TILES::f,
             TILES::o,
             TILES::r}},
        {3, {TILES::o,
             TILES::u,
             TILES::r}},
        {4, {TILES::r,
             TILES::e,
             TILES::d}},
        {5, {TILES::k,
             TILES::i,
             TILES::n,
             TILES::g}}
    };

    return mapping[id];
}
