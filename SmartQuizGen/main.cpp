
#include <QApplication>
#include <QCoreApplication>
#include "mainwindow.h"
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DataBaseManager::openDatabase();
    MainWindow w;
    w.show();


    return a.exec();
}
