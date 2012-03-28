#-------------------------------------------------
#
# Project created by QtCreator 2012-02-29T09:05:42
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SkyGuide
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


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
    skyextdevdatahandler.cpp

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
    skyextdevdatahandler.h
