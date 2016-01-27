#-------------------------------------------------
#
# Project created by QtCreator 2016-01-26T12:22:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatPrj
TEMPLATE = app


SOURCES += main.cpp\
        chatmainwindow.cpp \
    settingsdialog.cpp \
    profiledialog.cpp \
    broadcaster.cpp \
    peermanager.cpp \
    tcpconnection.cpp \
    tcpserver.cpp

HEADERS  += chatmainwindow.h \
    settingsdialog.h \
    profiledialog.h \
    broadcaster.h \
    peermanager.h \
    tcpconnection.h \
    tcpserver.h \
    encryption.h

FORMS    += chatmainwindow.ui \
    settingsdialog.ui \
    profiledialog.ui

RESOURCES += \
    res.qrc
