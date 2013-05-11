#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

QT       += core gui

TARGET = HakoComposer
TEMPLATE = app
DESTDIR = $$PWD/bin

INCLUDEPATH += include

APP_VERSION = 0.1.0
DEFINES += APP_VERSION=\\\"$$APP_VERSION\\\"

!include(HakoCore/HakoCore.pri) {
        error("Unable to include Hako Library.")
}

!include(Components/SampleComponent/SampleComponent.pri) {
        error("Unable to include Sample Component.")
}

!include(Components/SerialComponent/SerialComponent.pri) {
        error("Unable to include Serial Component.")
}

!include(Components/ImageLoaderComponent/ImageLoaderComponent.pri) {
        error("Unable to include Serial Component.")
}

!include(Components/ImageViewerComponent/ImageViewerComponent.pri) {
        error("Unable to include Serial Component.")
}

!include(Components/ImageFilterComponent/ImageFilterComponent.pri) {
        error("Unable to include Image Filter Component.")
}


HEADERS  += \
    include/MainWindow.hpp \
    include/Workspace.hpp \
    include/ComponentLibrary.hpp \
    include/WorkspaceView.hpp \
    include/PluginsInfoDialog.h

SOURCES += \
    src/main.cpp\
    src/MainWindow.cpp \
    src/ComponentLibrary.cpp \
    src/Workspace.cpp \
    src/WorkspaceView.cpp \
    src/PluginsInfoDialog.cpp

FORMS    += \
    ui/MainWindow.ui \
    ui/PluginsInfoDialog.ui

RESOURCES += HakoComposer.qrc

macx:ICON = img/hako.icns
