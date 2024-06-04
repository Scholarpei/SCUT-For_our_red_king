#include "bleedingcomponent.h"
#include "game.h"
#include "gameobject.h"

BleedingComponent::BleedingComponent(GameObject *gameObject, int drawOrder):
    spriteComponent(gameObject, drawOrder),
    plate(BACKGROUND::plate),
    blood(BACKGROUND::blood),
    hurting(BACKGROUND::hurting),
    healing(BACKGROUND::healing),
    shocked_plate(BACKGROUND::shocked_plate),
    drawn_plate(this->plate),
    state(State::ILDE)
{
    this->BLOOD_RELATIVE_POSI = QVector2D(4, 4);
    this->painter = this->mGameObject->mGame->mWindow->mPainter;
}

BleedingComponent::~BleedingComponent()
{
    //父类执行removesprite即可
    // mGameObject->getGame()->removeSprite(this);
}

void BleedingComponent::setTecture(AnimationLoader plate, AnimationLoader blood, AnimationLoader hurting, AnimationLoader healing, AnimationLoader shocked_plate)
{
    this->plate = plate;
    this->blood = blood;
    this->hurting = hurting;
    this->healing = healing;
    this->shocked_plate = shocked_plate;

    this->drawn_plate = this->plate;


    this->BLOOD_RELATIVE_POSI = QVector2D((plate.GetpixX()-blood.GetpixX())/2,
                                          (plate.GetpixY()-blood.GetpixY())/2);

}

void BleedingComponent::Draw()
{

    // 先画盘子
    painter->drawPixmap(this->mGameObject->getPosition().x(),
                        this->mGameObject->getPosition().y(),
                        QPixmap(this->drawn_plate.GetpixAddress()));

    // 根据该变量决定怎么画
    if (this->changePerTick > 0)
    {
        this->draw_value(this->hpAfter, this->healing.GetpixAddress());
        this->draw_value(this->hpCurrent, this->blood.GetpixAddress());
    }
    else if(this->changePerTick < 0)
    {
        this->draw_value(this->hpCurrent, this->hurting.GetpixAddress());
        this->draw_value(this->hpAfter, this->blood.GetpixAddress());
    }
    else
    {
        this->draw_value(this->hpCurrent, this->blood.GetpixAddress());
    }

    // 下一帧
    this->next_tick();
}

void BleedingComponent::changeHP(int HP)
{
    this->currentTick = 0;
    this->hpCurrent = this->hpAfter;
    this->hpAfter = HP;
    this->changePerTick = (double)(this->hpAfter - this->hpCurrent) / this->RECOVERING_TICKS;

    switch(this->state)
    {
    case State::ILDE:
    {
        this->state = State::SHOCKED;
        break;
    }
    case State::SHOCKED:
    {
        break;
    }
    case State::RECOVERING:
    {
        this->state = State::SHOCKED;
        break;
    }
    }
}

void BleedingComponent::next_tick()
{
    switch(this->state)
    {
    case State::ILDE:
    {
        break;
    }
    case State::SHOCKED:
    {
        if(this->currentTick == this->SHOECKED_TICKS)
        {
            this->currentTick = 0;
            this->state = State::RECOVERING;
            // this->drawn_plate = this->plate;
        }
        else
        {
            if(this->currentTick <= this->FLASHING_TICKS)
            {
                if(this->currentTick % this->FLASHING_DURATION == 0)
                {
                    if(this->drawn_plate.GetpixAddress() == this->plate.GetpixAddress())
                    {
                        this->drawn_plate = this->shocked_plate;
                    }
                    else
                    {
                        this->drawn_plate = this->plate;
                    }
                }
            }
            this->currentTick++;
        }
        break;
    }
    case State::RECOVERING:
    {
        if(this->currentTick == this->RECOVERING_TICKS)
        {
            this->currentTick = 0;
            this->changePerTick = 0;
            this->state = State::ILDE;
            this->hpCurrent = this->hpAfter;
        }
        else
        {
            this->currentTick++;
            this->hpCurrent += this->changePerTick;
        }
        break;
    }
    }
}

void BleedingComponent::draw_value(int value, QString add)
{
    double widthF = (double)this->blood.GetpixX() * value / this->MAX_HP;
    int width;

    if (widthF < this->blood.GetpixX() && widthF > this->blood.GetpixX()-1) width = this->blood.GetpixX()-1;
    else if (widthF > 0 && widthF < 1) width = 1;
    else width = round(widthF);

    QRect source(0,
                 0,
                 width,
                 this->blood.GetpixY());
    QRect target(this->mGameObject->getPosition().x() + this->BLOOD_RELATIVE_POSI.x(),
                 this->mGameObject->getPosition().y() + this->BLOOD_RELATIVE_POSI.y(),
                 width,
                 this->blood.GetpixY());

    this->painter->drawPixmap(target, QPixmap(add), source);
}

