#include "plantapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlantApp w;
    w.show();
    return a.exec();
}
