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

macx{
    INCLUDEPATH += /opt/local/include
    LIBS +=-L/opt/local/lib \
    -lopencv_core.2.4.5 \
    -lopencv_highgui.2.4.5 \
    -lopencv_imgproc.2.4.5 \
    -lopencv_video.2.4.5 \
}

SOURCES += \
    $$PWD/src/ImageFilterComponent.cpp \
    $$PWD/src/ImageFilterSettingsDialog.cpp

HEADERS  += \
    $$PWD/include/ImageFilterComponent.hpp \
    $$PWD/include/ImageFilterSettingsDialog.h

FORMS += \
    $$PWD/ui/ImageFilterSettingsDialog.ui

RESOURCES += \
    $$PWD/ImageFilterComponent.qrc

} else {
    message( "Skipping $$PWD: already included" )
}
