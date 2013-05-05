#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

QT       += core gui

TARGET = SampleComponent
TEMPLATE = lib
#CONFIG += staticlib

DESTDIR = $$PWD/../../plugins/$$TARGET

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += include

SOURCES += \
    src/SampleComponent.cpp \
    src/SampleSettingsDialog.cpp

HEADERS  += \
    include/SampleComponent.hpp \
    include/SampleSettingsDialog.h

FORMS += \
    ui/SampleSettingsDialog.ui

RESOURCES += \
    SampleComponent.qrc
