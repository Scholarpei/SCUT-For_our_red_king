#include "blocks.h"
#include "standard.h"
#include "game.h"
#include "player.h"
#include <math.h>
#include "monster.h"

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
    if(animes.size() < 9)
    {
        auto anime = animes[0];
        animes.resize(9);
        std::fill(animes.begin(), animes.end(), anime);
    }
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
        {12, {TILES::redP1,TILES::redP2,TILES::redP3,
              TILES::redP1, TILES::redP2,TILES::redP3,
              TILES::redP1,TILES::redP2,TILES::redP3}},
        {21, {TILES::masuTile}},
        {22, {TILES::air}},
        {23, {TILES::pftTile}},
        {24, {TILES::plateL,TILES::plateM,TILES::plateR,
              TILES::plateL,TILES::plateM,TILES::plateR,
              TILES::plateL,TILES::plateM,TILES::plateR}},
        {25, {TILES::pillarRa,TILES::pillarRa,TILES::pillarRa,TILES::pillarRb,TILES::pillarRb,TILES::pillarRb,TILES::pillarRc,TILES::pillarRc,TILES::pillarRc}},
        {26, {TILES::pillarBb,TILES::pillarBb,TILES::pillarBb,TILES::pillarBb,TILES::pillarBb,TILES::pillarBb,TILES::pillarBc,TILES::pillarBc,TILES::pillarBc}},
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
        {50, {TILES::plate1}},
        {51, {TILES::locker}},
        {52, {TILES::masuTile2}},
        {53, {TILES::masuTile4}},
        {54, {TILES::screen1}},
        {55, {TILES::Box8}}
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
        this->isOpen = false;
        break;
    }
    case 2:     // 退出游戏
    {
        this->isOpen = true;
        break;
    }
    case 3:
    {
        this->isOpen = true;
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
    Monster* monsterPtr = nullptr;

    switch(this->type)
    {
    case 1:
    {
        if(this->isOpen)
        {
            return;
        }
        bool flag = false;
        for(auto gameObject:this->mGame->mGameObjects){
            if(gameObject->gameObjectType == GameObject::Type::Monster){
                monsterPtr = dynamic_cast<Monster*> (gameObject);
                if(monsterPtr->mMonsterState != Monster::MonsterState::DYING)
                    flag = true;
            }
        }
        if(!flag)
            this->openDoor();
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
    if(s->gameObjectType != GameObject::Type::Player)
    {
        return;
    }
    if (this->isOpen)
    {
        switch(this->type)
        {
        case 1:
        {
            //随机选择关卡跳转
            QTimer::singleShot(100,this,[=](){
                this->mGame->mGoToNextLevel = 2;
            });
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
            QTimer::singleShot(100,this,[=](){
                this->mGame->mGoToNextLevel = 2;
            });
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
             TILES::g}},
        {6, {TILES::pftTile}}
    };

    return mapping[id];
}

std::vector<InterfaceBlock> VANITY::unlimited_block_works(short id)
{

    InterfaceBlock interface;
    std::vector<InterfaceBlock> blocks;

    interface.initializeBackGround(1);
    blocks.push_back(interface);        // 背景
    interface.initializeBar(0, QVector2D(5, 5));
    blocks.push_back(interface);        // 血条
    interface.initializeDamage(22,
                               QVector2D(-4, 19),
                               0,
                               60,
                               1000,
                               QVector2D(35, 1));
    blocks.push_back(interface);        // 虚空 vanity

    if(id == 0)
    {
        interface.initializeRock(12,
                                 QVector2D(8, 10),
                                 QVector2D(4, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 红色平台

        interface.initializeRock(23,
                                 QVector2D(13, 8),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 阶梯1

        interface.initializeRock(23,
                                 QVector2D(15, 6),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 阶梯2

        interface.initializeDamage(22,
                                   QVector2D(1, 13),
                                   0,90,3,
                                   QVector2D(2,1),
                                   0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeDamage(50,
                                   QVector2D(17, 4),
                                   0,30,-100,
                                   QVector2D(8,1),
                                   0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeLine(2,
                                 QVector2D(1, 1),
                                 1,0,2,0);
        blocks.push_back(interface);        // for

        interface.initializeLine(3,
                                 QVector2D(8, 2),
                                 1,0,2,0);
        blocks.push_back(interface);        // our

        interface.initializeLine(4,
                                 QVector2D(14, 0),
                                 1,0,2,0);
        blocks.push_back(interface);        // red

        interface.initializeLine(5,
                                 QVector2D(17, 4),
                                 1,1,2,0);
        blocks.push_back(interface);        // king

        interface.initializeRock(11,
                                 QVector2D(1, 13),
                                 QVector2D(6, 4),
                                 1,0,1,1,0);
        blocks.push_back(interface);        // 左下大平台

        interface.initializeDecoration(42,
                                       QVector2D(1, 12),
                                       0,0);
        blocks.push_back(interface);        // 地刺图像1

        interface.initializeDecoration(42,
                                       QVector2D(2, 12),
                                       0,0);
        blocks.push_back(interface);        // 地刺图像2

        interface.initializeDamage(49,
                                   QVector2D(5, 12),
                                   0, 100, 0,
                                   QVector2D(2, 1),
                                   0);
        blocks.push_back(interface);        // 桶子

        interface.initializeDoor(43,
                                 QVector2D(22, 2),
                                 1,
                                 0);
        blocks.push_back(interface);        // 门

        interface.initializeLine(1,
                                 QVector2D(0, 12),
                                 0,0,1,0);
        blocks.push_back(interface);        // quit

        interface.initializeDecoration(48,
                                       QVector2D(0, 16),
                                       0,0);
        blocks.push_back(interface);        // 梯子上沿

        interface.initializeDoor(46,
                                 QVector2D(0, 17),
                                 2,0);
        blocks.push_back(interface);        // 退出游戏

    }
    else if(id == 1)
    {
        interface.initializeRock(11,
                                 QVector2D(0, 16),
                                 QVector2D(2, 1),
                                 1,0,0,1,0);
        blocks.push_back(interface);        // 左下大平台

        interface.initializeRock(11,
                                 QVector2D(5, 17),
                                 QVector2D(5, 0),
                                 1,0,1,1,0);
        blocks.push_back(interface);        // 中下大平台

        interface.initializeRock(26,
                                 QVector2D(11, 15),
                                 QVector2D(1, 1),
                                 0,1,0,0,0);
        blocks.push_back(interface);        // 中下右柱

        interface.initializeRock(26,
                                 QVector2D(5, 14),
                                 QVector2D(1, 2),
                                 0,1,0,0,0);
        blocks.push_back(interface);        // 中下左柱

        interface.initializeRock(52,
                                 QVector2D(4, 14),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 中下左masu

        interface.initializeRock(24,
                                 QVector2D(14, 17),
                                 QVector2D(4, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 右下平台低

        interface.initializeRock(23,
                                 QVector2D(19, 16),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右下台阶1

        interface.initializeRock(23,
                                 QVector2D(20, 15),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右下台阶2

        interface.initializeRock(23,
                                 QVector2D(21, 14),
                                 QVector2D(4, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右下台阶3

        interface.initializeRock(23,
                                 QVector2D(19, 16),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右下台阶1

        interface.initializeDamage(22,
                                   QVector2D(16, 12),
                                   0,
                                   60,
                                   -10,
                                   QVector2D(4, 1),
                                   0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeRock(12,
                                 QVector2D(16, 12),
                                 QVector2D(2, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 回血平台

        interface.initializeRock(53,
                                 QVector2D(10, 10),
                                 QVector2D(5, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 中平台

        interface.initializeRock(11,
                                 QVector2D(3, 8),
                                 QVector2D(4, 0),
                                 1,1,1,1,0);
        blocks.push_back(interface);        // 中左大块

        interface.initializeRock(11,
                                 QVector2D(0, 7),
                                 QVector2D(1, 0),
                                 1,1,0,1,0);
        blocks.push_back(interface);        // 左大块

        interface.initializeRock(23,
                                 QVector2D(3, 5),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左上单点

        interface.initializeRock(23,
                                 QVector2D(4, 4),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左上台阶1

        interface.initializeRock(23,
                                 QVector2D(5, 3),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左上台阶2

        interface.initializeRock(23,
                                 QVector2D(8, 3),
                                 QVector2D(6, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 中上平台

        interface.initializeDecoration(45,
                                       QVector2D(13, 4),
                                       0,0);
        blocks.push_back(interface);        // 中上旗帜

        interface.initializeDecoration(54,
                                       QVector2D(12, 4),
                                       0,6);
        blocks.push_back(interface);        // 中上屏幕

        interface.initializeRock(23,
                                 QVector2D(15, 3),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上台阶1

        interface.initializeRock(23,
                                 QVector2D(18, 5),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上台阶2

        interface.initializeRock(23,
                                 QVector2D(20, 6),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上台阶3

        interface.initializeRock(23,
                                 QVector2D(23, 7),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上台阶2

        interface.initializeDoor(31,
                                 QVector2D(24, 6),
                                 1,0);
        blocks.push_back(interface);        // 门
    }
    else if(id == 2)
    {
        interface.initializeLine(6,
                                 QVector2D(0, 5),
                                 1,1,2,0);
        blocks.push_back(interface);        // 左上大块

        interface.initializeRock(24,
                                 QVector2D(3, 5),
                                 QVector2D(5, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 左上平台

        interface.initializeRock(25,
                                 QVector2D(5, 0),
                                 QVector2D(1, 3),
                                 1,1,0,0,0);
        blocks.push_back(interface);        // 左上柱子

        interface.initializeRock(24,
                                 QVector2D(9, 6),
                                 QVector2D(4, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 上平台

        interface.initializeLine(6,
                                 QVector2D(14, 6),
                                 1,1,1,0);
        blocks.push_back(interface);        // 上块

        interface.initializeRock(21,
                                 QVector2D(10, 2),
                                 QVector2D(3, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上masu平台

        interface.initializeRock(52,
                                 QVector2D(14, 3),
                                 QVector2D(5, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上masu2平台

        interface.initializeRock(53,
                                 QVector2D(20, 4),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上masu4平台

        interface.initializeRock(53,
                                 QVector2D(21, 5),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上masu4台阶

        interface.initializeRock(53,
                                 QVector2D(22, 6),
                                 QVector2D(3, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上masu4台阶2

        interface.initializeDoor(31,
                                 QVector2D(24, 5),
                                 1,0);
        blocks.push_back(interface);        // 门

        interface.initializeLine(6,
                                 QVector2D(0, 11),
                                 1,1,2,0);
        blocks.push_back(interface);        // 左大块

        interface.initializeLine(6,
                                 QVector2D(2, 11),
                                 1,1,2,0);
        blocks.push_back(interface);        // 左大块

        interface.initializeLine(6,
                                 QVector2D(5, 13),
                                 1,1,1,0);
        blocks.push_back(interface);        // 左下块

        interface.initializeRock(23,
                                 QVector2D(7, 13),
                                 QVector2D(4, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 下平台

        interface.initializeRock(50,
                                 QVector2D(12, 15),
                                 QVector2D(4, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 下平台2

        interface.initializeRock(23,
                                 QVector2D(17, 13),
                                 QVector2D(8, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右平台

        interface.initializeRock(49,
                                 QVector2D(22, 12),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右桶子

        interface.initializeDamage(55,
                                   QVector2D(20, 10),
                                   0,60, 5,
                                   QVector2D(1,1)
                                   ,0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeDamage(22,
                                   QVector2D(15, 9),
                                   0,60,-10,
                                   QVector2D(4, 1),
                                   0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeRock(12,
                                 QVector2D(15, 9),
                                 QVector2D(2, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 回血平台

        interface.initializeRock(49,
                                 QVector2D(15, 8),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 桶子

        interface.initializeRock(54,
                                 QVector2D(17, 10),
                                 QVector2D(1, 1),
                                 0,0,0,0,6);
        blocks.push_back(interface);        // 显示屏
    }
    else if(id == 3)
    {
        interface.initializeRock(11,
                                 QVector2D(10, 16),
                                 QVector2D(3, 1),
                                 1,0,1,1,0);
        blocks.push_back(interface);        // 下平台

        interface.initializeDecoration(51,
                                       QVector2D(10, 14),
                                       0,0);
        blocks.push_back(interface);        // 柜子

        interface.initializeRock(22,
                                 QVector2D(10, 14),
                                 QVector2D(1, 2),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 柜子

        interface.initializeDamage(45,
                                   QVector2D(10, 12)
                                   ,0,300,99,
                                   QVector2D(1, 1),
                                   0);
        blocks.push_back(interface);        // 旗子

        interface.initializeRock(11,
                                 QVector2D(16, 15),
                                 QVector2D(3, 2),
                                 1,0,1,1,0);
        blocks.push_back(interface);        // 右下

        interface.initializeRock(11,
                                 QVector2D(23, 15),
                                 QVector2D(1, 2),
                                 1,0,1,0,0);
        blocks.push_back(interface);        // 右下

        interface.initializeRock(11,
                                 QVector2D(24, 12),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右

        interface.initializeRock(11,
                                 QVector2D(20, 11),
                                 QVector2D(3, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右平台

        interface.initializeRock(11,
                                 QVector2D(15, 9),
                                 QVector2D(3, 0),
                                 1,1,1,1,0);
        blocks.push_back(interface);        // 右块

        interface.initializeRock(23,
                                 QVector2D(20, 6),
                                 QVector2D(4, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上平台

        interface.initializeRock(23,
                                 QVector2D(23, 5),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上台阶1

        interface.initializeRock(23,
                                 QVector2D(24, 4),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上台阶2

        interface.initializeRock(53,
                                 QVector2D(14, 3),
                                 QVector2D(8, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 右上平台

        interface.initializeRock(26,
                                 QVector2D(13, 2),
                                 QVector2D(1, 8),
                                 0,1,0,0,0);
        blocks.push_back(interface);        // 擎天柱

        interface.initializeRock(52,
                                 QVector2D(11, 7),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 中间平台

        interface.initializeDamage(55,
                                   QVector2D(11, 6),
                                   0,300,20,
                                   QVector2D(1, 1),0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeRock(21,
                                 QVector2D(8, 11),
                                 QVector2D(6, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 中下平台

        interface.initializeDamage(22,
                                   QVector2D(3, 15),
                                   0,60,-100,
                                   QVector2D(5, 1),
                                   0);
        blocks.push_back(interface);        // 巴列尔

        interface.initializeRock(12,
                                 QVector2D(3, 15),
                                 QVector2D(3, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 回血平台

        interface.initializeLine(6,
                                 QVector2D(0, 15),
                                 1,1,2,0);
        blocks.push_back(interface);        // 左大块

        interface.initializeRock(23,
                                 QVector2D(1, 12),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左平台

        interface.initializeRock(23,
                                 QVector2D(2, 10),
                                 QVector2D(1, 3),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左台阶

        interface.initializeRock(23,
                                 QVector2D(3, 8),
                                 QVector2D(1, 3),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左台阶

        interface.initializeRock(24,
                                 QVector2D(4, 8),
                                 QVector2D(1, 1),
                                 0,0,1,1,0);
        blocks.push_back(interface);        // 左平台

        interface.initializeRock(23,
                                 QVector2D(6, 5),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左上块

        interface.initializeRock(23,
                                 QVector2D(4, 4),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左上块

        interface.initializeRock(50,
                                 QVector2D(0, 4),
                                 QVector2D(4, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 左上平台

        interface.initializeRock(23,
                                 QVector2D(8, 2),
                                 QVector2D(1, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上块

        interface.initializeRock(26,
                                 QVector2D(8, 3),
                                 QVector2D(1, 6),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 擎天柱

        interface.initializeRock(53,
                                 QVector2D(9, 2),
                                 QVector2D(3, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上平台

        interface.initializeRock(53,
                                 QVector2D(6, 2),
                                 QVector2D(2, 1),
                                 0,0,0,0,0);
        blocks.push_back(interface);        // 上平台

        interface.initializeRock(26,
                                 QVector2D(11, 0),
                                 QVector2D(1, 1),
                                 0,1,0,0,0);
        blocks.push_back(interface);        // 左上块

        interface.initializeRock(54,
                                 QVector2D(7, 3),
                                 QVector2D(1, 1),
                                 0,0,0,0,6);
        blocks.push_back(interface);        // 显示屏

        interface.initializeDoor(31,
                                 QVector2D(9, 1),
                                 1,0);
        blocks.push_back(interface);        // 门
    }

    return blocks;
}
