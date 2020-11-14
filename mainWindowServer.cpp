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
}

void mainWindowServer::newConnect() {
    sendMessageToUsers(tr("<em> A new person join with us </em>"));
    QTcpSocket *newUser = server->nextPendingConnection();
    users.append(newUser);

    connect(newUser, SIGNAL(disconnected()), this, SLOT(disconnect()));
    connect(newUser, SIGNAL(readyRead()), this, SLOT(receiveData()));
    // update number of users
    numUserInfo->setText(QString::number(users.size()) + tr(" users in chat group"));
}

void mainWindowServer::disconnect() {
    sendMessageToUsers(tr("<em> A person leaved room chat </em>"));

    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) {
        return;
    }
    users.removeOne(socket);
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

void mainWindowServer::sendMessageToUsers(const QString &message) {
    QByteArray msgPackage;
    QDataStream out(&msgPackage, QIODevice::WriteOnly);

    out << (quint16) 0; // using 0 to reserve the place of data size;
    out << message;

    out.device()->seek(0);
    out << (quint16) (msgPackage.size() - sizeof(quint16));

    for (int i = 0; i < users.size() ; i++) {
        users[i]->write(msgPackage);
    }
}
