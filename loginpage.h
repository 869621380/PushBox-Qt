#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include"Database.h"
#include<QPaintEvent>
#include<QPushButton>
#include<QVBoxLayout>
#include<QLineEdit>
#include <QObject>
#include<QPainter>
#include<QWidget>
#include<QDebug>
#include<QTimer>
#include<QLabel>

class loginPage: public QWidget{

public:
    loginPage(QWidget *parent);
    bool hasLogged();//检测是否登录
    void logOut();//退出登录
    QString getId();//获取账号id

public slots:
    void inspect();//检查数据库有无此账号
    void registerAccount();//注册账号

private:
    QLineEdit *idLineEdit;//id文本框
    QLineEdit *passwordLineEdit;//密码文本框
    QPushButton *loginButton;//登录按钮
    QString theId;//账户id
    QString password;//密码
    DataBase db;//数据库
    bool  haslogged;//是否登录


};

#endif // LOGINPAGE_H
