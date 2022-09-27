
TARGET = QtDTMF
TEMPLATE = app
QT += core gui multimedia widgets
CONFIG += c++11

SOURCES += \
        Generator.cpp \
        MyAudioOutput6.cpp \
        SineCurve.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
        Generator.h \
        MainWindow.h \
	MyAudioOutput6.h \
		SineCurve.h \
		pi2.h

FORMS += \
        MainWindow.ui
