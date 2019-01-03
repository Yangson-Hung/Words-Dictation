#include "dictation.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    Dictation dictation;
    dictation.setMaximumSize(500,500);
    dictation.setWindowTitle(QObject::tr("单词听写"));
    dictation.setWindowIcon(QIcon(":/new/prefix1/ico.ico"));
    dictation.show();

    return app.exec();
}
