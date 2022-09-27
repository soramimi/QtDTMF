
TARGET = QtDTMF
TEMPLATE = app
QT += core gui multimedia widgets
CONFIG += c++11

SOURCES += \
        SineCurve.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        MainWindow.h \
        SineCurve.h \
        pi2.h

FORMS += \
        MainWindow.ui
