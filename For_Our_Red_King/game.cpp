#include "game.h"
#include "mytimer.h"
#include "spritecomponent.h"
#include "player.h"
#include "cmath"
#include "blocks.h"
#include"monster.h"
#include "standard.h"
#include <QAudioOutput>
#include "stopbutton.h"

#include "qteobject.h"
Game::Game(QObject *parent,MainWindow* window):
    QObject{parent},
    mPlayer(nullptr)
{
    qDebug()<<"到达Game对象构造函数处";
    mWindow = window;
    mPainter = new QPainter(mWindow);

    mMusicPlayer = new MusicPlayer;
    mMusicPlayer->play(SYSTEM::bgmURL,true);
    //设置bgm

    generateContent();//临时生成关卡信息（为了使构造函数看起来更好看）
    //在制作好关卡后，就是先loadData(关卡字符串资源url) 到 Game中的mInterface中，再调用changeLevel(mInterface)来切换关卡了

    Initialize();

}

void Game::ExitGame()
{
    //这里要制作退出游戏的缓冲动画
    GameObject* tempObject = new GameObject(this,this);
    this->createGameObject(tempObject);
    NewAnimationComponent* overGameAnimation = new NewAnimationComponent(tempObject,DRAWORRDER::backGroundfilter,this);
    overGameAnimation->resetAnimation(FILTER::ExitGameFilter);
    overGameAnimation->setRect(SYSTEM::windowWidth,SYSTEM::windowHeight);
    overGameAnimation->play(false);
    tempObject->addComponent(overGameAnimation);

    QTimer::singleShot(1000,this,[=](){
        unloadData();//先清除数据
        this->removeGameObject(tempObject);
        mIsRuning = false;  //游戏结束标记flag
        this->mWindow->close();
    });//退出游戏
}

//!释放数据
void Game::unloadData()
{
    //清除上一关的GameObject、Sprites、Timers或者结束游戏

}

void Game::generateContent()
{

    mPlayer = new Player(this,this);
    mQTE= new QTEObject(this,this);
    Monster* mMonster = new Monster(this,this);
    stopbutton=new StopButton(this,this);
    returnmainbutton=new ReturnMainButton(this,this);
    createGameObject(mPlayer);
    createGameObject(mQTE);
    createGameObject(mMonster);
    createGameObject(stopbutton);
    createGameObject(returnmainbutton);

    {
        // 测试用创建砖块
        // 注释掉所有和 masu 有关的来去掉玩家脚下的 〼　砖块
        InterfaceBlock interface;

        std::vector<InterfaceBlock> blocks;
        interface.initializeRock(11,
                                 QVector2D(0, 8),
                                 QVector2D(8, 3),
                                 1,0,1,0);
        blocks.push_back(interface);        // 左边大地
        interface.initializeRock(11,
                                 QVector2D(10, 0),
                                 QVector2D(1, 2),
                                 0,1,0,0);
        blocks.push_back(interface);        // 天上大柱子
        interface.initializeRock(11,
                                 QVector2D(10, 6),
                                 QVector2D(5, 3),
                                 1,1,1,1);
        blocks.push_back(interface);        // 右边大地
        interface.initializeBackGround(1);
        blocks.push_back(interface);        // 背景
        interface.initializeDecoration(41,
                                       QVector2D(12, 5),
                                       0,
                                       6);
        blocks.push_back(interface);        // 钱
        interface.initializeBar(0, QVector2D(5, 5));
        blocks.push_back(interface);        // 血条
        interface.initializeDamage(45,
                                   QVector2D(2, 3),
                                   2,
                                   60,
                                   5,
                                   QVector2D(1, 1));
        blocks.push_back(interface);        // 伤害旗帜
        interface.initializeDamage(22,
                                   QVector2D(7, 2),
                                   2,
                                   60,
                                   -10,
                                   QVector2D(1, 1));
        blocks.push_back(interface);        // 隐藏回血块
        interface.initializeDamage(22,
                                   QVector2D(-4, 12),
                                   2,
                                   60,
                                   1000,
                                   QVector2D(26, 1));
        blocks.push_back(interface);        // 虚空 vanity
        interface.initializeDecoration(23,
                                       QVector2D(9, 7),
                                       0,
                                       0);
        blocks.push_back(interface);        // q
        interface.initializeDecoration(24,
                                       QVector2D(9, 8),
                                       0,
                                       0);
        blocks.push_back(interface);        // u
        interface.initializeDecoration(25,
                                       QVector2D(9, 9),
                                       0,
                                       0);
        blocks.push_back(interface);        // i
        interface.initializeDecoration(26,
                                       QVector2D(9, 10),
                                       0,
                                       0);
        blocks.push_back(interface);        // t
        interface.initializeDecoration(48,
                                       QVector2D(9, 10),
                                       0,
                                       0);
        blocks.push_back(interface);        // 梯子头装饰
        interface.initializeDoor(47,
                                 QVector2D(9, 11),
                                 2,
                                 0);
        blocks.push_back(interface);        // 退出
        interface.initializeRock(12,
                                 QVector2D(17, 4),
                                 QVector2D(1, 0),
                                 1,0,1,1,0);
        blocks.push_back(interface);        // 开始平台
        interface.initializeDoor(43,
                                 QVector2D(18, 2),
                                 0,
                                 0);
        blocks.push_back(interface);        // 开始门



        for(auto block : blocks)
        {
            block.createBlock(this);
        }
    }
}

