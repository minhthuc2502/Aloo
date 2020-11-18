#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <userInfo.h>

class database {
private:
    QSqlDatabase sqlDB;
public:
    database();
    void saveUserInfoToDB(userInfo *clientConnection);
};

#endif // DATABASE_H
