#include "abbreviation.h"
#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Abbreviation w;


    w.show();

    return a.exec();
}
