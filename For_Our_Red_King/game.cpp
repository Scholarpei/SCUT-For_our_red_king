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
#include "qteplayer.h"
#include "qteobject.h"
#include "interface.h"
Game::Game(QObject *parent,MainWindow* window):
    QObject{parent},
    mPlayer(nullptr)
{
    qDebug()<<"到达Game对象构造函数处";
    mWindow = window;
    mPainter = new QPainter(mWindow);
    mMusicPlayer = new MusicPlayer;
    mSoundPlayer = new MusicPlayer;//初始化音效player

//#define GENERATE_DATA_MODE
#define LOAD_DATA_MODE

    #ifdef GENERATE_DATA_MODE
        generateContent();//临时生成关卡信息（为了使构造函数看起来更好看）
        // generateLevelData("Level3");用以生成level data
    #endif

    //上面这两行是用来生成关卡数据用的，下面的是载入数据用的

    #ifdef LOAD_DATA_MODE
        loadData(DATA::MainLevelDataURL);//这里更改路径可以生成数据
        changeLevel(mInterface);
    #endif

    //在制作好关卡后，就是先loadData(关卡字符串资源url) 到 Game中的mInterface中，再调用changeLevel(mInterface)来切换关卡了
    //示例：loadData("mainLevel.data"); changeLevel(mInterface)
    Initialize();

    mStatistic = this->getLocalStatistic();

    QTimer::singleShot(250,this,[=](){
        mTimer = new myTimer(this,this);
        timerLoop = startTimer(15);      //建立循环timer并设定每隔15ms触发事件timerEvent
    });


/*这个是切换关卡的示例
    QTimer::singleShot(2000,this,[=](){
        this->mGoToNextLevel = 1;
     });
*/

}

void Game::loadData(QString target)
{
    //载入target为名字的Interface数据，存储在mInterface中
    //类似于mInterface = read()....
    QString fileName = target;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("读入失败！！！");
        exit(0);
    }
    file.read((char *)&mInterface,sizeof(Interface));//读取数据到Interface

    if(target == DATA::MainLevelDataURL)
        this->lastLevelNo = 0;
    else if(target == DATA::Level1DataURL)
        this->lastLevelNo = 1;
    else if(target ==DATA::Level2DataURL)
        this->lastLevelNo = 2;
    else if(target == DATA::Level3DataURL)
        this->lastLevelNo = 3;
    //记录切换关卡编号
}

void Game::generateLevelData(QString filename)
{
    Interface i;//空的关卡data
    //下面为示例写法
    InterfacePlayer   Playertmp ;
    InterfaceMonster  Monstertmp;
    Player* playerptr;
    Monster* monsterptr;
    for(auto gameObject:mGameObjects)
        {
            switch(gameObject->gameObjectType){
                //根据不同的gameobject的类型选择对应的类的函数
                case GameObject::Type::Player :
                    playerptr = dynamic_cast<Player*>(gameObject);
                    Playertmp.interfaceInitialization(playerptr);
                    i.playerinterface = Playertmp;
                    break;
                case GameObject::Type::Monster :
                    monsterptr = dynamic_cast<Monster*>(gameObject);
                    Monstertmp.interfaceInitialization(monsterptr);
                    i.monsterinterfacearray[i.Monstersize++] = Monstertmp;
                    break;
                default:
                    break;
            }
        }

    int blocksleveltype = -1;
    if(filename == "mainLevel")
        blocksleveltype = 0;
    else if(filename == "Level1")
        blocksleveltype = 1;
    else if(filename == "Level2")
        blocksleveltype = 2;
    else if(filename == "Level3")
        blocksleveltype = 3;

    auto blocks = VANITY::unlimited_block_works(blocksleveltype);
    for(auto block : blocks)
    {
        i.blockInterfaceArray[i.BlockSize++] = block;
    }

    QString Filename = "..\\..\\Data\\levelData\\" + filename;    //mainLevel名字即为存在本地的名字
    QFile file(Filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug()<<"写入发生错误！";
        exit(0);
    }
    file.write((const char*)&i,sizeof(Interface));//写入
}

