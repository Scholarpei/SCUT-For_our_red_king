#include "animationloader.h"

AnimationLoader::AnimationLoader(QString pixaddresss,int pixx,int pixy,int pixframe) {
    pixAddress = pixaddresss;
    pixX = pixx;
    pixY = pixy;
    pixFrame = pixframe;
}

AnimationLoader::AnimationLoader() {
    pixAddress = "";
    pixX = 0;
    pixY = 0;
    pixFrame = 0;
    //默认空的构造函数
}

QString AnimationLoader::GetpixAddress() const {
    return this->pixAddress;
}

int AnimationLoader::GetpixX() const {
    return this->pixX;
}

int AnimationLoader::GetpixY() const {
    return this->pixY;
}



int AnimationLoader::GetpixFrame() const {
    return this->pixFrame;
}
