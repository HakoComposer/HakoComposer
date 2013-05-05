#-------------------------------------------------
#
# Project created by QtCreator 2013-05-04T14:00:38
#
#-------------------------------------------------
!contains( included_modules, $$PWD ) {
    included_modules += $$PWD
    message( "Including $$PWD" )

QT       += widgets

!include(../../HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

INCLUDEPATH += $$PWD/include

SOURCES += \
    $$PWD/src/ImageViewerComponent.cpp \
    $$PWD/src/ImageViewerSettingsDialog.cpp

HEADERS += \
    $$PWD/include/ImageViewerComponent.h \
    $$PWD/include/ImageViewerSettingsDialog.h

FORMS += \
    $$PWD/ui/ImageViewerSettingsDialog.ui

RESOURCES += \
    $$PWD/ImageViewerComponent.qrc

} else {
    message( "Skipping $$PWD: already included" )
}
