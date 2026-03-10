#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!dbmanager::connect("localhost", 5432, "localdb", "postgres", "1234")){
    QMessageBox::critical(nullptr, "Error", "Neuspesna konekcija so bazata");
        return 0;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
