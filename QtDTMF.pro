
TARGET = QtDTMF
TEMPLATE = app
QT += core gui multimedia widgets
CONFIG += c++11

SOURCES += \
        Generator.cpp \
        MyAudioOutput5.cpp \
        SineCurve.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        Generator.h \
        MainWindow.h \
        MyAudioOutput5.h \
        SineCurve.h \
        pi2.h

FORMS += \
        MainWindow.ui
