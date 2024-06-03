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
#include "musicplayer.h"
#include "stopbutton.h"
#include "interface.h"

class GameObject;
class spriteComponent;
class Player;
class myTimer;
class Monster;
class StopButton;
class QTEObject;
class Game: public QObject
{
    Q_OBJECT
public:
    bool stop=false;
    bool isQTE = false;      //!<正在QTE中

    Player* mPlayer;                  //!<    玩家角色
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
    void mousePressInput(QMouseEvent * event); //!<按下鼠标按键event
    void mouseReleaseInput(QMouseEvent *  event);

    void createGameObject(GameObject*);  //!<创建gameObject
    void removeGameObject(GameObject*);  //!<移除gameObject
    void createSprite(spriteComponent* sprite);//!<创建并按绘制顺序存储精灵
    void removeSprite(spriteComponent* sprite);//!<移除精灵
    void removeMyTimer(myTimer* timer);  //!<移除自定义计时器

    bool collisionDetection(GameObject* first,GameObject* second);   //!<两个对象的碰撞检测判定

    void generateContent();//!<临时生成关卡信息的函数

    void changeLevel(Interface i);   //!<改变关卡、回到主界面函数
    void loadData(QString target);   //!<加载数据
    void unloadData();               //!<释放数据
    void ExitGame();                 //!<游戏结束函数
    bool mIsRuning = true;                      //!<    运行状态

protected:
    virtual void timerEvent(QTimerEvent *event);    //!<定时器事件

private:
    MusicPlayer * mMusicPlayer ;                    //!<音乐播放player
    std::vector<GameObject*> mPendingObjects;        //!<    等待状态的游戏物体容器

    bool    mIsUpdating = false;                    //!<    是否在更新状态
    bool    mIsLooping = false;                     //!<    是否在循环中

    int timerLoop;                    //!<主循环Loop的timer ID
    myTimer* mTimer;                  //!<主循环用timer
    QTEObject* mQTE;                    //!< qte
    StopButton* stopbutton;

    void Update();                       //!<更新
    void Draw();                         //!<绘制
    void Tick(int fps);                  //!<设置帧率

signals:
};

#endif // GAME_H
