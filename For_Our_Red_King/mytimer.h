#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QElapsedTimer>

class Game;
class myTimer : public QObject
{
    Q_OBJECT
public:
    explicit myTimer(QObject *parent = nullptr,Game* game = nullptr);
    ~myTimer();
    float deltaTime;            //! 增量time
    unsigned int ticksCount;         //! 下一帧开始之前的总时间
    QElapsedTimer* recordTime;                 //!记录从game开始的时间
private:
    Game* mGame;          //!从属Game对象

signals:
};

#endif // MYTIMER_H
