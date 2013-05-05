#-------------------------------------------------
#
# Project created by QtCreator 2013-05-04T14:00:38
#
#-------------------------------------------------

QT       += widgets

TARGET = ImageLoaderComponent
TEMPLATE = lib

DESTDIR = $$PWD/../../plugins/$$TARGET

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

