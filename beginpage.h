#ifndef BEGINPAGE_H
#define BEGINPAGE_H

#include <QMessageBox>
#include"mainwindow.h"
#include"loginpage.h"
#include"Database.h"

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

private:
    void basicButton();//经典模式按钮
    void loginButton();//账号登录按钮
    void logOutButton();//退出登录按钮
    QPushButton*loginBtn;//点击登录按钮
    QPushButton*basicBtn;//开始游戏按钮
    QPushButton *logOutBtn;//登出按钮
    class::loginPage*login;//登录界面
    class::DataBase db;//数据库
    MainWindow*m;//游戏页面
};

#endif // BEGINPAGE_H
