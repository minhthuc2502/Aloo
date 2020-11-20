#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QtWidgets>
#include <QtNetwork>
#include <QtSql>
#include <userInfo.h>
#include <database.h>

class mainWindowServer: public QWidget {
    Q_OBJECT
public:
    mainWindowServer(QWidget* pParent = 0, Qt::WindowFlags flags = 0);
    void sendMessageToUsers(const QString &message);
    void deleteUserInList(QTcpSocket *socket);
private slots:
    void newConnect();
    void disconnect();
    void receiveData();
    void receiveInfoFromUsers(QTcpSocket *clientConnection);
private:
    QLabel *stateServer;
    QLabel *numUserInfo;
    QPushButton *closeServer;
    QPushButton *showDB;

    QTcpServer *server;
    QMap<QTcpSocket *, userInfo *> users;
    database* db;
};

#endif // MAINWINDOWSERVER_H
