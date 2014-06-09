
TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui serialport
DESTDIR     = $$PWD/../../bin/plugins

TARGET = SerialComponent

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += include

SOURCES += \
    src/SerialComponent.cpp \
    src/SerialSettingsDialog.cpp

HEADERS  += \
    include/SerialComponent.hpp \
    include/SerialSettingsDialog.h

FORMS += \
    ui/SerialSettingsDialog.ui

RESOURCES += \
    SerialComponent.qrc
