#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QtWidgets>
#include <QtNetwork>
#include <userInfo.h>

class mainWindowServer: public QWidget {
    Q_OBJECT
public:
    mainWindowServer();
    void sendMessageToUsers(const QString &message);
    void deleteUserInList(QTcpSocket *socket);
private slots:
    void newConnect();
    void disconnect();
    void receiveData();
    void receiveInfoFromUsers(userInfo *clientConnection);
private:
    QLabel *stateServer;
    QLabel *numUserInfo;
    QPushButton *closeServer;

    QTcpServer *server;
    QList<userInfo *> users;
    quint16 size;
};

#endif // MAINWINDOWSERVER_H
