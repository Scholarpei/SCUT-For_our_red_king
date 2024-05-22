#include "standard.h"
namespace PLAYER{
const AnimationLoader idle= AnimationLoader(":/pictureResoource/Player/idle.png",
                                       192,48,4);
const AnimationLoader walking = AnimationLoader(":/pictureResoource/Player/Run.png",
                                          288,48,6);
const AnimationLoader jumping = AnimationLoader("://pictureResoource/Player/jump.png",
                                          192,48,4);

}

namespace MONSTER {


}

namespace DOOR{

}

namespace TILES{
const AnimationLoader industrialTile1(":/pictureResoource/Tiles/IndustrialTile_1",
                                32, 32, 1);
const AnimationLoader industrialTile2(":/pictureResoource/Tiles/IndustrialTile_2",
                                32, 32, 1);
const AnimationLoader industrialTile3(":/pictureResoource/Tiles/IndustrialTile_3",
                                32, 32, 1);
const AnimationLoader industrialTile4(":/pictureResoource/Tiles/IndustrialTile_4",
                                32, 32, 1);
const AnimationLoader industrialTile5(":/pictureResoource/Tiles/IndustrialTile_5",
                                32, 32, 1);
const AnimationLoader industrialTile6(":/pictureResoource/Tiles/IndustrialTile_6",
                                32, 32, 1);
const AnimationLoader industrialTile7(":/pictureResoource/Tiles/IndustrialTile_7",
                                32, 32, 1);
const AnimationLoader industrialTile8(":/pictureResoource/Tiles/IndustrialTile_8",
                                32, 32, 1);
const AnimationLoader industrialTile9(":/pictureResoource/Tiles/IndustrialTile_9",
                                32, 32, 1);

const AnimationLoader masuTile(":/pictureResoource/Tiles/masuTile",
                         32, 32, 1);
}

namespace DRAWORRDER{
//值从低到高，绘制从下往上
const int backGround = 1;//背景
const int ground = 8;//地面
const int door = 40;//游戏结束的门
const int platForm = 42;//平台
const int item = 72;//物品，如钱、武器
const int Monster = 90;//敌人
const int Player = 110;//玩家
const int   QTE = 120;//即时战斗模式
const int specialEffect = 135;//特效

}

namespace SYSTEM{
const int fpsNormal = 60;
const int fpsExciting = 90;
const int fpsBreathtaking = 120;
//fps
const int windowWidth = 960;
const int windowHeight = 576;
}
namespace ACTIONCONST{
const float maxSpeed = 15;
const float gravityAcceleration = -9.8;
const float playerMoveXSpeed = 1;
const float playerMoveYSpeed = 1;

}