void Game::changeLevel(Interface i)
{
    unloadData();//先清除之前的数据
    //根据mInterface的内容初始化数据   意思是把数据关卡信息导入到游戏中

    mMusicPlayer->play(SYSTEM::bgmURL,true);

    mPlayer = new Player(this,this);
    mPlayer->initialByInterface(i.playerinterface);
    this->createGameObject(mPlayer);

    for(int j=0;j<i.Monstersize;j++){
        Monster* monster = new Monster(this,this);  //实例化默认Monster
        monster->initialByInterface(i.monsterinterfacearray[j]);  //根据monsterinterface信息初始化当前的Monster
        this->createGameObject(monster);//放入mGameObject中
    }

    for(int j = 0; j < i.BlockSize; j++)
    {
        i.blockInterfaceArray[j].createBlock(this);
    }

    // auto blocks = VANITY::unlimited_block_works(3);
    // for(auto block : blocks)
    // {
    //     block.createBlock(this);
    // }

    mIsRuning = true;

}



//!退出游戏就调用这个函数
void Game::ExitGame()
{
    //这里要制作退出游戏的缓冲动画
    if(!mExitGameAnimationFlag){
        GameObject* tempObject = new GameObject(this,this);
        this->createGameObject(tempObject);
        NewAnimationComponent* overGameAnimation = new NewAnimationComponent(tempObject,DRAWORRDER::backGroundfilter,this);
        overGameAnimation->resetAnimation(FILTER::ExitGameFilter);
        overGameAnimation->setRect(SYSTEM::windowWidth,SYSTEM::windowHeight);
        overGameAnimation->play(false);
        mExitGameAnimationFlag= true;
    }

    this->updateStatistic();
    //更新数据

    QTimer::singleShot(1000,this,[=](){
        unloadData();//先清除数据
        mIsRuning = false;  //游戏结束标记flag
        this->mWindow->close();
    });//退出游戏
}

//!释放数据
void Game::unloadData()
{
    mIsRuning = false;
    //清除上一关的GameObject、Sprites、Timers或者结束游戏

    for(int i=0;i<mGameObjects.size();i++){
        qDebug("order:%d",i);
        delete mGameObjects[i];
    }
    mGameObjects.clear();

    while(!mSprites.empty())
        this->removeSprite(mSprites[0]);
}

