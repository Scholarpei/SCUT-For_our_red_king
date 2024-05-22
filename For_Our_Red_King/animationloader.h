#ifndef ANIMATIONLOADER_H
#define ANIMATIONLOADER_H
#include<QString>
class AnimationLoader
{
public:
    AnimationLoader(QString pixaddresss,int pixx,int pixy,int pixframe);
    AnimationLoader();
    QString GetpixAddress() const;
    int GetpixX() const;
    int GetpixY() const;
    int GetpixFrame() const;
private:
    QString pixAddress;
    int pixX;
    int pixY;
    int drawOrder;
    int pixFrame;
};

#endif // ANIMATIONLOADER_H
