#include "warningbox.h"
#include <QtWinExtras>

WarningBox::WarningBox()
{
    if (QOperatingSystemVersion::current() < QOperatingSystemVersion::Windows8) {
        if (QtWin::isCompositionEnabled()) {
            QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
            setAttribute(Qt::WA_TranslucentBackground, true);
            setStyleSheet(QStringLiteral("warningbox { background: transparent; }"));
        } else {
            QtWin::resetExtendedFrame(this);
            setAttribute(Qt::WA_TranslucentBackground, false);
            setStyleSheet(QStringLiteral("warningbox { background: %1; }").arg(QtWin::realColorizationColor().name()));
        }
    }
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);

}
