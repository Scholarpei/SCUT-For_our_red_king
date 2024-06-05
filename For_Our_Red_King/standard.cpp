#include "standard.h"
namespace PLAYER{
const AnimationLoader idle= AnimationLoader(":/pictureResoource/Player/idle.png",
                                       48,48,4);
const AnimationLoader walking = AnimationLoader(":/pictureResoource/Player/Run.png",
                                          48,48,6);
const AnimationLoader jumping = AnimationLoader(":/pictureResoource/Player/jump.png",
                                          48,48,4);
const AnimationLoader dead = AnimationLoader(":/pictureResoource/Player/death.png",
                                             48,48,6);
const AnimationLoader attack = AnimationLoader(":/pictureResoource/Player/attack3.png",48,48,8);
const int loseHPTimePeriod = 30;
const int MaxHP = 100;
const int Player_Width = 48;
const int Player_Height = 60;
const int PlayerTeleportationTime = 20;   //Player缓慢移动到瞬移的帧数
const float PlayerTeleportationMovingProportion = 0.3;  //player从移动到瞬移要走的距离比例

const QString walkSoundURL = ":/sound/player/soundPlayerWalking.wav";
const QString jumpSoundURL = ":/sound/player/soundPlayerJumping.wav";
}

namespace MONSTER {
const AnimationLoader Bikeridle = AnimationLoader(":/pictureResoource/Monster/Biker/Idle.png",48,48,4);
const AnimationLoader Bikerwalking = AnimationLoader(":/pictureResoource/Monster/Biker/Walk.png",48,48,6);
const AnimationLoader Bikerfighting = AnimationLoader(":/pictureResoource/Monster/Biker/attack.png",48,48,8);
const AnimationLoader Bikerdead = AnimationLoader(":/pictureResoource/Monster/Biker/death.png",48,48,6);

const AnimationLoader Batmanidle = AnimationLoader(":/pictureResoource/Monster/Batman/idle.png",48,48,4);
const AnimationLoader Batmanwalking = AnimationLoader(":/pictureResoource/Monster/Batman/Walk.png",48,48,6);
const AnimationLoader Batmanfighting = AnimationLoader(":/pictureResoource/Monster/Batman/Attack.png",48,48,6);
const AnimationLoader Batmandead = AnimationLoader(":/pictureResoource/Monster/Batman/Death.png",48,48,6);

const AnimationLoader Cyborgidle = AnimationLoader(":/pictureResoource/Monster/Cyborg/idle.png",48,48,4);
const AnimationLoader Cyborgwalking = AnimationLoader(":/pictureResoource/Monster/Cyborg/run.png",48,48,6);
const AnimationLoader Cyborgfighting = AnimationLoader(":/pictureResoource/Monster/Cyborg/attack.png",48,48,8);
const AnimationLoader Cyborgdead = AnimationLoader(":/pictureResoource/Monster/Cyborg/death.png",48,48,6);

const AnimationLoader Robotidle = AnimationLoader(":/pictureResoource/Monster/Robot/Idle.png",48,48,4);
const AnimationLoader Robotwalking = AnimationLoader(":/pictureResoource/Monster/Robot/Walk.png",48,48,6);
const AnimationLoader Robotfighting = AnimationLoader(":/pictureResoource/Monster/Robot/Attack.png",48,48,6);
const AnimationLoader Robotdead = AnimationLoader(":/pictureResoource/Monster/Robot/Death.png",48,48,6);

const AnimationLoader exclamation = AnimationLoader(":/pictureResoource/QTE/exclamation.png",
                                                    256,226,3);
const int MaxHP = 60;
const int loseHPTimePeriod = 15;
const int Monster_Width = 48;
const int Monster_Height = 60;

const float exclamationXOffset = 7;//感叹号相比于monster的x上的偏移量
const float exclamationYOffset = -10;//感叹号相比于monster的y上的偏移量
const int ExclamationWidth = 32;
const int ExclamationHeight = 32;

const QString monsterBeingDestroyedURL = QString(":/sound/monster/monsterBeingDestroyed.wav");
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
const AnimationLoader pftTile(":/pictureResoource/Tiles/pftTile.png",
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
const AnimationLoader plate1(":/pictureResoource/Tiles/plate1.png",
                             32, 32, 1);
const AnimationLoader barrel(":/pictureResoource/Tiles/Barrel1-export.png",
                           18, 26, 1);
const AnimationLoader broken(":/pictureResoource/Tiles/broken.png",
                             18, 26, 1);
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
const AnimationLoader f(":/pictureResoource/Tiles/f.png",
                        16, 16, 1);
const AnimationLoader o(":/pictureResoource/Tiles/o.png",
                        16, 16, 1);
const AnimationLoader r(":/pictureResoource/Tiles/r.png",
                        16, 16, 1);
const AnimationLoader e(":/pictureResoource/Tiles/e.png",
                        16, 16, 1);
const AnimationLoader d(":/pictureResoource/Tiles/d.png",
                        16, 16, 1);
const AnimationLoader k(":/pictureResoource/Tiles/k.png",
                        16, 16, 1);
const AnimationLoader n(":/pictureResoource/Tiles/n.png",
                        16, 16, 1);
const AnimationLoader g(":/pictureResoource/Tiles/g.png",
                        16, 16, 1);
}

namespace DRAWORRDER{
//值从低到高，绘制从下往上
const int backGround = 1;//背景
const int backGroundfilter = 125;//背景滤镜（这个数值取决于你想不想要让其他Object染上滤镜效果）
const int backGroundTile = 5;//背景砖块
const int ground = 8;//地面
const int door = 40;//游戏结束的门
const int platForm = 42;//平台
const int item = 72;//物品，如钱、武器
const int Monster = 90;//敌人
const int Player = 110;//玩家
const int   QTE = 120;//即时战斗模式
const int specialEffect = 135;//特效
const int Exclamation = 80;//敌人上的感叹号
const int Button=120;//按钮 如停止按钮
}

namespace SYSTEM{
const int fpsNormal = 60;
const int fpsExciting = 90;
const int fpsBreathtaking = 120;
//fps
const int windowWidth = 1200;
const int windowHeight = 864;
const int tileSide = 48;
const int imgSide = 32;
const int durationPerFrame = 6;

const QString bgmURL = ":/sound/system/bgm.wav";
const QString icon=":/pictureResoource/icon.ico";
}

namespace FILTER {
const AnimationLoader ExitGameFilter(":/pictureResoource/background/exitGameFilter.jpg",1920,1280,10);
}

namespace ACTIONCONST{
const float maxSpeed = 10;
const float gravityAcceleration = 2.0;
const float jump_gravityAcceleration = 0.3;
const float playerMoveXSpeed = 10;
const float playerMoveYSpeed = -9;
const float monsterMoveXSpeed = 3;
const float monsterMoveYSpeed = 3;
const int monsterIdleFrame = 90;


}
namespace QTE{
const QString PointPicture=":/pictureResoource/QTE/QTE_Point.png";
const QString PlatePicture=":/pictureResoource/QTE/QTE_Plate.png";
const int qteWidth=32*12;
const int qteHeight=32*12;
const QVector2D centralPosition(SYSTEM::windowWidth/2,SYSTEM::windowHeight/2);
const int addAngle=7;
const int DELTAANGLE = 15;
const int BEGINANGLE=0;
const int ROUNDENDANGLE=290;

const QString REDPART=":/pictureResoource/QTE/QTE_red.png";
const QString BLUEPART=":/pictureResoource/QTE/QTE_blue.png";
const QString ORANGEPART=":/pictureResoource/QTE/QTE_orange.png";
const int TIMEWIDTH = 1;
const float leastQTEDistance = 200;
const float leastQTEAppendDistance = leastQTEDistance * 8;  //追击时的最小可自动qte距离
const int QteWinWaitingTime = SYSTEM::fpsNormal;   //qte结束后等待的动画时间

const QString firstStartQTEURL = QString(":/sound/qte/firstStartQTE.wav");   //开启qte的音效
const QString qteHit1URL= QString(":/sound/qte/hit1.wav");         //击打1音效
const QString qteHit2URL= QString(":/sound/qte/hit2.wav");         //击打2音效
const QString qteHit3URL= QString(":/sound/qte/hit3.wav");         //击打3音效
const QString qteContinueURL= QString(":/sound/qte/QTEContinue.wav");     //qte中播放鼓点音乐
const QString qteMissURL = QString(":/sound/qte/miss.wav");         //击打打空miss

}
namespace BUTTONS{
const int ButtonWIDTH=32;
const int ButtonHEIGHT=32;

const QVector2D stopButtonPOS(SYSTEM::windowWidth-32,32);
const QString stopButtonTYPE1=":/pictureResoource/button/stopbutton_type1.png";
const QString stopButtonTYPE2=":/pictureResoource/button/stopbutton_type2.png";
const QString stopButtonTYPE3=":/pictureResoource/button/stopbutton_type3.png";
const QString stopButtonTYPE4=":/pictureResoource/button/stopbutton_type4.png";

const QVector2D returnMainButtonPOS(SYSTEM::windowWidth-64,32);
const QString returnMainButtonTYPE1=":/pictureResoource/button/returnmainbutton_type1.png";
const QString returnMainButtonTYPE2=":/pictureResoource/button/returnmainbutton_type2.png";
}