void Game::generateContent()
{

    mPlayer = new Player(this,this);
    mPlayer->setPosition(QVector2D(550,600));
    createGameObject(mPlayer);


    Monster* Monster1 = new Monster(this,this);
    Monster1->setPosition(QVector2D(800,600));
    Monster1->mMonsterType = Monster::MonsterType::Robot;


    Monster* Monster2 =  new Monster(this,this);
    Monster2->setPosition(QVector2D(800,200));
    Monster2->mMonsterType = Monster::MonsterType::Biker;

    Monster* Monster3 =  new Monster(this,this);
    Monster3->setPosition(QVector2D(500,400));
    Monster3->mMonsterType = Monster::MonsterType::Cyborg;

    Monster* Monster4 =  new Monster(this,this);
    Monster4->setPosition(QVector2D(850,50));
    Monster4->mMonsterType = Monster::MonsterType::Batman;

    Monster* Monster5 =  new Monster(this,this);
    Monster5->setPosition(QVector2D(100,50));
    Monster5->mMonsterType = Monster::MonsterType::Robot;

    Monster* Monster6 =  new Monster(this,this);
    Monster6->setPosition(QVector2D(200,300));
    Monster6->mMonsterType = Monster::MonsterType::Batman;


    createGameObject(Monster1);
    createGameObject(Monster2);
    createGameObject(Monster3);
    createGameObject(Monster4);
    createGameObject(Monster5);
    createGameObject(Monster6);


    {
        // 测试用创建砖块

        auto blocks = VANITY::unlimited_block_works(3);

        for(auto block : blocks)
        {
            block.createBlock(this);
        }
    }

    /* Level1 information
    mPlayer = new Player(this,this);
    mPlayer->setPosition(QVector2D(20,500));
    createGameObject(mPlayer);


    Monster* Monster1 = new Monster(this,this);
    Monster1->setPosition(QVector2D(400,600));
    Monster1->mMonsterType = Monster::MonsterType::Robot;


    Monster* Monster2 =  new Monster(this,this);
    Monster2->setPosition(QVector2D(750,660));
    Monster2->mMonsterType = Monster::MonsterType::Biker;

    Monster* Monster3 =  new Monster(this,this);
    Monster3->setPosition(QVector2D(1050,560));
    Monster3->mMonsterType = Monster::MonsterType::Cyborg;

    Monster* Monster4 =  new Monster(this,this);
    Monster4->setPosition(QVector2D(600,360));
    Monster4->mMonsterType = Monster::MonsterType::Batman;

    Monster* Monster5 =  new Monster(this,this);
    Monster5->setPosition(QVector2D(300,300));
    Monster5->mMonsterType = Monster::MonsterType::Biker;

    Monster* Monster6 =  new Monster(this,this);
    Monster6->setPosition(QVector2D(550,50));
    Monster6->mMonsterType = Monster::MonsterType::Biker;

    createGameObject(Monster1);
    createGameObject(Monster2);
    createGameObject(Monster3);
    createGameObject(Monster4);
    createGameObject(Monster5);
    createGameObject(Monster6);
    */

    /* Level2 information
    mPlayer = new Player(this,this);
    mPlayer->setPosition(QVector2D(20,100));
    createGameObject(mPlayer);


    Monster* Monster1 = new Monster(this,this);
    Monster1->setPosition(QVector2D(150,400));
    Monster1->mMonsterType = Monster::MonsterType::Robot;


    Monster* Monster2 =  new Monster(this,this);
    Monster2->setPosition(QVector2D(750,660));
    Monster2->mMonsterType = Monster::MonsterType::Biker;

    Monster* Monster3 =  new Monster(this,this);
    Monster3->setPosition(QVector2D(500,500));
    Monster3->mMonsterType = Monster::MonsterType::Cyborg;

    Monster* Monster4 =  new Monster(this,this);
    Monster4->setPosition(QVector2D(850,550));
    Monster4->mMonsterType = Monster::MonsterType::Batman;

    Monster* Monster5 =  new Monster(this,this);
    Monster5->setPosition(QVector2D(600,200));
    Monster5->mMonsterType = Monster::MonsterType::Biker;

    Monster* Monster6 =  new Monster(this,this);
    Monster6->setPosition(QVector2D(700,50));
    Monster6->mMonsterType = Monster::MonsterType::Robot;

    Monster* Monster7 =  new Monster(this,this);
    Monster7->setPosition(QVector2D(300,50));
    Monster7->mMonsterType = Monster::MonsterType::Cyborg;

    createGameObject(Monster1);
    createGameObject(Monster2);
    createGameObject(Monster3);
    createGameObject(Monster4);
    createGameObject(Monster5);
    createGameObject(Monster6);
    createGameObject(Monster7);
    */
}

Game::~Game()
{

}

