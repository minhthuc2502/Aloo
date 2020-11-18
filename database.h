#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QWidget>
#include <userInfo.h>

class database : public QWidget {
    Q_OBJECT
private:
    QSqlDatabase sqlDB;
public slots:
    void showDatabase();
public:
    database();
    void saveUserInfoToDB(userInfo *clientConnection);
};

#endif // DATABASE_H
