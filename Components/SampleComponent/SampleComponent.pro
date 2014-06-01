#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

TEMPLATE    = lib
CONFIG      += plugin
QT          += core gui
DESTDIR     = $$PWD/../../bin/plugins


TARGET      = SampleComponent

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/SampleComponent.cpp \
    $$PWD/src/SampleSettingsDialog.cpp

HEADERS  += \
    $$PWD/include/SampleComponent.hpp \
    $$PWD/include/SampleSettingsDialog.h

FORMS += \
    $$PWD/ui/SampleSettingsDialog.ui

RESOURCES += \
    $$PWD/SampleComponent.qrc
