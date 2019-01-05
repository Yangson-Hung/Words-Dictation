#include "dictation.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QObject::tr("单词听写"));
    QGuiApplication::setApplicationDisplayName(QObject::tr("单词听写"));

    Dictation dictation;
    dictation.setMaximumSize(200,100);
    dictation.show();

    return app.exec();
}
