TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tcalc.cpp \
    toperators.cpp \
    Ttoken.cpp

HEADERS += \
    tcalc.h \
    toperators.h \
    Ttoken.h \
    toperand.h \
    tbracket.h
