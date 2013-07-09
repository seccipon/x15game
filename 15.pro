TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    table_func.cpp \
    table.cpp \
    pathstep.cpp \
    astar.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    table_func.h \
    table_const.h \
    table.h \
    exc.h \
    pathstep.h \
    astar.h
