TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../stack/stack.cpp

HEADERS += \
    ../stack/stack.h

SUBDIRS += \
    ../stack/stack.pro

