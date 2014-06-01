#-------------------------------------------------
#
# Project created by QtCreator 2013-05-04T14:00:38
#
#-------------------------------------------------

TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui
DESTDIR     = $$PWD/../../bin/plugins

TARGET = ImageViewerComponent

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += include

SOURCES += \
    src/ImageViewerComponent.cpp \
    src/ImageViewerSettingsDialog.cpp

HEADERS += \
    include/ImageViewerComponent.h \
    include/ImageViewerSettingsDialog.h

FORMS += \
    ui/ImageViewerSettingsDialog.ui

RESOURCES += \
    ImageViewerComponent.qrc

