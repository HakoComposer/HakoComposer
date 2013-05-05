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

!include(qextserialport/src/qextserialport.pri) {
        error("Unable to include qextserialport library.")
}

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/SerialComponent.cpp \
    $$PWD/src/SerialSettingsDialog.cpp

HEADERS  += \
    $$PWD/include/SerialComponent.hpp \
    $$PWD/include/SerialSettingsDialog.h

FORMS += \
    $$PWD/ui/SerialSettingsDialog.ui

RESOURCES += \
    $$PWD/SerialComponent.qrc

} else {
    message( "Skipping $$PWD: already included" )
}
