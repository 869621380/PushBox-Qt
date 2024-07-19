#ifndef BEGINPAGE_H
#define BEGINPAGE_H

#include"Database.h"
#include"loginpage.h"
#include"mainwindow.h"
#include"ranklistpage.h"
#include"freemodelPage.h"
#include<QMediaPlayer>
#include<QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class beginPage; }
QT_END_NAMESPACE

class beginPage : public QWidget{
    Q_OBJECT

public:
    beginPage(QWidget *parent = nullptr);
    ~beginPage();
    void button();//按钮
    void paintEvent(QPaintEvent *);//背景图片渲染

public slots:

    void showLoginPage();//登录页面显示
    void onStateChanged(QMediaPlayer::State state);//音乐结束时重新播放

private:
    void basicButton();//经典模式按钮
    void loginButton();//账号登录按钮
    void logOutButton();//退出登录按钮
    void rankListButton();//排行榜按钮
    void freeModeButton();//自主设计模式按钮
    QPushButton*loginBtn;//点击登录按钮
    QPushButton*basicBtn;//开始游戏按钮
    QPushButton*logOutBtn;//登出按钮
    QPushButton*rankListBtn;//排行榜按钮
    QPushButton*freeModeBtn;//自主设计模式按钮
    class::loginPage*login;//登录界面
    class::rankListPage*ranklist;//排行榜界面
    MainWindow*m;//游戏页面
    freeModelPage*freeModel;//自由模式页面
    class::DataBase db;//数据库  
    QMediaPlayer* player;//音乐播放器
};

#endif // BEGINPAGE_H
