
TARGET = QtDTMF
TEMPLATE = app
QT += core gui multimedia widgets
CONFIG += c++11

SOURCES += \
        Generator.cpp \
        SineCurve.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        Generator.h \
        MainWindow.h \
		SineCurve.h \
		pi2.h

FORMS += \
        MainWindow.ui
