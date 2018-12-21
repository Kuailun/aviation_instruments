#-------------------------------------------------
#
# Project created by QtCreator 2018-05-22T23:24:57
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
                                  QT += network

TARGET = aviation_instruments
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


SOURCES += \
    src/configuration.cpp \
    src/datastruct.cpp \
    src/instrument.cpp \
    src/instrumentwindow.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/printlog.cpp \
    src/xmlcontrol.cpp \
    src/msocket.cpp

HEADERS += \
    include/configuration.h \
    include/datastruct.h \
    include/instrument.h \
    include/instrumentwindow.h \
    include/mainwindow.h \
    include/printlog.h \
    include/xmlcontrol.h \
    include/msocket.h

FORMS += \
    ui/configuration.ui \
    ui/instrumentwindow.ui \
    ui/mainwindow.ui \
    ui/msocket.ui

RESOURCES += \
    resource/resource.qrc
