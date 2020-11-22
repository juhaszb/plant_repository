#include "plantapp.h"
#include "api_server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    api_server api;
    api.exec();
    PlantApp w(api.ip, api.port);
    w.show();
    return a.exec();
}
