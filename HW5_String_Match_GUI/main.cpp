#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // if you are not a mac user
    // do not apply the following codes

    /*QString pathApp = QCoreApplication::applicationDirPath();
    std::string sApp = pathApp.toStdString();
    int t = sApp.find("StringMatch.app");
    sApp.resize(t - 1);
    QDir::setCurrent(QString(sApp.c_str()));*/

    return a.exec();
}
