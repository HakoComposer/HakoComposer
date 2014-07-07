#
#  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
#  as-is and without warranty under the MIT License. See
#  [root]/license.txt for more. This information must remain intact.
#

!contains( included_modules, $$PWD ) {
    included_modules += $$PWD

    QT       += core gui widgets

    INCLUDEPATH += $$PWD/include

    HEADERS  += \
        $$PWD/include/ComponentInterface.h \
        $$PWD/include/NodeView.hpp \
        $$PWD/include/NodePortView.hpp \
        $$PWD/include/NodeLinkView.hpp \
        $$PWD/include/LinkConnectorView.h \
        $$PWD/include/TemporaryPortView.hpp \
        $$PWD/include/Component.hpp

    SOURCES += \
        $$PWD/src/NodeView.cpp \
        $$PWD/src/NodePortView.cpp \
        $$PWD/src/NodeLinkView.cpp \
        $$PWD/src/LinkConnectorView.cpp \
        $$PWD/src/TemporaryPortView.cpp \
        $$PWD/src/Component.cpp

    RESOURCES += \
        $$PWD/HakoCore.qrc

}