//!初始化
bool Game::Initialize()
{
    mQTE= new QTEObject(this,this);
    stopbutton = new StopButton(this,this);
    returnmainbutton = new ReturnMainButton(this,this);
    statisticbutton = new StatisticButton(this,this);
    createGameObject(mQTE);
    createGameObject(stopbutton);
    createGameObject(returnmainbutton);
    createGameObject(mQTE->object_Enermy);
    createGameObject(mQTE->object_Player);
    createGameObject(statisticbutton);
    //其他的初始化内容 QTE button

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
        pos.setY(pos.y()+ object->getHeight() * 0.15);
        if(object->gameObjectType == GameObject::Type::Player){
            if(object->getDirection() == 1)
                pos.setX( pos.x() + object->getWidth() * 0.08);
            else
                pos.setX(pos.x() + object->getWidth() * 0.07);
        }
        else if(object->gameObjectType == GameObject::Type::Monster){

        }
        return pos;
    };

    if(first->gameObjectType == GameObject::Type::Player){
        f_pos = getCollidePosition(f_pos,first);
        f_Width *= 0.55;
        f_Height *= 0.80;
    }

    if(first->gameObjectType == GameObject::Type::Monster){
        f_pos = getCollidePosition(f_pos,first);
        Monster* monsterptr = dynamic_cast<Monster*>(first);
        switch(monsterptr->mMonsterType){
        case Monster::MonsterType::Batman:
            f_Width *= 0.3;
            break;
        case Monster::MonsterType::Biker:
            f_Width *= 0.4;
            break;
        case Monster::MonsterType::Cyborg :
            f_Width *= 0.4;
            break;
        case Monster::MonsterType::Robot :
            f_Width *= 0.4;
            break;
        }
        f_Height *= 0.85;
    }
    if(second->gameObjectType == GameObject::Type::Monster){
        s_pos = getCollidePosition(s_pos,second);
        Monster* monsterptr = dynamic_cast<Monster*>(second);
        switch(monsterptr->mMonsterType){
            case Monster::MonsterType::Batman:
                s_Width *= 0.3;
                break;
            case Monster::MonsterType::Biker:
                s_Width *= 0.4;
                break;
            case Monster::MonsterType::Cyborg :
                s_Width *= 0.4;
                break;
            case Monster::MonsterType::Robot :
                s_Width *= 0.4;
                break;
        }
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
    if(this->mGoToNextLevel){
        //切换关卡
        if(mGoToNextLevel == 1){
            this->mStatistic.maxPassLevelNumber = 0;//过关归零
            unloadData();
            loadData(DATA::MainLevelDataURL);
            changeLevel(mInterface);
            Initialize();
        }
        else{
            //从3关中随机选择一关
            unloadData();
            int levelVal = std::rand()%3+1;
            while(levelVal == lastLevelNo)
                levelVal = rand()%3+1;//关卡切换不能跟上一关一样
            switch(levelVal){
            case 1:
                loadData(DATA::Level1DataURL);
                break;
            case 2:
                loadData(DATA::Level2DataURL);
                break;
            case 3:
                loadData(DATA::Level3DataURL);
                break;
            }
            changeLevel(mInterface);

            Initialize();
        }
        this->mGoToNextLevel = 0;//归零
    }
    //检测是否要切换关卡并切换

    //qte win后的动画等待事件开始
    if(this->qteWinPeriodFlag){
        this->qteWintimer++;
        if(qteWintimer > QTE::QteWinWaitingTime){//win的动画效果结束，开始自动寻找追击对象
            this->qteWinPeriodFlag = false;  //要设置为false
            Monster* sourceMonsterPtr = nullptr;
            float dis;
            for(auto object:mGameObjects)
                if(object->gameObjectType == GameObject::Type::Monster){
                    //怪物才追击
                    Monster * monsterptr = dynamic_cast<Monster*>(object);
                    if(monsterptr->mMonsterState == Monster::MonsterState::DYING)
                        continue;//不考虑死亡的Monster
                    dis = std::sqrt(std::pow(object->getPosition().x() - mPlayer->getPosition().x(),2) + std::pow(object->getPosition().y() - mPlayer->getPosition().y(),2));
                    if(dis < QTE::leastQTEDistance){
                        //小于追击范围，锁定目标
                        sourceMonsterPtr = dynamic_cast<Monster*>(object);
                        break;
                    }
                }
            //结束搜索
            if(sourceMonsterPtr != nullptr){
                bool dir = (mPlayer->getPosition().x() - sourceMonsterPtr->getPosition().x()) > 0;
                int to = dir? 1 : -1;
                mPlayer->setMoveDirection(-to);
                sourceMonsterPtr->setMoveDirection(to);
                //改变二者的方向关系

                mQTE->setMonster(sourceMonsterPtr);
                mQTE->QTEshowGraph(true);
                mQTE->startQTEfrom3();//从最后一轮开始
            }
            else{
                this->nowIsQTE = false;//结束qte了， component正常运作
                this->mQTE->object_Enermy->setNeedDraw(0);
                this->mQTE->object_Player->setNeedDraw(0);
                this->mMusicPlayer->setVolumeProportion(0.8f);//设置背景音乐恢复音量
                mQTE->mbgmPlayer->stop();//停止播放鼓点
            }
        }
    }
    //qte win后的动画等待事件结束
}

