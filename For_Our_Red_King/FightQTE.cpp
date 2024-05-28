#include "FightQTE.h"
#include <qdebug.h>
#include <standard.h>
#include <cmath>
void FightQTE::initial()
{
    //!<��ʼ��hit type
    for(int i=0;i<4;i++)
        hit_type.at(i)=rand()%2;
    TargetAngle=rand()%4*90;
    //!< ���ô�С:
    this->mHeight=QTE::qteHeight;
    this->mWidth=QTE::qteWidth;
    //!< ��������:
    this->setPosition(QTE::centralPosition);
    //! <���ò�������ײ��
    attendCollision=1;
	//!< ��centralfunction�ӵ�timercomponent
    timer = new TimerComponent(this,this);
    timer->startRun();
    sprite_Plate=new spriteComponent(this,DRAWORRDER::QTE);
    sprite_Point=new rotationComponent(this,DRAWORRDER::QTE);
    //!< ����ͼ��: ���ｫ����ͼƬ��С������һ���� �ȽϷ��㡣
    sprite_Point->SetTexture(QTE::PointPicture);
    sprite_Plate->SetTexture(QTE::PlatePicture);
}
FightQTE::~FightQTE(){
    delete sprite_Plate;
    delete sprite_Point;

}
FightQTE::FightQTE(QObject *parent,Game* game):
    GameObject(parent,game),round(0),angle(QTE::BEGINANGLE)
{
    initial();
}

void FightQTE::Update(){

    if(mState == State::EDead)
        return;
    //����궨Ϊ�����Ͳ��ٸ�����

    for(auto component:mComponents){
        component->Update();
    }
    //��������������


}

void FightQTE::inputKeyPressProcess(int key)
{
//    qDebug()<<"input key event "<<key;
//    qDebug()<<"now angle"<<angle;
//    qDebug()<<"now round"<<round;
    if(!state_INHIT){
    state_INHIT=1;
	if (round == 2)
	{
        round2Judge(key);
    }
    if(round==3)
    {
        round3Judge(key);
    }
    state_INHIT=0;
    }
}

void FightQTE::centralFunction()
{

    rotation(QTE::addAngle);
	if (round == 1)
	{
        if (angle%90==0)
        {
            //!<change color
            //!<sound
            //!<draw->change
        }
	}
    if(round==2)
    {  
        if (angle%90==QTE::DELTAANGLE)
        {
            // qDebug()<<"judge 2";
            if(!isHit)
            {
                cnt++;
                //!< Lose û����
            }else
                isHit=0;
        }
    }
    if(round==3)
    {
        if (angle-TargetAngle==QTE::DELTAANGLE)
        {
            if(!isHit)
            {
                //!< Lose նɱδ����
//                qDebug()<<"lose";
            }else
                isHit=0;
        }
    }
}

void FightQTE::rotation(int addAngle)
{
    angle = angle + addAngle;
    if (angle >= 360)
    {
        angle -= 360;
    }
    if(angle==300)
    {
        round++;
        cnt=0;
        isHit=0;
    }
    sprite_Point->setAngle(drawAngle(angle));
}

inline int FightQTE::changeKeyToNumber(int key)
{
	int number;
    if (key == 'A')number = 0;
    else if (key == 'D')number = 1;
	return number;
}

inline int FightQTE::drawAngle(int angle)
{
    return angle-135;
}

void FightQTE::round2Judge(int key){
    bool flag=1;
    int number = changeKeyToNumber(key);
    if(isHit||number!=hit_type.at(cnt))
    {
         qDebug()<<number;
         qDebug()<<hit_type.at(cnt);
         qDebug()<<isHit;
        //!< lose �ظ�hit||HIT���Ͳ���
        flag=0;
            //qDebug()<<"lose 1";
    }

    if(flag){
        int nowAngle=angle;
        int currentPoint = cnt*90;
        int deltaAngle = std::abs(nowAngle-currentPoint);
        if(deltaAngle>=180)deltaAngle=360-deltaAngle;//! ����0�����
        // qDebug()<<"deltaAngle"<<deltaAngle;
        // qDebug()<<"currentPoint"<<currentPoint;
        // qDebug()<<"nowAngle"<<nowAngle;
        // qDebug()<<"isHIt"<<isHit;
        if (deltaAngle <= QTE::DELTAANGLE)
        {
            cnt++;
            isHit=1;
            //!<correct
            //! <sound
            //! <animation
            //qDebug()<<"hit correct";
        }
    }
}
void FightQTE::round3Judge(int key)
{
    bool flag=1;
    int number = changeKeyToNumber(key);
    if(isHit)
    {
        //!< lose �ظ�hit
        cnt--;
        flag=0;
        //qDebug()<<"lose 1";
    }
    if(flag){

        int nowAngle=angle;
        int deltaAngle = std::abs(nowAngle-TargetAngle);
        if(deltaAngle>=180)deltaAngle=360-deltaAngle;//! ����0�����
        //qDebug()<<"deltaAngle"<<deltaAngle;
        //qDebug()<<"currentPoint"<<currentPoint;
        //qDebug()<<"nowAngle"<<nowAngle;
        if (deltaAngle <= QTE::DELTAANGLE)
        {
            isHit=1;
            //!<correct
            //! <sound
            //! <animation
            //qDebug()<<"hit correct";
        }
    }
}

void FightQTE::startQTE(){
    //Ŀǰ��û���ϡ�
        state_INHIT=0;
        rotation(-angle);
        round=1;
        timer->startRun();
}
