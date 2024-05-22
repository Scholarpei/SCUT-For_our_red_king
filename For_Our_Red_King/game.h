#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "gameobject.h"
#include <QTimer>
#include <QTimerEvent>
#include <QTest>
#include <QElapsedTimer>
#include <QEvent>
#include <QPainter>
#include "mainwindow.h"

class GameObject;
class spriteComponent;
class Player;
class myTimer;

class Game: public QObject
{
    Q_OBJECT
public:
    std::vector<GameObject*> mGameObjects;        //!<    游戏物体容器
    std::vector<spriteComponent*>mSprites;          //!<   精灵容器
    MainWindow* mWindow;                          //!<  主界面
    QPainter* mPainter;                                //!<绘画Painter
    explicit Game(QObject *parent = nullptr,MainWindow* window = nullptr);
    virtual ~Game();

    bool Initialize();//!<初始化
    void Shutdown();  //!<游戏结束
    void Loop();      //!<主循环
    void Event();     //!<事件处理：碰撞...

    void keyPressInput(int event);  //!<按下按键event
    void keyReleaseInput(int event); //!<松开按键event


    void createGameObject(GameObject*);  //!<创建gameObject
    void removeGameObject(GameObject*);  //!<移除gameObject
    void createSprite(spriteComponent* sprite);//!<创建并按绘制顺序存储精灵
    void removeSprite(spriteComponent* sprite);//!<移除精灵
    void removeMyTimer(myTimer* timer);  //!<移除自定义计时器

    bool collisionDetection(GameObject* first,GameObject* second);   //!<两个对象的碰撞检测判定

protected:
    virtual void timerEvent(QTimerEvent *event);    //!<定时器事件


private:
    std::vector<GameObject*> mPendingObjects;        //!<    等待状态的游戏物体容器

    bool    mIsUpdating;                    //!<    是否在更新状态
    bool    mIsRuning;                      //!<    运行状态
    bool    mIsLooping;                     //!<    是否在循环中
    Player* mPlayer;                  //!<    玩家角色
    int timerLoop;                    //!<主循环Loop的timer ID
    myTimer* mTimer;                  //!<主循环用timer



    void Update();                       //!<更新
    void Draw();                         //!<绘制
    void Tick(int fps);                  //!<设置帧率
    void loadData();                     //!<加载数据
    void unloadData();                   //!<释放数据

signals:
};

#endif // GAME_H
