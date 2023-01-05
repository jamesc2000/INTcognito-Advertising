#include "mainwindow.h"
#include "databasehandler.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Databasehandler dbhandler;
//    dbhandler.testWrite();
//    dbhandler.uploadAd("test", {"test"}, {"test"}, "test");
    MainWindow w;
    w.show();
    return a.exec();
}
