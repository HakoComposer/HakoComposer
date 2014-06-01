#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui
DESTDIR     = $$PWD/../../bin/plugins

TARGET = ImageFilterComponent

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += include

SOURCES += \
    src/ImageFilterComponent.cpp \
    src/ImageFilterSettingsDialog.cpp

HEADERS  += \
    include/ImageFilterComponent.hpp \
    include/ImageFilterSettingsDialog.h

FORMS += \
    ui/ImageFilterSettingsDialog.ui

RESOURCES += \
    ImageFilterComponent.qrc
