#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include "gameobject.h"
#include "animationComponent.h"
#include "animationloader.h"

class SpriteObject : public GameObject
{
public:
    explicit SpriteObject(QObject *parent = nullptr, Game *game = nullptr,int draworder=200);
    virtual ~SpriteObject();
    void setDirection(int dir);
    void setPosition(int x,int y);
    void setOpacity(double opa);
    void setNeedDraw(bool needOrNot);
    void setWidth(int width);
    void setHeight(int height);
    void reload();
    virtual int getDrawDirection()override;
    void playOrstop(bool isPlay);

protected:
    AnimationComponent* sprite;
    int direction;
    int drawPosX;
    int drawPosY;
    int realPosX;
    int realPosY;
    //width height
    double opacity;
    bool needDraw;



};

#endif // SPRITEOBJECT_H
