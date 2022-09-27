
TARGET = QtDTMF
TEMPLATE = app
QT += core gui multimedia widgets
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 5) {
	CONFIG += qt6
}
lessThan(QT_MAJOR_VERSION, 6) {
	CONFIG += qt5
}


SOURCES += \
        Generator.cpp \
        SineCurve.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
		SineCurve.h \
		Generator.h \
		MainWindow.h \
		pi2.h

FORMS += \
        MainWindow.ui

qt5 {
SOURCES += MyAudioOutput5.cpp
HEADERS += MyAudioOutput5.h
}

qt6 {
SOURCES += MyAudioOutput6.cpp
HEADERS += MyAudioOutput6.h
}
