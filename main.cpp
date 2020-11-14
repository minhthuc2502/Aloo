#include "mainWindowServer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    mainWindowServer m_server;
    m_server.show();
    return app.exec();
}
