#include "mainwindow.h"
#include <QApplication>
#pragma execution_character_set("UTF-8")
#include <QTextCodec>
int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    QTextCodec *gbk = QTextCodec::codecForName("gbk");
    QTextCodec::setCodecForLocale(gbk);
    Login log;
    if (!createConnection())
        return 1;
    MainWindow w;
    if(log.exec() == QDialog::Accepted)
        w.show();


    return a.exec();
}
