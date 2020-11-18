#include "mainWindowServer.h"

mainWindowServer::mainWindowServer() {
    stateServer = new QLabel();
    closeServer = new QPushButton(tr("close"));
    numUserInfo = new QLabel();
    connect(closeServer, SIGNAL(clicked(bool)), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(stateServer);
    layout->addWidget(numUserInfo);
    layout->addWidget(closeServer);
    setLayout(layout);
    setWindowTitle("Aloo");

    // Allocate server
    // using this -> when close window, the server will close also
    server = new QTcpServer(this);
    if (!server->listen(QHostAddress::Any, 50885)) {
        // If server can't start on this port
        stateServer->setText(tr("The server can't be started because of error: ") + server->errorString());
    } else {
        stateServer->setText(tr("The server is started on port <strong>") + QString::number(server->serverPort()) + tr("</strong>.<br>User can connect to chat"));
        numUserInfo->setText(tr("0 user in chat group"));
        connect(server, SIGNAL(newConnection()), this, SLOT(newConnect()));
    }
    size = 0;

    db = new database();
}

void mainWindowServer::newConnect() {
    sendMessageToUsers(tr("<em> A new person join with us </em>"));
    QTcpSocket *newUser = server->nextPendingConnection();
    userInfo *user = new userInfo();
    // get socket id
    user->setSocketId(newUser);
    // get avatar, name, age
    receiveInfoFromUsers(user);
    db->saveUserInfoToDB(user);
    users.append(user);

    connect(user->getSocketId(), SIGNAL(disconnected()), this, SLOT(disconnect()));
    connect(user->getSocketId(), SIGNAL(readyRead()), this, SLOT(receiveData()));
    // update number of users
    numUserInfo->setText(QString::number(users.size()) + tr(" users in chat group"));
}

void mainWindowServer::disconnect() {
    sendMessageToUsers(tr("<em> A person leaved room chat </em>"));

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) {
        return;
    }
    deleteUserInList(socket);
    socket->deleteLater(); // delete socket after slot finish
    
    // update number of users
    numUserInfo->setText(QString::number(users.size()) + tr(" users in chat group"));
}

void mainWindowServer::receiveData() {
    // slot is called each time a package of data come in socket
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) {
        return;
    }
    QDataStream in(socket);
    if (size == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }
        in >> size; // transfer 16 bits for data size to size and change reference in datastream
    }

    // when we know data size, check until we have enough data
    if (socket->bytesAvailable() < size) {
        return;
    }
    // when data in datastream came, set message
    QString msg;
    in >> msg;

    sendMessageToUsers(msg);
    // reset size of data
    size = 0;
}

void mainWindowServer::receiveInfoFromUsers(userInfo *clientConnection) {
    QByteArray array;
    quint32 sizeImage;
    // wait until get all data from client
    while (clientConnection->getSocketId()->waitForReadyRead(1000)) {
        array.append(clientConnection->getSocketId()->readAll());
    }

    /* Image processing */
    QByteArray tempArray;
    // Get size of image in array
    tempArray = array.left((int)sizeof(quint32));
    QDataStream in(&tempArray, QIODevice::ReadOnly);
    in >> sizeImage;

    // get data of image from array
    tempArray = array.mid((int)sizeof(quint32), sizeImage);
    QBuffer buffer(&tempArray);
    buffer.open(QIODevice::ReadOnly);

    // read image
    QImageReader reader(&buffer, "JPG");
    QImage img = reader.read();

    if (!img.isNull()) {
        clientConnection->setAvatar(QPixmap::fromImage(img));
    }
    else {
        qDebug() << "error" << endl;
    }

    // remove data analyzed
    array = array.mid((int)sizeof(quint32) + sizeImage, array.size() - ((int)sizeof(quint32) + sizeImage));
    tempArray = array.left((int)sizeof(quint16));
    quint16 sizeData;
    QDataStream inNameLength(&tempArray, QIODevice::ReadOnly);
    inNameLength >> sizeData;
    // get name
    tempArray = array.mid((int)sizeof(quint16), sizeData);
    QDataStream inName(&tempArray, QIODevice::ReadOnly);
    QString name;
    inName >> name;
    clientConnection->setNickName(name);

    // remove data analyzed
    array = array.mid((int)sizeof(quint16) + sizeData, array.size() - ((int)sizeof(quint16) + sizeData));
    tempArray = array.left((int)sizeof(quint16));
    QDataStream inAgeLength(&tempArray, QIODevice::ReadOnly);
    inAgeLength >> sizeData;
    // get age
    tempArray = array.right(sizeData);
    QDataStream inAge(&tempArray, QIODevice::ReadOnly);
    int age;
    inAge >> age;
    clientConnection->setAge(age);
}

void mainWindowServer::sendMessageToUsers(const QString &message) {
    QByteArray msgPackage;
    QDataStream out(&msgPackage, QIODevice::WriteOnly);

    out << (quint16) 0; // using 0 to reserve the place of data size;
    out << message;

    out.device()->seek(0);
    out << (quint16) (msgPackage.size() - sizeof(quint16));

    for (int i = 0; i < users.size() ; i++) {
        users[i]->getSocketId()->write(msgPackage);
    }
}

void mainWindowServer::deleteUserInList(QTcpSocket *socket) {
    QList<userInfo*>::iterator i;
    for (i = users.begin(); i != users.end(); i++) {
        userInfo* temp = *i;
        if (temp->getSocketId() == socket) {
            users.removeOne(temp);
            return;
        }
    }
}
