#ifndef INTERFACE_H
#define INTERFACE_H
class Player;
class Monster;
#include "blocks.h"
struct InterfacePlayer
{
    float x,y;    //坐标
    int HP;         //存档时的血量
    InterfacePlayer();
    void interfaceInitialization(Player* playerP);
};

struct InterfaceMonster
{
    float x,y;    //坐标
    int HP;         //存档时的血量
    int type;       //怪物类型
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

#endif // INTERFACE_H
