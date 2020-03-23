include(../defaults.pri)

QT -= qt core gui

CONFIG   -= app_bundle
CONFIG += c++14 console

LIBS +=  -lGL -lSDL2 -lGLEW

INCLUDEPATH += $$PWD

LIBS += -L../src -lKitsunemimiOpengl

SOURCES += \
    main.cpp
