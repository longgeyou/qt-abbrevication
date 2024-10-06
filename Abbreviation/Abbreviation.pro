#-------------------------------------------------
#
# Project created by QtCreator 2024-10-03T22:33:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Abbreviation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        abbreviation.cpp

HEADERS += \
        abbreviation.h \
    ../build-Abbreviation-aa-Debug/ui_abbreviation.h \
    ../build-Abbreviation-aa-Debug/ui_dialogdirectory.h \
    ../Debug/ui_abbreviation.h \
    ../Debug/ui_dialogdirectory.h

FORMS += \
        abbreviation.ui \
    dialogdirectory.ui
