#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent):
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//设置主菜单ui界面
    this->setWindowTitle(QString("为了红王"));
    this->setFocusPolicy(Qt::StrongFocus);     //对主窗口进行强关注
    this->setFixedSize(1960,1080);             //!<设置分辨率为1960*1080

    mGame = new Game(this,this);                    //创建Game对象

}

MainWindow::~MainWindow()
{
    delete mGame;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    mGame->keyPressInput(event->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    mGame->keyReleaseInput(event->key());
}
