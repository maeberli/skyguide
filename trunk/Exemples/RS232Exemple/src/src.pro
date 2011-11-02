#-------------------------------------------------
#
# Project created by QtCreator 2011-10-26T11:24:14
#
#-------------------------------------------------

QT       += core gui

TARGET = RS232Exemple
TEMPLATE = app
OBJECTS_DIR = obj
MOC_DIR = moc
INCLUDEPATH += ../libqserialdevice/qserialdevice/
INCLUDEPATH += ../libqserialdevice/qserialdeviceenumerator/


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release) {
    QMAKE_LIBDIR += ../libqserialdevice/build/debug
    LIBS += -lqserialdeviced
    DESTDIR = debug
    TARGET = RS232Exempled
} else {
    QMAKE_LIBDIR += ../libqserialdevice/build/release
    LIBS += -lqserialdevice
    DESTDIR = release
    TARGET = RS232Exempled
}


win32 {
    LIBS += -lsetupapi -luuid -ladvapi32
}
unix:!macx {
    LIBS += -ludev
}
macx {
    LIBS += -framework IOKit -framework CoreFoundation
}
