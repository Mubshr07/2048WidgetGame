#include "mainwindow.h"

#include <QApplication>
#include <QIODevice>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Load an application style
    QFile styleFile( ":/Irrorater.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    a.setStyleSheet( style );


    w.show();
    return a.exec();
}
