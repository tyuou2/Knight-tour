#include "mainwindow.h"
#include"horse.h"
#include <QApplication>
#include"login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/icons8_title_4.png"));
    QFile qss(":/my_sh.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    login loginDialog;
//    MainWindow w;
//    w.show();
    loginDialog.show();

    return a.exec();
}
