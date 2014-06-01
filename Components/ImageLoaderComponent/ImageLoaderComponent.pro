#-------------------------------------------------
#
# Project created by QtCreator 2013-05-04T14:00:38
#
#-------------------------------------------------

TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui
DESTDIR     = $$PWD/../../bin/plugins

TARGET = ImageLoaderComponent

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += include

SOURCES += \
    src/ImageLoaderComponent.cpp \
    src/ImageLoaderSettingsDialog.cpp

HEADERS += \
    include/ImageLoaderComponent.h \
    include/ImageLoaderSettingsDialog.h

FORMS += \
    ui/ImageLoaderSettingsDialog.ui

RESOURCES += \
    ImageLoaderComponent.qrc

