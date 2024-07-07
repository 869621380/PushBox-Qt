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
                             "id VARCHAR(10),"
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
                                 "id VARCHAR(10),"
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
            }
            else {
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

//获取当前关卡所用步数最多的用户的步数
int DataBase::getLastStep(int level) {
    QSqlQuery query(db);
    query.prepare("SELECT step FROM leaderboard WHERE level = :level ORDER BY id DESC LIMIT 1");
    query.bindValue(":level", level);
    if (query.exec() && query.next()) {
        int lastStep = query.value(0).toInt();
        return lastStep;
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
        return -1;  // 返回一个错误标志，或者根据需要返回适当的默认值
    }
}

//删除当前关卡当前关卡所用步数最多的用户的步数
bool DataBase::deleteLastRecord(int level) {
    QSqlQuery querySelect(db);
    querySelect.prepare("SELECT id FROM leaderboard WHERE level = :level ORDER BY id DESC LIMIT 1");
    querySelect.bindValue(":level", level);
    if (!querySelect.exec() || !querySelect.next()) {
        qDebug() << "Select query failed:" << querySelect.lastError().text();
        return false;
    }
    int idToDelete = querySelect.value(0).toInt();
    QSqlQuery queryDelete(db);
    queryDelete.prepare("DELETE FROM leaderboard WHERE id = :id");
    queryDelete.bindValue(":id", idToDelete);
    if (!queryDelete.exec()) {
        qDebug() << "Delete query failed:" << queryDelete.lastError().text();
        return false;
    }
    return true;  // 删除成功
}

//查询当前关卡进入排行榜的总人数
int DataBase::getTotalCount(int level) {
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM leaderboard WHERE level = :level");
    query.bindValue(":level", level);
    if (query.exec() && query.next()) {
        int totalCount = query.value(0).toInt();
        return totalCount;
    }
    else {
        qDebug() << "Query failed:" << query.lastError().text();
        return -1;
    }
}

void DataBase::sortRecords(int level) {
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();

    // 查询指定 level 的记录
    QSqlQuery query;
    query.prepare("SELECT id, step FROM leaderboard WHERE level = :level ORDER BY step ASC");
    query.bindValue(":level", level);
    query.exec();

    std::vector<std::pair<int, int>> records;
    while (query.next()) {
        records.emplace_back(query.value("id").toInt(), query.value("step").toInt());
    }
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM leaderboard WHERE level = :level");
    deleteQuery.bindValue(":level", level);
    if (!deleteQuery.exec()) {
        db.rollback();
        qCritical() << "Failed to delete leaderboard records: " << deleteQuery.lastError().text();
        return;
    }
    std::sort(records.begin(), records.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    });
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO leaderboard (id, step, level) VALUES (:id, :step, :level)");
    for (const auto& pair : records) {
        insertQuery.bindValue(":id", pair.first);
        insertQuery.bindValue(":step", pair.second);
        insertQuery.bindValue(":level", level);
        if (!insertQuery.exec()) {
            db.rollback();
            qCritical() << "Failed to insert leaderboard record: " << insertQuery.lastError().text();
            return;
        }
    }
    db.commit();
}

//插入新的排行榜数据或更新原在榜人的数据
bool DataBase::inserting(QString id, int level, int step) {
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT step FROM leaderboard WHERE id = :id AND level = :level");
    checkQuery.bindValue(":id", id);
    checkQuery.bindValue(":level", level);
    if (!checkQuery.exec()) {
        qDebug() << "Check query failed:" << checkQuery.lastError().text();
        return false;
    }
    if (checkQuery.next()) {
        int existingStep = checkQuery.value(0).toInt();
        if (step >= existingStep) {
            qDebug() << "No update needed, current step (" << step << ") is not less than existing step (" << existingStep << ")";
            return true;
        }
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE leaderboard SET step = :step WHERE id = :id AND level = :level");
        updateQuery.bindValue(":step", step);
        updateQuery.bindValue(":id", id);
        updateQuery.bindValue(":level", level);
        if (!updateQuery.exec()) {
            qDebug() << "Update failed:" << updateQuery.lastError().text();
            return false;
        }
    }
    else {
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO leaderboard (id, level, step) VALUES (:id, :level, :step)");
        insertQuery.bindValue(":id", id);
        insertQuery.bindValue(":level", level);
        insertQuery.bindValue(":step", step);
        if (!insertQuery.exec()) {
            qDebug() << "Insert failed:" << insertQuery.lastError().text();
            return false;
        }
    }
    return true;
}

//判断此账户在此关卡是否在榜；
bool DataBase::judgeInRankList(QString id,int level){
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT step FROM leaderboard WHERE id = :id AND level = :level");
    checkQuery.bindValue(":id", id);
    checkQuery.bindValue(":level", level);
    if (!checkQuery.exec()) {
        qDebug() << "Check query failed:" << checkQuery.lastError().text();
        return false;
    }
    if (checkQuery.next()){
        return  true;
    }
    else return false;
}


