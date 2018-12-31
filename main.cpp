#include "dictation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dictation d;
    d.show();

    return a.exec();
}
