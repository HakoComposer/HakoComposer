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
    $$PWD/src/ImageLoaderComponent.cpp \
    $$PWD/src/ImageLoaderSettingsDialog.cpp

HEADERS += \
    $$PWD/include/ImageLoaderComponent.h \
    $$PWD/include/ImageLoaderSettingsDialog.h

FORMS += \
    $$PWD/ui/ImageLoaderSettingsDialog.ui

RESOURCES += \
    $$PWD/ImageLoaderComponent.qrc

} else {
    message( "Skipping $$PWD: already included" )
}
