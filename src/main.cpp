/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#include <QtGui/QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Mehrez Kristou");
    QApplication::setOrganizationDomain("Kristou.com");
    QApplication::setApplicationName("HakoComposer");
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setWindowIcon(QIcon(":/icons/hako"));

    MainWindow w;
    w.show();

    return a.exec();
}
