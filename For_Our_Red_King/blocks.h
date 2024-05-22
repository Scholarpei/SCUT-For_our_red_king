#ifndef BLOCKS_H
#define BLOCKS_H

#include "brick.h"

struct InterfaceBlock
{
    short category = -1;
    short position[4] = {0, 0, 0, 0};
    short textureID = 0;
    short status[5] = {0, 0, 0, 0, 0};

    static std::vector<AnimationLoader> toAnime(short ID);

    void initializeRock(short textureID, QVector2D posi, QVector2D inSize, bool up, bool down, bool left, bool right);
    void initializeBackGround(short textureID);
    void initializeDoor(short texturID, QVector2D posi, short type);
};


class Block: public GameObject
{
protected:
    QVector2D gridPosition;
    QVector2D gridSize;
    std::vector<std::vector<Brick*>> bricks;

public:
    explicit Block(QObject *parent = nullptr,class Game* game = nullptr);
    virtual ~Block();

    // void initialize();
    virtual void initialize(const InterfaceBlock& interface) = 0;

    virtual void update() = 0;
    // void vanish();

    int getX();
    int getY();
    int getWidth();
    int getHeight();

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

private:

    void fromID(short id);

public:
    RockSpawner(short ID, bool up, bool down, bool left, bool right, int inWidth, int inHeight);

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
    virtual void update();
};


class BlockBack : public Block
{
public:
    explicit BlockBack(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(const AnimationLoader& anime);
    virtual void initialize(const InterfaceBlock& interface);
    virtual void update();
};

class BlockDoor : public Block
{
private:
    bool isOpen;
    short type;

    void openDoor();

public:
    explicit BlockDoor(QObject *parent = nullptr,class Game* game = nullptr);

    void initialize(const AnimationLoader& anime, QVector2D posi, short type);
    virtual void initialize(const InterfaceBlock& interface);
    virtual void update();
};


#endif // BLOCKS_H
