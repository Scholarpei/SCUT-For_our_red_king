#include "standard.h"
namespace PLAYER{
const AnimationLoader idle= AnimationLoader(":/pictureResoource/Player/idle.png",
                                       48,48,4);
const AnimationLoader walking = AnimationLoader(":/pictureResoource/Player/Run.png",
                                          48,48,6);
const AnimationLoader jumping = AnimationLoader(":/pictureResoource/Player/jump.png",
                                          48,48,4);
const int loseHPTimePeriod = 30;
const int MaxHP = 100;
const int Player_Width = 48;
const int Player_Height = 60;

const QString walkSoundURL = ":/sound/player/soundPlayerWalking.wav";
const QString jumpSoundURL = ":/sound/player/soundPlayerJumping.wav";
}

namespace MONSTER {
const AnimationLoader idle= AnimationLoader(":/pictureResoource/Monster/Idle.png",
                                             48,48,4);
const AnimationLoader walking = AnimationLoader(":/pictureResoource/Monster/Walk.png",
                                                48,48,6);
const AnimationLoader fighting = AnimationLoader(":/pictureResoource/Monster/attack.png",
                                                48,48,8);
const int MaxHP = 60;
const int loseHPTimePeriod = 15;
const int Monster_Width = 48;
const int Monster_Height = 60;
}

namespace BACKGROUND{
const AnimationLoader bg1(":/pictureResoource/background/Background.png",
                          576, 324, 1);
const AnimationLoader blood(":/pictureResoource/background/blood.png",
                          232, 15, 1);
const AnimationLoader plate(":/pictureResoource/background/plate.png",
                          240, 24, 1);
const AnimationLoader shocked_plate(":/pictureResoource/background/shocked_plate.png",
                            240, 24, 1);
const AnimationLoader hurting(":/pictureResoource/background/hurting.png",
                            232, 15, 1);
const AnimationLoader healing(":/pictureResoource/background/healing.png",
                            232, 15, 1);
}

namespace TILES{
const AnimationLoader industrialTile1(":/pictureResoource/Tiles/IndustrialTile_1.png",
                                32, 32, 1);
const AnimationLoader industrialTile2(":/pictureResoource/Tiles/IndustrialTile_2.png",
                                32, 32, 1);
const AnimationLoader industrialTile3(":/pictureResoource/Tiles/IndustrialTile_3.png",
                                32, 32, 1);
const AnimationLoader industrialTile4(":/pictureResoource/Tiles/IndustrialTile_4.png",
                                32, 32, 1);
const AnimationLoader industrialTile5(":/pictureResoource/Tiles/IndustrialTile_5.png",
                                32, 32, 1);
const AnimationLoader industrialTile6(":/pictureResoource/Tiles/IndustrialTile_6.png",
                                32, 32, 1);
const AnimationLoader industrialTile7(":/pictureResoource/Tiles/IndustrialTile_7.png",
                                32, 32, 1);
const AnimationLoader industrialTile8(":/pictureResoource/Tiles/IndustrialTile_8.png",
                                32, 32, 1);
const AnimationLoader industrialTile9(":/pictureResoource/Tiles/IndustrialTile_9.png",
                                32, 32, 1);
const AnimationLoader masuTile(":/pictureResoource/Tiles/masuTile.png",
                         32, 32, 1);
const AnimationLoader door1(":/pictureResoource/Tiles/door.png",
                            32, 32, 8);
const AnimationLoader money(":/pictureResoource/Tiles/Money.png",
                            24, 24, 6);
const AnimationLoader screen2(":/pictureResoource/Tiles/Screen2.png",
                              32, 42, 4);
const AnimationLoader bench(":/pictureResoource/Tiles/Bench.png",
                              32, 32, 1);
const AnimationLoader air(":/pictureResoource/Tiles/Bench.png",
                          4, 4, 1);
const AnimationLoader flag(":/pictureResoource/Tiles/Flag.png",
                          32, 64, 1);
const AnimationLoader ladder1(":/pictureResoource/Tiles/Ladder1.png",
                              32, 32, 1);
const AnimationLoader ladder2(":/pictureResoource/Tiles/Ladder2.png",
                              32, 32, 1);
const AnimationLoader ladder3(":/pictureResoource/Tiles/Ladder3.png",
                           32, 32, 1);
const AnimationLoader q(":/pictureResoource/Tiles/q.png",
                              16, 16, 1);
const AnimationLoader u(":/pictureResoource/Tiles/u.png",
                        16, 16, 1);
const AnimationLoader i(":/pictureResoource/Tiles/i.png",
                        16, 16, 1);
const AnimationLoader t(":/pictureResoource/Tiles/t.png",
                        16, 16, 1);
const AnimationLoader redP1(":/pictureResoource/Tiles/redP1.png",
                        32, 32, 1);
const AnimationLoader redP2(":/pictureResoource/Tiles/redP2.png",
                            32, 32, 1);
const AnimationLoader redP3(":/pictureResoource/Tiles/redP3.png",
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
const int tileSide = 48;
const int imgSide = 32;
const int durationPerFrame = 6;

const QString bgmURL = ":/sound/system/bgm.wav";
const QString icon=":/pictureResoource/icon.ico";
}
namespace ACTIONCONST{
const float maxSpeed = 5;
const float gravityAcceleration = 0.5;
const float jump_gravityAcceleration = 0.1;
const float playerMoveXSpeed = 5;
const float playerMoveYSpeed = -5;
const float monsterMoveXSpeed = 1;
const float monsterMoveYSpeed = 1;
const int monsterIdleFrame = 90;


}
namespace QTE{
const QString PointPicture=":/pictureResoource/QTE/QTE_Point.png";
const QString PlatePicture=":/pictureResoource/QTE/QTE_Plate.png";
const int qteWidth=32*12;
const int qteHeight=32*12;
const QVector2D centralPosition(SYSTEM::windowWidth/2,SYSTEM::windowHeight/2);
const int addAngle=5;
const int DELTAANGLE = 15;
const int BEGINANGLE=0;
const int ROUNDENDANGLE=290;

const QString REDPART=":/pictureResoource/QTE/QTE_red.png";
const QString BLUEPART=":/pictureResoource/QTE/QTE_blue.png";
const QString ORANGEPART=":/pictureResoource/QTE/QTE_orange.png";
const int TIMEWIDTH = 1;
const float leastQTEDistance = 200;

}
