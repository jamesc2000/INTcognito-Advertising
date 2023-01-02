#include "mainwindow.h"
#include "databasehandler.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Databasehandler dbhandler;
    MainWindow w;
    w.show();
    return a.exec();
}
