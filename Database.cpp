#include "Database.h"

DataBase::DataBase(){
}

//创建数据库
void DataBase::createDataBase(){
    //创建数据库
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Account.db");
    //打开数据库
    if(!db.open()){
        qDebug()<<"open error"<<db.lastError();
    }

    //创建账号密码表
    QSqlQuery query;
    QString sqlCreateTable = "CREATE TABLE IF NOT EXISTS account ("
                              "id VARCHAR(10) PRIMARY KEY, "
                             "password VARCHAR(20)"
                             ");";
    if (!query.exec(sqlCreateTable)) {
       qDebug() << "Error: Failed to create table" << query.lastError().text();
    }
    else {
       qDebug() << "Table 'account' created successfully!";
    }

    //创建排行榜表
    QSqlQuery query2;
    QString sqlCreateTable2 = "CREATE TABLE IF NOT EXISTS leaderboard ("
                             "id VARCHAR(10) PRIMARY KEY,"
                             "level INTEGER, "
                             "step INTEGER"
                             ");";

    if (!query2.exec(sqlCreateTable2)) {
       qDebug() << "Error: Failed to create table" << query2.lastError().text();
    }
    else {
       qDebug() << "Table 'leaderboard' created successfully!";
    }

    //创建账号数据表
    QSqlQuery query3;
    QString sqlCreateTable3 = "CREATE TABLE IF NOT EXISTS idData ("
                                 "id VARCHAR(10) PRIMARY KEY,"
                                 "level INTEGER"
                                 ");";
    if (!query2.exec(sqlCreateTable3)) {
       qDebug() << "Error: Failed to create table" << query3.lastError().text();
    }
    else {
       qDebug() << "Table 'idData' created successfully!";
    }
}

//查找账户密码是否匹配
bool DataBase::selecting(QString id,QString password){
    QSqlQuery query(db);
    QString queryString = QString("SELECT * FROM account WHERE id = :id AND password = :password");
    query.prepare(queryString);
    query.bindValue(":id", id);
    query.bindValue(":password", password);
    if (!query.exec()) {
          qDebug() << "Error executing query:" << query.lastError().text();
          return false;
    }
    // 如果查询到
    if (query.next()) {
          qDebug() << "Login successful for user:" << id;
          return true;
    }
    else {
          qDebug() << "Login failed for user:" << id;
          return false;
    }
}

//添加账户
bool DataBase::inserting(QString id,QString password){
      QSqlQuery query;
      // 检查账号是否已经存在
      QString checkQuery = "SELECT COUNT(*) FROM account WHERE id = :id";
      query.prepare(checkQuery);
      query.bindValue(":id", id);

      if (!query.exec()) {
          qDebug() << "Error checking account existence:" << query.lastError().text();
          return false;
      }
      if (query.next()) {
          int count = query.value(0).toInt();
          if (count > 0) {
              qDebug() << "Account with ID" << id << "already exists.";
              return false;
          }
      }
      // 如果账号不存在，则执行插入操作
      QString insertQuery = "INSERT INTO account (id, password) VALUES (:id, :password)";
      query.prepare(insertQuery);
      query.bindValue(":id", id);
      query.bindValue(":password", password);

      if (query.exec()) {
          qDebug() << "Insertion successful!";
          return true;
      } else {
          qDebug() << "Insertion failed:" << query.lastError().text();
          return false;
      }
}

//查询当前id最大通关数
int DataBase::selecting(QString id){
    QSqlQuery query;
    QString idToFind = id;
    QString sqlSelect = "SELECT level FROM idData WHERE id = :id";
    query.prepare(sqlSelect);
    query.bindValue(":id", idToFind);
    if (query.exec()) {
        if (query.next()) {
            int level = query.value(0).toInt();
            qDebug() << "Level for ID" << idToFind << "is" << level;
            return level;
        }
        // 未找到该id，插入新的记录并初始化level为1
        else {
            QString sqlInsert = "INSERT INTO idData (id, level) VALUES (:id, 1)";
            query.prepare(sqlInsert);
            query.bindValue(":id", idToFind);
            if (query.exec()) {
                qDebug() << "Inserted new ID" << idToFind << "with level initialized to 1";
                return 1;
            } else {
                qDebug() << "Error inserting new ID:" << query.lastError().text();
                return -1;
            }
        }
    }
    else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    return -1;
}

//更新该账户的最大通关数
bool DataBase::updateLevel(QString id, int newLevel) {
    QSqlQuery query;
    QString sqlUpdate = "UPDATE idData SET level = :newLevel WHERE id = :id";
    query.prepare(sqlUpdate);
    query.bindValue(":newLevel", newLevel);
    query.bindValue(":id", id);
    if (query.exec()) {
        qDebug() << "Updated level for ID" << id << "to" << newLevel;
        return true;
    }
    else {
        qDebug() << "Error updating level for ID" << id << ":" << query.lastError().text();
        return false;
    }
}

















