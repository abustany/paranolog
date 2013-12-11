TEMPLATE = app
TARGET = paranolog
DEPENDPATH += . src
INCLUDEPATH += . src

QT += gui sql

# Input
HEADERS += \
	src/logwindow.h \
	src/nagwindow.h \
	src/paranolog.h \
	src/settings.h \
	src/settingswindow.h \
	src/statusicon.h \
	src/utils.h \
	src/workdb.h

SOURCES += \
	src/logwindow.cpp \
	src/main.cpp \
	src/nagwindow.cpp \
	src/paranolog.cpp \
	src/settings.cpp \
	src/settingswindow.cpp \
	src/statusicon.cpp \
	src/utils.cpp \
	src/workdb.cpp

RESOURCES += paranolog.qrc

QMAKE_INFO_PLIST = paranolog.plist
ICON = icons/paranolog.icns

icns.depends = icons/tomato.svg
icns.commands = ./icons/generate_osx_icons.rb
icns.target = icons/paranolog.icns

QMAKE_EXTRA_TARGETS += icns
