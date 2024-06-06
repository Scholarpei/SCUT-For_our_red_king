#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "interface.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QPainter* mPainter;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showStatisticWidget();//数据统计界面
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent* e);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_staBackButton_clicked();

    void on_staBackMainLevelButton_clicked();

private:
    Ui::MainWindow *ui;
    class Game* mGame;

};
#endif // MAINWINDOW_H
