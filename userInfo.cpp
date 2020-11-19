#include "userInfo.h"

userInfo::userInfo() {
    nickName = "";
    age = 0;
    sizeMessage = 0;
}

void userInfo::setNickName(QString name) {
    nickName = name;
}

void userInfo::setAge(int a) {
    age = a;
}

void userInfo::setSizeMessage(quint16 size) {
    sizeMessage = size;
}

void userInfo::setAvatar(QPixmap ava) {
    avatar = ava;
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

quint16 userInfo::getSizeMessage() {
    return sizeMessage;
}
