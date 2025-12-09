#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // application Qt
    MainWindow w;               // création widget
    w.show();                   // affichage widget
    return a.exec();            // lancement boucle gestion événement
}