Game::~Game()
{

}

//!初始化
bool Game::Initialize()
{
    QTimer::singleShot(250,this,[=](){
        mTimer = new myTimer(this,this);
        timerLoop = startTimer(15);      //建立循环timer并设定每隔15ms触发事件timerEvent
    });
    return true;
}


//!两个物体的碰撞检测
bool Game::collisionDetection(GameObject* first,GameObject* second)
{
    if(second ->gameObjectType == GameObject::Type::Player)
        std::swap(first,second);
    //依靠aabb碰撞实现
    QVector2D f_pos = first->getPosition(),s_pos = second->getPosition();
    QVector2D f_scale = first->getScale(),s_scale = second->getScale();
    float f_Width = first->getWidth()*f_scale.x(),f_Height = first->getHeight() * f_scale.y();//碰撞框宽
    float s_Width = second->getWidth()*s_scale.x(),s_Height = second->getHeight() * s_scale.y();//碰撞框高

    //下面是对于贴图不透明度的修改进行的玄学修改框框位置以及大小（针对player）
    auto getCollidePosition = [](QVector2D pos,GameObject* object) -> QVector2D{
        if(object->getDirection() == 1)
            pos = QVector2D(pos.x() + object->getWidth() * 0.08,pos.y()+ object->getHeight() * 0.15);
        else
            pos = QVector2D(pos.x() + object->getWidth() * 0.07,pos.y()+ object->getHeight() * 0.15);
        return pos;
    };

    if(first->gameObjectType == GameObject::Type::Player){
        f_pos = getCollidePosition(f_pos,first);
        f_Width *= 0.55;
        f_Height *= 0.85;
    }
    if(second->gameObjectType == GameObject::Type::Monster){
        s_pos = getCollidePosition(s_pos,second);
        s_Width *= 0.55;
        s_Height *= 0.85;
    }


    auto getMiddlePoint = [](QVector2D pos,float width,float height) -> QVector2D{
        QVector2D ret = QVector2D(pos.x()+(width/2),pos.y() + (height/2));
        return ret;
    };//获得框框中心点的lamda function

    QVector2D f_midPoint = getMiddlePoint(f_pos,f_Width,f_Height);
    QVector2D s_midPoint = getMiddlePoint(s_pos,s_Width,s_Height);
    QVector2D deltaMidPoint = s_midPoint - f_midPoint;
    //获得物体对象两个的中心点并计算delta
    QVector2D totalHalfSize = QVector2D((f_Width+s_Width)/2,(f_Height+s_Height)/2);
    //计算两个物体一半长的和

    if(abs(deltaMidPoint.x()) < totalHalfSize.x() &&
        abs(deltaMidPoint.y()) < totalHalfSize.y())
        return true;   //发生碰撞
    return false;  //未发生碰撞
}

void Game::timerEvent(QTimerEvent *event)
{

    if(event->timerId() == timerLoop){
        Loop();
        //主循环
    }
}

//!主循环
void Game::Loop()
{
    if(mIsRuning && !mIsLooping)
    {
        mIsLooping = true;
        Event();
        if(!stop)
        Update();
        mWindow->update();
        // Draw();

        mIsLooping = false;
    }
}

//!设置帧率
void Game::Tick(int fps)
{
    // 根据设置的帧率计算每帧至少的时间
    int fpsTime = 1000 / fps;

    while(mTimer->recordTime->elapsed() > fpsTime + mTimer->ticksCount)
        QTest::qSleep(1);
    //如果这一帧未到达时间，则等待

    mTimer->deltaTime = (mTimer->recordTime->elapsed() - mTimer->ticksCount) /1000.0f;
    //计算新deltaTime
    mTimer->ticksCount = mTimer->recordTime->elapsed();
    //计算新一帧开始之前所经过的总时间
}

