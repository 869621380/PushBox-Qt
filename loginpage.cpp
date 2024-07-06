#include "loginpage.h"

loginPage::loginPage(QWidget *parent){
    haslogged=0;
    Q_UNUSED(parent);
    //打开当前窗口时禁止对其他窗口进行操作
    setWindowModality((Qt::ApplicationModal));
    setFixedSize(600, 300); // 设置窗口大小为固定的 600x300 像素
    setWindowIcon(QIcon(":/image/kun.png"));
    setWindowTitle("账号登录");
    //设置登录页面
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    //登录注册栏
    QHBoxLayout*idLayout=new QHBoxLayout;
    QLabel *idLabel = new QLabel("登录/注册: ");
    idLayout->addWidget(idLabel);
    idLineEdit=new QLineEdit;
    idLayout->addWidget(idLineEdit);
    mainLayout->addLayout(idLayout);
    //密码栏
    QHBoxLayout*passwordLayout=new QHBoxLayout;
    QLabel *passwordLabel = new QLabel("     密码: ");
    passwordLayout->addWidget(passwordLabel);
    passwordLineEdit=new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLineEdit);
    mainLayout->addLayout(passwordLayout);
    //登录/注册按钮
    QHBoxLayout*buttonLayout=new QHBoxLayout;
    QPushButton*loginBtn=new QPushButton;
    loginBtn->setParent(this);
    loginBtn->setText("登录");
    buttonLayout->addWidget(loginBtn);
    QPushButton*registerBtn=new QPushButton;
    registerBtn->setParent(this);
    registerBtn->setText("注册");
    buttonLayout->addWidget(registerBtn);
    mainLayout->addLayout(buttonLayout);

    connect(loginBtn, &QPushButton::clicked, this, &loginPage::inspect);
    connect(registerBtn, &QPushButton::clicked, this, &loginPage::registerAccount);
}

//检查数据库有无此账号
void loginPage::inspect(){ 
    QString id=QString(idLineEdit->text().trimmed());
    QString password=QString(passwordLineEdit->text().trimmed());
    if(!id.isEmpty()&&!password.isEmpty()){
    if(db.selecting(id,password)){
        haslogged=true;
    }
    else{
        QLabel*msg=new QLabel(this);
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::red);
        msg->setPalette(palette);
        msg->resize(150,50);
        msg->setText("账号或密码错误");
        msg->move(60,160);
        msg->show();
        QTimer::singleShot(3000, msg, &QWidget::deleteLater);
    }
   }
   if(hasLogged()){
       theId=id;
       this->close();
   }
}

//账号注册
void loginPage::registerAccount(){
    QString id=QString(idLineEdit->text().trimmed());
    QString password=QString(passwordLineEdit->text().trimmed());
    if(!id.isEmpty()&&!password.isEmpty()){
    if(db.inserting(id,password)){
        haslogged=true;
        QLabel*msg=new QLabel(this);
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::red);
        msg->setPalette(palette);
        msg->resize(150,50);
        msg->setText("注册成功");
        msg->move(60,160);
        msg->show();
        QTimer::singleShot(3000, msg, &QWidget::deleteLater);
    }
    else{
        QLabel*msg=new QLabel(this);
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::red);
        msg->setPalette(palette);
        msg->resize(150,50);
        msg->setText("账号已存在");
        msg->move(60,160);
        msg->show();
        QTimer::singleShot(3000, msg, &QWidget::deleteLater);
    }
   }
}

//检测是否登录
bool loginPage::hasLogged(){
    return haslogged;
}

//获取账号id
QString loginPage::getId(){
    return theId;
}

//退出登录
void loginPage::logOut(){
    haslogged=false;
}
