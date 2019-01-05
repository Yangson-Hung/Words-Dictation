QT  += core gui winextras


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Words-Dictation
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
    dictation.cpp \
    tts.cpp \
    getaudiothread.cpp \
    warningbox.cpp

HEADERS += \
    dictation.h \
    tts/msp_cmn.h \
    tts/msp_errors.h \
    tts/msp_types.h \
    tts/qtts.h \
    tts.h \
    getaudiothread.h \
    warningbox.h

RC_ICONS = images/logo.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32: LIBS += -L$$PWD/libs/ -lmsc_x64 -L$$PWD/libs/ -lmsc

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/msc_x64.lib $$PWD/libs/msc.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libmsc_x64.a $$PWD/libs/libmsc.a