void Game::Shutdown()
{
    unloadData();
}


void Game::createGameObject(GameObject* gameObject)
{
    qDebug("创建第%d个GameObject",mGameObjects.size());
    // 如果当前正在更新，将该对象加入等待区
    if (mIsUpdating)
    {
        mPendingObjects.emplace_back(gameObject);
    }
    else
    {
        mGameObjects.emplace_back(gameObject);
    }
}

void Game::removeGameObject(GameObject* gameObject)
{
    // 先在等待区中寻找并移除物体
    auto iter = std::find(mPendingObjects.begin(), mPendingObjects.end(), gameObject);
    if (iter != mPendingObjects.end())
    {
        std::iter_swap(iter, mPendingObjects.end() - 1);
        mPendingObjects.pop_back();
    }

    // 在正式物体区中寻找并移除物体
    iter = std::find(mGameObjects.begin(), mGameObjects.end(), gameObject);
    if (iter != mGameObjects.end())
    {
        std::iter_swap(iter, mGameObjects.end() - 1);
        mGameObjects.pop_back();
    }
}

void Game::Event()
{
    //to be written需要做的事件操作
    // QVector2D playerPos = mPlayer->getPosition();
    // QVector2D monsterPos;
    // float dis;
    // for(auto t_gameObject : mGameObjects)
    //     if(t_gameObject->gameObjectType == GameObject::Type::Monster){
    //         monsterPos = t_gameObject->getPosition();
    //         dis = std::sqrt(pow(playerPos.x()-monsterPos.x(),2) + pow(playerPos.y()-monsterPos.y(),2));

    //     }
    //判定玩家跟各个object距离
}

void Game::Update()
{
    //设置帧率
    Tick(60);

    // 更新开始
    mIsUpdating = true;
    // 遍历并执行所有物体的更新函数
    for (auto gameObject : mGameObjects)
    {
        gameObject->Update();
    }
    // 更新结束
    mIsUpdating = false;

    // 将所有等待区物体移动至正式的物体区
    for (auto pendingObject : mPendingObjects)
    {
        mGameObjects.emplace_back(pendingObject);
    }
    // 清空等待区
    mPendingObjects.clear();

    // 将所有状态为EDead的物体添加至死亡区
    std::vector<GameObject*> deadObjects;
    for (auto deadObject : mGameObjects)
    {
        if (deadObject->getState() == GameObject::State::EDead)
        {
            deadObjects.emplace_back(deadObject);
            qDebug()<<"删除死亡物体";
        }
    }
    // 释放掉所有死亡区的物体
    for (auto deadObject : deadObjects)
    {
        this->removeGameObject(deadObject);
        delete deadObject;
    }


}

//!绘制精灵
void Game::Draw()
{
    //这个实际上已经不会调用了，在mainwindows中paintevent中实现
    for (auto sprite:mSprites)
    {
        sprite->Draw();
    }
}

//!创建精灵并按绘画顺序插入
void Game::createSprite(spriteComponent* sprite)
{
    int order = sprite->getDrawOrder();
    // 按照绘制顺序插入
    std::vector<spriteComponent*>::iterator iter = mSprites.begin();
    for (; iter != mSprites.end(); ++iter)
    {
        if (order < (*iter)->getDrawOrder())
        {
            break;
        }
    }
    mSprites.insert(iter, sprite);
}

//!移除精灵
void Game::removeSprite(spriteComponent* sprite)
{
    std::vector<spriteComponent*>::iterator iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    if(iter!= mSprites.end())
        mSprites.erase(iter);
}

//!移除自定义myTimer
void Game::removeMyTimer(myTimer* timer)
{
    delete timer;
}

void Game::keyPressInput(int e)
{
    if(this->mIsRuning){
        for(auto gameObject:mGameObjects)
            gameObject->inputKeyPressProcess(e);
    }
}

void Game::keyReleaseInput(int e)
{
    if(this->mIsRuning){
        for(auto gameObject:mGameObjects)
            gameObject->inputKeyReleaseProcess(e);
    }
}

void Game::mousePressInput(QMouseEvent * e)
{
    if(this->mIsRuning){
        for(auto gameObject:mGameObjects)
            gameObject->inputMousePressProcess(e);
    }
}

void Game::mouseReleaseInput(QMouseEvent * e)
{
    if(this->mIsRuning){
        for(auto gameObject:mGameObjects)
            gameObject->inputMouseReleaseProcess(e);
    }
}
