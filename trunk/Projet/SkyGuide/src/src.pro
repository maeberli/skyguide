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

RC_FILE += icon.rc


SOURCES += main.cpp \
    skycore.cpp \
    skylogger.cpp \
    skydatabase.cpp \
    skyelement.cpp \
    skycalculator.cpp \
    skyguielement.cpp \
    skyexternaldevice.cpp \
    skycomponent.cpp \
    skygui.cpp \
    skyconfiguration.cpp \
    ExternalDeviceImpl/command.cpp \
    ExternalDeviceImpl/cmdpointermode.cpp \
    ExternalDeviceImpl/cmdping.cpp \
    ExternalDeviceImpl/cmdguidemode.cpp \
    ExternalDeviceImpl/cmdgps.cpp \
    ExternalDeviceImpl/cmdaccelerometer.cpp \
    ExternalDeviceImpl/cmdmagnetometer.cpp \
    ExternalDeviceImpl/cmdpicstatus.cpp \
    ExternalDeviceImpl/cmdunknown.cpp \
    ExternalDeviceImpl/starpointercommunication.cpp \
    GuiImpl/mainwindow.cpp \
    GuiImpl/skystarfield.cpp \
    skyposition.cpp \
    skytransformation.cpp \
    CalculatorImpl/vectoroperations.cpp

HEADERS += \
    skycore.h \
    skylogger.h \
    skyloggertypes.h \
    skycomponent.h \
    skydatabase.h \
    skyelement.h \
    skycalculator.h \
    skyguielement.h \
    skyexternaldevice.h \
    skygui.h \
    skyconfiguration.h \
    ExternalDeviceImpl/command.h \
    ExternalDeviceImpl/cmdpointermode.h \
    ExternalDeviceImpl/cmdping.h \
    ExternalDeviceImpl/cmdguidemode.h \
    ExternalDeviceImpl/cmdgps.h \
    ExternalDeviceImpl/cmdaccelerometer.h \
    ExternalDeviceImpl/cmdmagnetometer.h \
    ExternalDeviceImpl/cmdpicstatus.h \
    ExternalDeviceImpl/cmdunknown.h \
    ExternalDeviceImpl/starpointercommunication.h \
    GuiImpl/mainwindow.h \
    GuiImpl/skystarfield.h \
    skyposition.h \
    skytransformation.h \
    CalculatorImpl/vectoroperations.h


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


