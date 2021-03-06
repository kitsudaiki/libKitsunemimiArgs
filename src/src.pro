QT -= qt core gui

TARGET = KitsunemimiArgs
TEMPLATE = lib
CONFIG += c++14
VERSION = 0.2.1

LIBS += -L../../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../../libKitsunemimiCommon/include

LIBS += -L../../libKitsunemimiPersistence/src -lKitsunemimiPersistence
LIBS += -L../../libKitsunemimiPersistence/src/debug -lKitsunemimiPersistence
LIBS += -L../../libKitsunemimiPersistence/src/release -lKitsunemimiPersistence
INCLUDEPATH += ../../libKitsunemimiPersistence/include


LIBS +=  -lboost_filesystem -lboost_system

INCLUDEPATH += $$PWD \
               $$PWD/../include

HEADERS += \
    ../include/libKitsunemimiArgs/arg_parser.h \
    sub_command_entry.h \
    ../include/libKitsunemimiArgs/sub_command.h

SOURCES += \
    arg_parser.cpp \
    sub_command_entry.cpp \
    sub_command.cpp

