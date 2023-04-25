
#include <QCoreApplication>
#include "Server.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    server.run();
    return 0;

    return a.exec();
}
