#ifndef USERINFO_H
#define USERINFO_H

#include <stdio.h>
#include <QtWidgets>
#include <QtNetwork>
class userInfo {
public:
    userInfo();
    void setNickName(QString name);
    void setAge(int a);
    void setSocketId(QTcpSocket *socket);
    void setAvatar(QPixmap ava);

    QTcpSocket* getSocketId();
    QString getNickName();
    QPixmap getAvatar();
    int getAge();

    //bool operator==(const userInfo &user) const;
private:
    QString nickName;
    int age;
    QTcpSocket *idSocket;
    QPixmap avatar;
};

#endif // USERINFO_H
