#ifndef DARABASE_H
#define DARABASE_H
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlDatabase>
#include<QDebug>
#include<QtSql>
class DataBase{
public:
    DataBase();
    void createDataBase();//创建数据库

    bool selecting(QString id,QString password);//查找账户密码是否匹配
    bool inserting(QString id,QString password);//添加账户

    int selecting(QString id);//查询当前id最大通关数
    bool updateLevel(QString id, int newLevel); //更新该账户的最大通关数
    int getLastStep(int level);//获取当前关卡所用步数最多的用户的步数
    bool deleteLastRecord(int level); //删除当前关卡当前关卡所用步数最多的用户的步数
    int getTotalCount(int level);//查询当前关卡进入排行榜的总人数
    void sortRecords(int level);//对相同关卡的人根据步数多少进行升序稳定排序
    bool inserting(QString ids,int level,int step);//插入新的排行榜数据或更新原在榜人的数据
    bool judgeInRankList(QString id,int level);//判断此账户在此关卡是否在榜；
    QVector<QString> findUserId(int level);//对当前关卡排行榜上所有账号名称进行查询
    QVector<int> findUserStep(int level);//对当前关卡排行榜上所有账号最小步数进行查询

private:
    QSqlDatabase db;
};

#endif // DARABASE_H
