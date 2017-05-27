TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ttranslator.cpp \
    tru_en.cpp \
    ten_ru.cpp \
    ten_de.cpp \
    tde_en.cpp

HEADERS += \
    ttranslator.h \
    tru_en.h \
    ten_ru.h \
    ten_de.h \
    tde_en.h
