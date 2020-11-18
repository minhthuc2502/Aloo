#include <database.h>

database::database() {
    // setup database
    // lib for mysql driver libqt5sql5-mysql
    sqlDB = QSqlDatabase::addDatabase("QMYSQL");
    sqlDB.setHostName("127.0.0.1");
    sqlDB.setUserName("root");
    sqlDB.setPassword("Minhthuc123");
    sqlDB.setDatabaseName("usersInfoDB");
}

void database::saveUserInfoToDB(userInfo *clientConnection) {
    sqlDB.open();

    QByteArray array;

    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);

    clientConnection->getAvatar().save(&buffer, "jpg");

    // save image to database
    QSqlQuery query = QSqlQuery();
    query.prepare("INSERT INTO information (filename, image, name, age) VALUES ('avatar-" + clientConnection->getNickName() + ".jpg', :imageData, :Name, :Age)");
    query.bindValue(":imageData", array);
    query.bindValue(":Name", clientConnection->getNickName());
    query.bindValue(":Age", clientConnection->getAge());
    if (!query.exec())
        qDebug() << "Error inserting image into table:\n" << query.lastError();
    sqlDB.close();
}

