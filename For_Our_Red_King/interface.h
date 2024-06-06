#ifndef INTERFACE_H
#define INTERFACE_H
class Player;
class Monster;
#include "blocks.h"
struct InterfacePlayer
{
    float x = 0,y = 0;    //坐标
    int HP = 100;         //存档时的血量
    InterfacePlayer();
    void interfaceInitialization(Player* playerP);
};

struct InterfaceMonster
{
    float x = 50,y = 50;    //坐标
    int HP = 100;         //存档时的血量
    int type = 1;       //怪物类型
    int ATK = 30;       //攻击力
    InterfaceMonster();

    void interfaceInitialization(Monster *MonsterP);
};
class Interface
{
public:
    Interface();

     InterfacePlayer playerinterface;
     InterfaceMonster monsterinterface;

     int Monstersize = 0;
     InterfaceMonster monsterinterfacearray[20];                //monsterinterface数组

     int BlockSize = 0;
     InterfaceBlock blockInterfaceArray[100];



};

struct GameStatisticInterface
{
    int maxCombos = 0;    //最高不扣血连击数
    int alreadyKillMonsterNumber = 0;//已经击杀了几只怪物
    int maxPassLevelNumber = 0;   //最高一次性通过多少关
    GameStatisticInterface():maxCombos(0),alreadyKillMonsterNumber(0),maxPassLevelNumber(0){};
};

#endif // INTERFACE_H
