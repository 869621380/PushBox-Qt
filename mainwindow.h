#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MAX_LEVEL 3//最大关卡数
#define MIN_LEVEL 1//最小关卡数

#include<QMainWindow>
#include<QPushButton>
#include<QMessageBox>
#include"Database.h"
#include<QKeyEvent>
#include"QPainter"
#include"button.h"
#include<QString>
#include"data.h"
#include<QStack>
#include<QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr,QString id=nullptr);
    ~MainWindow();
    void initialize(int level);//资源初始化
    void paintEvent(QPaintEvent *);//图片资源渲染
    void keyReleaseEvent(QKeyEvent*event);//键盘案件响应
    void button();//侧边按钮
    void checkWin();//检查游戏胜利
    void winMessage();//胜利消息弹窗

private:
    Ui::MainWindow *ui;
    QStack<QPair<int,QVector<int>>>operationData;//角色操作移动数据
    int initialData[16][16];//初始地图资源
    int currentData[16][16];//当前地图资源
    int currentMax;//当前已解锁的最高关卡
    class data config;//地图初始资源
    bool result;//是否达成胜利条件
    bool updateRank;
    int person_x;//人物x坐标
    int person_y;//人物y坐标
    int moveTimes;//移动次数
    int level;//当前关卡
    DataBase db;//数据库
    QString id;//账户id
};

#endif // MAINWINDOW_H
