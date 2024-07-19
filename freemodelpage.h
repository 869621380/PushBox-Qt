#ifndef FREEMODELTYPE_H
#define FREEMODELTYPE_H

#include"mainwindow.h"
#include"data.h"
#include<QMessageBox>
#include<QLabel>

class freeModelPage : public QWidget{
    Q_OBJECT

public:
     freeModelPage(QWidget *parent = nullptr);
     void initialize();//资源初始化
     void paintEvent(QPaintEvent *event) override;//图片渲染
     void mousePressEvent(QMouseEvent* event) override;//鼠标点击
     void fillAllButton();//未填充方块一键填充为地板
     void startButton();//关卡设计结束

private:
    bool checkRight();//检测关卡是否合理
    class data*config;//初始地图数据
    bool designCanceled;//关卡设计完毕
    int initialData[16][16];//填充结束后的初始数据
    int currentData[16][16];//当前数据
    int selected;//当前选中的方块
    QPushButton*fillAllBtn;//一件填充按钮
    QPushButton*startBtn;//游戏开始按钮
};

#endif // FREEMODELTYPE_H
