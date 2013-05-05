#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

!contains( included_modules, $$PWD ) {
    included_modules += $$PWD
    message( "Including $$PWD" )

QT       += core gui

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

} else {
    message( "Skipping $$PWD: already included" )
}
