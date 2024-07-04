#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<data.h>
#include<QStack>
#include<QPair>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initialize(int level);//资源初始化
    void paintEvent(QPaintEvent *);//图片资源渲染
    void button();
    void keyReleaseEvent(QKeyEvent*event);
    void checkWin();
    void winMessage();
private:
    Ui::MainWindow *ui;
    int level;//当前关卡
    int initialData[16][16];//初始地图资源
    int currentData[16][16];//当前地图资源
    bool result;//是否达成胜利条件
    int person_x;//人物坐标
    int person_y;
    int moveTimes;//移动次数
    class data config;
    int currentMax;//当前已解锁的最高关卡
    QStack<QPair<int,QVector<int>>>opData;

};
#endif // MAINWINDOW_H
