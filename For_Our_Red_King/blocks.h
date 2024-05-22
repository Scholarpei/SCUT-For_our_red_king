#ifndef BLOCKS_H
#define BLOCKS_H

#include "brick.h"

struct InterfaceBlock
{
    short category;
    short position[4];
    short textureID;
    short status[5];

    void initializeRock(short textureID, QVector2D size, QVector2D inSize, bool up, bool down, bool left, bool right);
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

    virtual void update();
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


public:
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
    void initialize(RockSpawner::RockSpawner spawner, QVector2D posi);
    virtual void initialize(const InterfaceBlock& interface);
};


#endif // BLOCKS_H
