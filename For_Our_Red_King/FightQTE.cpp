#include "FightQTE.h"
#include <qdebug.h>
#include <standard.h>
#include <cmath>
void FightQTE::initial()
{
    //!< 初始化hit type
    state_INHIT = 0;
    //!< 设置大小:
    this->mHeight = QTE::qteHeight;
    this->mWidth = QTE::qteWidth;
    //!< 设置坐标:
    this->setPosition(QTE::centralPosition);
    //! <设置不参与碰撞：
    attendCollision = 0;
    //!< 把centralfunction加到timercomponent
    timer = new TimerComponent(this, this);
    timer->EndRun();

    // timer->startRun();
    // 绘画部分
    sprite_Plate = new NewspriteComponent(this, DRAWORRDER::QTE);
    sprite_Point = new NewspriteComponent(this, DRAWORRDER::QTE);
    sprite_Plate->setNeedDraw(0);
    sprite_Point->setNeedDraw(0);
    for (int i = 0; i < 4; i++)
        sprite_colors.at(i) = new NewspriteComponent(this, DRAWORRDER::QTE);

    RoundInitial();
    // 设置图像
    sprite_Point->SetTexture(QTE::PointPicture);
    sprite_Plate->SetTexture(QTE::PlatePicture);

    // 对scale进行处理
    //  scalecnt=0;
    //  scale=1;

    colorInitial = 0;
}
void FightQTE::RoundInitial()
{
    sprite_Plate->setPos(this->getPosition().x() - this->mWidth / 2, this->getPosition().y() - this->mHeight / 2);
    sprite_Point->setPos(this->getPosition().x(), this->getPosition().y());
    for (int i = 0; i < 4; i++)
    {
        hit_type.at(i) = rand() % 2;
        if (hit_type.at(i))
            sprite_colors.at(i)->SetTexture(QTE::BLUEPART);
        else
            sprite_colors.at(i)->SetTexture(QTE::ORANGEPART);
        sprite_colors.at(i)->setAngle(i * 90 - 135);
        sprite_colors.at(i)->setNeedDraw(0);
        sprite_colors.at(i)->setPos(this->getPosition().x(), this->getPosition().y());
    }
}
FightQTE::~FightQTE()
{
    delete sprite_Plate;
    delete sprite_Point;
}
FightQTE::FightQTE(QObject *parent, Game *game) : GameObject(parent, game), round(0), angle(QTE::BEGINANGLE)
{
    initial();
}
void FightQTE::Update()
{

    if (mState == State::EDead)
        return;
    // 物体标定为消亡就不再更新了

    for (auto component : mComponents)
    {
        component->Update();
    }
    // 按照组件数组更新
}

void FightQTE::inputKeyPressProcess(int key)
{
    //qDebug()<<"state_INHIT"<<state_INHIT<<key;
    if (!state_INHIT)
    {
        state_INHIT = 1;
        if (round == 2)
        {
            round2Judge(key);
        }
        else if (round == 3)
        {
            round3Judge(key);
        }
        state_INHIT = 0;
    }
}

void FightQTE::centralFunction()
{

    rotation(QTE::addAngle);
    if (round == 1)
    {
        if (angle % 90 >= 0 && angle % 90 < QTE::addAngle)
        {
            // draw图画
            sprite_colors.at(cnt)->setNeedDraw(1);
            cnt++;
            // 写到这里
            //!< sound
            //!< draw->change
        }
    }
    if (round == 2)
    {
        if (angle % 90 >= QTE::DELTAANGLE && angle % 90 < QTE::DELTAANGLE + QTE::addAngle)
        {
            if (!isHit)
            {
                if (!state_INHIT)
                {
                    cnt++;
                    if (cnt >= 4)
                        cnt = 3;
                }
                lose_typeone();
            }
            else
                isHit = 0;
        }
    }
    if (round == 3)
    {
        if (!colorInitial)
        {
            nextRound();
        }
        if (angle - TargetAngle * 90 >= QTE::DELTAANGLE && angle - TargetAngle * 90 < QTE::DELTAANGLE + QTE::addAngle)
        {
            if (!isHit && sprite_colors.at(TargetAngle)->getNeedDraw())
            {
                lose_typeone();
            }
            else
                isHit = 0;
        }
    }
}
void FightQTE::nextRound()
{
    //qDebug()<<"nextround";
    TargetAngle = rand() % 4;
    for (int i = 0; i < 4; i++)
    {
        sprite_colors.at(i)->setNeedDraw(0);
        sprite_colors.at(i)->SetTexture(QTE::REDPART);
    }
    sprite_colors.at(TargetAngle)->setNeedDraw(1);
    colorInitial = 1;
}
void FightQTE::rotation(int addAngle)
{
    angle = angle + addAngle;
    if (angle >= 360)
    {
        angle -= 360;
    }
    if (angle >= QTE::ROUNDENDANGLE && angle < QTE::ROUNDENDANGLE + QTE::addAngle)
    {
        if (roundIncre)
            round++;
        if (round > 3)
            round = 3;
        cnt = 0;
        isHit = 0;
    }
    sprite_Point->setAngle(drawAngle(angle));
}
inline int FightQTE::changeKeyToNumber(int key)
{
    int number;
    if (key == 'A')
        number = 0;
    else if (key == 'D')
        number = 1;
    else if (key == ' ')
        number = 2;
    return number;
}
inline int FightQTE::drawAngle(int angle)
{
    return angle - 135;
}
void FightQTE::round2Judge(int key)
{
    bool flag = 1;
    int number = changeKeyToNumber(key);
    if (isHit || number != hit_type.at(cnt))
    {
        lose_typetwo();
        flag = 0;
    }

    if (flag)
    {
        int nowAngle = angle;
        int currentPoint = cnt * 90;
        int deltaAngle = std::abs(nowAngle - currentPoint);
        if (deltaAngle >= 180)
            deltaAngle = 360 - deltaAngle; //! 特判0处左侧

        if (deltaAngle <= QTE::DELTAANGLE)
        {
            cnt++;
            if(cnt>3)cnt=3;
            isHit = 1;
            sprite_colors.at(cnt - 1)->setNeedDraw(0);
            //!< correct
            //! <sound
            //! <animation
        }
    }
}
void FightQTE::round3Judge(int key)
{
    bool flag = 1;
    int number = changeKeyToNumber(key);
    if (isHit || number != 2)
    {
        //!< lose 重复hit
        lose_typetwo();
        cnt--;
        flag = 0;
        // qDebug()<<"lose 1";
    }
    if (flag)
    {
        int nowAngle = angle;
        int deltaAngle = std::abs(nowAngle - TargetAngle * 90);

        if (deltaAngle >= 180)
            deltaAngle = 360 - deltaAngle; //! 特判0处左侧
        if (deltaAngle <= QTE::DELTAANGLE)
        {
            //            qDebug()<<"setfalse2";
            sprite_colors.at(TargetAngle)->setNeedDraw(0);
            isHit = 1;
            //!< correct
            //! <sound
            //! <animation
            win();
            if (neednextRound)
                colorInitial = 0;
        }
    }
}
void FightQTE::startQTE()
{
    state_INHIT = 0;
    rotation(-angle - QTE::addAngle);
    round = 1;
    roundIncre = 1;
    cnt = 0;
    colorInitial=0;
}
void FightQTE::lose_typeone()
{

}
void FightQTE::lose_typetwo()
{

}
void FightQTE::win()
{

}
