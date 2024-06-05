#include "interface.h"
#include"player.h"
#include"monster.h"
Interface::Interface() {


}



InterfacePlayer::InterfacePlayer(){
        //空的构造函数
}

void InterfacePlayer::interfaceInitialization(Player* playerP){
        this->x = playerP->getPosition().x();
        this->y = playerP->getPosition().y();
        this->HP = playerP->getHP();
}


InterfaceMonster::InterfaceMonster(){
        //空的构造函数
}

void InterfaceMonster::interfaceInitialization(Monster *MonsterP){
        this->x = MonsterP->getPosition().x();
        this->y = MonsterP->getPosition().y();
        this->HP = MonsterP->getHP();
        this->type = MonsterP->getMonsterType();      //1为Batman，2为Biker，3为Cyborg，4为Robot

}
