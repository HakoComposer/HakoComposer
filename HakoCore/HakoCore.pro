#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HakoCore
TEMPLATE = lib
CONFIG += staticLib

DESTDIR = $$PWD/../lib

INCLUDEPATH += $$PWD/include

HEADERS  += \
    $$PWD/include/NodeView.hpp \
    $$PWD/include/NodePortView.hpp \
    $$PWD/include/NodeLinkView.hpp \
    $$PWD/include/TemporaryPortView.hpp \
    $$PWD/include/Component.hpp

SOURCES += \
    $$PWD/src/NodeView.cpp \
    $$PWD/src/NodePortView.cpp \
    $$PWD/src/NodeLinkView.cpp \
    $$PWD/src/TemporaryPortView.cpp \
    $$PWD/src/Component.cpp

RESOURCES += \
    $$PWD/HakoCore.qrc
