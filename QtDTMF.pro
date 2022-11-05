
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
        Audio.cpp \
        Generator.cpp \
        SineCurve.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
		Audio.h \
		AudioAbstractIO.h \
		SineCurve.h \
		Generator.h \
		MainWindow.h \
		pi2.h

FORMS += \
        MainWindow.ui

qt5 {
SOURCES += \
	AudioInputQt5.cpp \
	AudioOutputQt5.cpp
HEADERS += \
	AudioInputQt5.h \
	AudioOutputQt5.h
}

qt6 {
SOURCES += \
	AudioInputQt6.cpp \
	AudioOutputQt6.cpp
HEADERS += \
	AudioInputQt6.h \
	AudioOutputQt6.h
}
