#include "userInfo.h"

userInfo::userInfo() {
    nickName = "";
    age = 0;
    idSocket = NULL;
}

void userInfo::setNickName(QString name) {
    nickName = name;
}

void userInfo::setAge(int a) {
    age = a;
}

void userInfo::setSocketId(QTcpSocket *socket) {
    idSocket = socket;
}

void userInfo::setAvatar(QPixmap ava) {
    avatar = ava;
}

QTcpSocket* userInfo::getSocketId() {
    return idSocket;
}

QString userInfo::getNickName() {
    return nickName;
}

QPixmap userInfo::getAvatar() {
    return avatar;
}

int userInfo::getAge() {
    return age;
}

//bool userInfo::operator ==(userInfo &user) {
//    return (idSocket == user.getSocketId());
//}
