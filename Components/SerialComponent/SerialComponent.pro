
QT       += core gui

TARGET = SerialComponent
TEMPLATE = lib
#CONFIG += staticlib

DESTDIR = $$PWD/../../plugins/$$TARGET

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

!include(qextserialport/src/qextserialport.pri) {
        error("Unable to include qextserialport library.")
}

INCLUDEPATH += include

SOURCES += \
    src/SerialComponent.cpp \
    src/SettingsDialog.cpp

HEADERS  += \
    include/SerialComponent.hpp \
    include/SettingsDialog.h

FORMS += \
    ui/SettingsDialog.ui

RESOURCES += \
    SerialComponent.qrc
