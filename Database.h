#ifndef DARABASE_H
#define DARABASE_H
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QDebug>
class DataBase
{
public:
    DataBase();
    void createDataBase();//创建数据库
    bool selecting(QString id,QString password);//查找账户密码是否匹配
    bool inserting(QString id,QString password);//添加账户
    int selecting(QString id);//查询当前id最大通关数
    bool updateLevel(QString id, int newLevel); //更新该账户的最大通关数
private:
    QSqlDatabase db;
};

#endif // DARABASE_H
