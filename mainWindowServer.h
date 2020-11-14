#ifndef MAINWINDOWSERVER_H
#define MAINWINDOWSERVER_H

#include <QtWidgets>
#include <QtNetwork>

class mainWindowServer: public QWidget {
    Q_OBJECT
public:
    mainWindowServer();
    void sendMessageToUsers(const QString &message);
private slots:
    void newConnect();
    void disconnect();
    void receiveData();
private:
    QLabel *stateServer;
    QLabel *numUserInfo;
    QPushButton *closeServer;

    QTcpServer *server;
    QList<QTcpSocket *> users;
    quint16 size;
};

#endif // MAINWINDOWSERVER_H
