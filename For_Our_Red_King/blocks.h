#ifndef BLOCKS_H
#define BLOCKS_H

#include "brick.h"
#include "bleedingcomponent.h"

class Block;

struct InterfaceBlock
{
    short category = -1;
    short position[4] = {0, 0, 0, 0};
    short textureID = 0;
    short status[5] = {0, 0, 0, 0, 0};
    short durationPerFrame = 0;    // durationPerFrame以及函数传入的该参数都是表示该砖块是否有动画的，如果是就从一开始直接播放。 数值代表每几刻换下一个帧， 0代表没有动画

    static std::vector<AnimationLoader> toAnime(short ID);

    void initializeRock(short textureID, QVector2D posi, QVector2D inSize, bool up, bool down, bool left, bool right, short durationPerFrame = 0);
    void initializeBackGround(short textureID, short durationPerFrame = 0);
    void initializeDoor(short texturID, QVector2D posi, short type, short durationPerFrame = 0);
    void initializeDecoration(short texturID, QVector2D posi, short type, short durationPerFrame = 0);
    void initializeBar(short textureID, QVector2D posi);
    void initializeDamage(short texturID, QVector2D posi, short type,short interval, short damage, QVector2D size ,short durationPerFrame = 0);
    void initializeLine(short id, QVector2D posi, bool isHorizontal, bool attendCollision, short scale, short dpf = 0);

    Block* cateToPointer(int cate, Game* game);
    void createBlock(Game* game);
};


class Block: public GameObject
{
protected:
    QVector2D gridPosition;
    QVector2D gridSize;
    std::vector<std::vector<Brick*>> bricks;

public:
    explicit Block(QObject *parent = nullptr,class Game* game = nullptr);

    // void initialize();
    virtual void initialize(const InterfaceBlock& interface) = 0;

    virtual void Update();
    // void vanish();

    int getX();
    int getY();
    int getWidth();
    int getHeight();

    virtual void beingCollide(GameObject* s);

};


namespace RockSpawner
{

class RockSpawner
{
private:
    bool up;
    bool down;
    bool left;
    bool right;
    int inWidth;
    int inHeight;

    std::array<AnimationLoader, 9> bricks;
public:
    short durationPerFrame;
private:

    void fromID(short id);

public:
    RockSpawner(short ID, bool up, bool down, bool left, bool right, int inWidth, int inHeight, short durationPerFrame);

    int getWidth();
    int getHeight();
    AnimationLoader getAnime(int x, int y);

};

};



class BlockRock : public Block
{
public:
    explicit BlockRock(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(RockSpawner::RockSpawner spawner, QVector2D posi);
    virtual void initialize(const InterfaceBlock& interface);
    virtual void Update();
};

class BlockDecoration : public Block
{
private:
    short type;

public:
    explicit BlockDecoration(QObject *parent = nullptr,class Game* game = nullptr);

    void initiialize(const AnimationLoader& anime, QVector2D posi, short type, short dpf);
    virtual void initialize(const InterfaceBlock& interface);

};


class BlockBack : public Block
{
public:
    explicit BlockBack(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(const AnimationLoader& anime, short dpf);
    virtual void initialize(const InterfaceBlock& interface);
};

class BlockDoor : public Block
{
private:
    bool isOpen = false;
    short type;

    void openDoor();

public:
    explicit BlockDoor(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(const AnimationLoader& anime, QVector2D posi, short type, short dpf);
    virtual void initialize(const InterfaceBlock& interface);
    virtual void Update();
    virtual void beingCollide(GameObject* s);
};

class BlockDamage : public Block
{
protected:
    int damage;
    int HURT_INTERVAL;      // 单位是tick

    int current_tick;

public:
    explicit BlockDamage(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(const AnimationLoader& anime, QVector2D posi, short type, short dpf, short interval, short damage, QVector2D size);
    virtual void initialize(const InterfaceBlock& interface);
    virtual void Update();
    virtual void beingCollide(GameObject* s);
};


class BlockBar : public Block
{
public:
    explicit BlockBar(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(BleedingComponent* bar, int posX, int posY);
    virtual void initialize(const InterfaceBlock& interface);

    virtual void Update();

protected:
    BleedingComponent* HPbar;

    int hp = PLAYER::MaxHP;
};

class BlockLine : public Block
{
public:
    explicit BlockLine(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(short id, QVector2D posi, bool isHorizontal, bool attendCollision, short dpf, short scale=1);
    virtual void initialize(const InterfaceBlock& interface);

    std::vector<AnimationLoader> getAnime(short id);
};




namespace VANITY{

std::vector<InterfaceBlock> unlimited_block_works(short id);
}

#endif // BLOCKS_H
