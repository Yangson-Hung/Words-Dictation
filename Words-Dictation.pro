#-------------------------------------------------
#
# Project created by QtCreator 2018-12-30T17:57:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Words-Dictation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    dictation.cpp

HEADERS += \
    dictation.h \
    tts/msp_cmn.h \
    tts/msp_errors.h \
    tts/msp_types.h \
    tts/qise.h \
    tts/qisr.h \
    tts/qtts.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc


win32: LIBS += -L$$PWD/libs/ -lmsc_x64

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/msc_x64.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libmsc_x64.a
