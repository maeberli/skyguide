#-------------------------------------------------
#
# Project created by QtCreator 2012-02-29T09:05:42
#
#-------------------------------------------------

QT       += core
QT       += gui
QT       += sql

OBJECTS_DIR = obj
MOC_DIR = moc
INCLUDEPATH += ../lib/libqserialdevice/qserialdevice/


SOURCES += main.cpp \
    skycore.cpp \
    skylogger.cpp \
    skydatabase.cpp \
    skyrange.cpp \
    skyelement.cpp \
    skycalculator.cpp \
    skyguielement.cpp \
    skyexternaldevice.cpp \
    skycomponent.cpp \
    skygui.cpp \
    skyextdevdatahandler.cpp \
    skyconfiguration.cpp \
    ExternalDeviceImpl/command.cpp \
    ExternalDeviceImpl/cmdpointermode.cpp \
    ExternalDeviceImpl/cmdping.cpp \
    ExternalDeviceImpl/cmdguidemode.cpp \
    ExternalDeviceImpl/cmdgps.cpp \
    ExternalDeviceImpl/cmdaccelerometer.cpp \
    ExternalDeviceImpl/cmdmagnetometer.cpp \
    ExternalDeviceImpl/cmdpicstatus.cpp \
    ExternalDeviceImpl/starpointerprotocol.cpp \
    # GuiImpl/SkyField.cpp \
    GuiImpl/mainwindow.cpp

HEADERS += \
    skycore.h \
    skylogger.h \
    skyloggertypes.h \
    skycomponent.h \
    skydatabase.h \
    skyrange.h \
    skyelement.h \
    skycalculator.h \
    skyguielement.h \
    skyexternaldevice.h \
    skygui.h \
    skyextdevdatahandler.h \
    skyconfiguration.h \
    ExternalDeviceImpl/command.h \
    ExternalDeviceImpl/cmdpointermode.h \
    ExternalDeviceImpl/cmdping.h \
    ExternalDeviceImpl/cmdguidemode.h \
    ExternalDeviceImpl/cmdgps.h \
    ExternalDeviceImpl/cmdaccelerometer.h \
    ExternalDeviceImpl/cmdmagnetometer.h \
    ExternalDeviceImpl/cmdpicstatus.h \
    ExternalDeviceImpl/starpointerprotocol.h \
    # GuiImpl/SkyField.h \
    GuiImpl/mainwindow.h

FORMS += \
    GuiImpl/mainwindow.ui

CONFIG(debug, debug|release) {
    QMAKE_LIBDIR += ../lib/libqserialdevice/build/debug
    LIBS += -lqserialdeviced
    DESTDIR = debug
    TARGET = SkyGuideDebug
} else {
    QMAKE_LIBDIR += ../lib/libqserialdevice/build/release
    LIBS += -lqserialdevice
    DESTDIR = release
    TARGET = SkyGuide
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