void Game::TryQTE()
{
    Monster* sourceMonsterPtr = nullptr;
    float dis;
    for(auto object:mGameObjects)
        if(object->gameObjectType == GameObject::Type::Monster){
            //怪物才追击
            Monster * monsterptr = dynamic_cast<Monster*>(object);
            if(monsterptr->mMonsterState == Monster::MonsterState::DYING)
                continue;//不考虑死亡的Monster
            dis = std::sqrt(std::pow(object->getPosition().x() - mPlayer->getPosition().x(),2) + std::pow(object->getPosition().y() - mPlayer->getPosition().y(),2));
            if(dis < QTE::leastQTEDistance){
                //小于追击范围，锁定目标
                sourceMonsterPtr = dynamic_cast<Monster*>(object);
                break;
            }
        }
    if(sourceMonsterPtr != nullptr){
        //已获取
        bool dir = (mPlayer->getPosition().x() - sourceMonsterPtr->getPosition().x()) > 0;
        int to = dir? 1 : -1;
        mPlayer->setMoveDirection(-to);
        sourceMonsterPtr->setMoveDirection(to);
        //改变二者的方向关系

        mQTE->setMonster(sourceMonsterPtr);
        this->nowIsQTE = true;
        mQTE->QTEshowGraph(true);
        this->mMusicPlayer->setVolumeProportion(0.2);//设置背景音乐弱化
        mQTE->mbgmPlayer->play(QTE::qteContinueURL,false);//qte的bgm鼓点
        this->mSoundPlayer->play(QTE::firstStartQTEURL,false);//开始qte的音效
        mQTE->QTEBegin();
    }
}

void Game::Update()
{

    //设置帧率
    Tick(60);

    if(stop)
        return ;

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
    if(iter != mSprites.end())
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
        if(e == Qt::Key_E && !nowIsQTE){
            //按下qte检测的E键单独处理
            TryQTE();
        }
        else
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

GameStatisticInterface Game::getLocalStatistic()
{
    QFile file(DATA::GameStatisticURL);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug("本地读入失败或尚未创建本地文件");
        GameStatisticInterface i;
        QString Filename = ".\\GameStatistic";    //这个路径可以根据自己的更改
        QFile file(Filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug()<<"写入Statistic发生错误！";
            exit(0);
        }
        file.write((const char*)&i,sizeof(GameStatisticInterface));//写入一个默认数据
    }
    GameStatisticInterface temp;
    file.read((char *)&temp,sizeof(GameStatisticInterface));//读取数据到temp;
    return temp;
}

void Game::updateStatistic()
{
    GameStatisticInterface u = getLocalStatistic();
    if(u.maxPassLevelNumber < this->mStatistic.maxPassLevelNumber)
        u.maxPassLevelNumber = mStatistic.maxPassLevelNumber;
    if(mStatistic.alreadyKillMonsterNumber)
        u.alreadyKillMonsterNumber += mStatistic.alreadyKillMonsterNumber,mStatistic.alreadyKillMonsterNumber = 0;
    if(u.maxCombos < this->mStatistic.maxCombos)
        u.maxCombos = this->mStatistic.maxCombos;
    QString Filename = ".\\GameStatistic";    //这个路径可以根据自己的更改
    QFile file(Filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug()<<"写入Statistic发生错误！";
        exit(0);
    }
    file.write((const char*)&u,sizeof(GameStatisticInterface));//写入数据
}
