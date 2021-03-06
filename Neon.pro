#-------------------------------------------------
#
# Project created by QtCreator 2018-09-22T14:29:55
#
#-------------------------------------------------

QT += core gui widgets svg

TARGET = Neon
TEMPLATE = lib

DEFINES += NEON_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	neon.cpp \
    singleapp.cpp \
    status.cpp \
    nresources.cpp \
    ioexception.cpp

HEADERS += \
	neon.h \
	Neon \
	neon_global.h \
    theme.h \
    singleapp.h \
    status.h \
    nresources.h \
    ioexception.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    neon_resources.qrc

DISTFILES += \
    README.md \
    .gitignore \
	LICENSE.txt \
	compile_res.bat
