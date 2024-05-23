#ifndef STANDARD_H
#define STANDARD_H
#include "animationloader.h"
//用于
//参数分配：1.绝对路径 2.图片宽 3.图片长
//4.图片帧数
namespace PLAYER{
    extern const AnimationLoader idle;
    extern const AnimationLoader walking;
    extern const AnimationLoader jumping;
    extern const int loseHPTimePeriod;
    extern const int MaxHP;
    extern const int Player_Width;
    extern const int Player_Height;
}

namespace MONSTER {
    extern const AnimationLoader idle;
    extern const AnimationLoader walking;
    extern const AnimationLoader jumping;
}

namespace BACKGROUND{
extern const AnimationLoader bg1;
}

namespace TILES{
extern const AnimationLoader industrialTile1;
extern const AnimationLoader industrialTile2;
extern const AnimationLoader industrialTile3;
extern const AnimationLoader industrialTile4;
extern const AnimationLoader industrialTile5;
extern const AnimationLoader industrialTile6;
extern const AnimationLoader industrialTile7;
extern const AnimationLoader industrialTile8;
extern const AnimationLoader industrialTile9;
extern const AnimationLoader masuTile;
extern const AnimationLoader door1;
}


namespace DRAWORRDER{
//值从低到高，绘制从下往上
extern const int backGround;//背景
extern const int ground;//地面
extern const int door;//游戏结束的门
extern const int platForm;//平台
extern const int item;//物品，如钱、武器
extern const int Monster;//敌人
extern const int Player;//玩家
extern const int QTE;//即时战斗模式
extern const int specialEffect;//特效

}

namespace SYSTEM{
    extern const int fpsNormal;
    extern const int fpsExciting;
    extern const int fpsBreathtaking;
    //fps
    extern const int windowWidth;
    extern const int windowHeight;
    extern const int tileSide;
}
namespace ACTIONCONST{
extern const float maxSpeed;
extern const float gravityAcceleration ;
extern const float playerMoveXSpeed;
extern const float playerMoveYSpeed;
extern const float monsterMoveXSpeed;
extern const float monsterMoveYSpeed;
extern const float jump_gravityAcceleration;
extern const int monsterIdleFrame;

}





#endif // STANDARD_H
