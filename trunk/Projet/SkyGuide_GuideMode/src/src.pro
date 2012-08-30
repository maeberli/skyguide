QT       += core
QT       -= gui

OBJECTS_DIR = obj
MOC_DIR = moc
INCLUDEPATH += ../lib/libqserialdevice/qserialdevice/

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
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
    CalculatorImpl/vectoroperations.cpp \
    guidemodehandler.cpp \
    applicationcontroler.cpp

HEADERS += \
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
    CalculatorImpl/vectoroperations.h \
    guidemodehandler.h \
    applicationcontroler.h


CONFIG(debug, debug|release) {
    QMAKE_LIBDIR += ../lib/libqserialdevice/build/debug
    LIBS += -lqserialdeviced
    DESTDIR = debug
    TARGET = SkyGuide_GuideModeDebug
} else {
    QMAKE_LIBDIR += ../lib/libqserialdevice/build/release
    LIBS += -lqserialdevice
    DESTDIR = release
    TARGET = SkyGuide_GuideMode
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
