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
    void setAvatar(QPixmap ava);
    void setSizeMessage(quint16 size);

    QString getNickName();
    QPixmap getAvatar();
    int getAge();
    quint16 getSizeMessage();

private:
    QString nickName;
    int age;
    QPixmap avatar;
    quint16 sizeMessage;
};

#endif // USERINFO_H
