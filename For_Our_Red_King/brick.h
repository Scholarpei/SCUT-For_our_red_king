#ifndef BRICK_H
#define BRICK_H

#include "animationComponent.h"
#include "gameobject.h"

class Brick: public GameObject
{
private:
    QVector2D gridPosition;
    QVector2D gridSize;
    AnimationComponent* animation;

public:
    const static int SIDE = 48;

public:
    explicit Brick(QObject *parent = nullptr,class Game* game = nullptr, int drawOrder = 0);
    // virtual ~Brick();

    //初始化砖块，传入信息
    void initialize(const AnimationLoader& anime, QVector2D posi, QVector2D size);

    // void update();
    // void vanish();

    int getX();
    int getY();
    int getWidth();
    int getHeight();



};





#endif // BRICK_H
