/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef COMPONENT_H
#define COMPONENT_H

#include "NodeView.hpp"
#include <QTimer>
#include <QMenu>

namespace Hako {

#define COMPONENT_SIGNAL(a) (char *)SIGNAL(a)
#define COMPONENT_SLOT(a) (char *)SLOT(a)

class Component: public NodeView
{
    Q_OBJECT
public:
    Component(QGraphicsItem *parent = 0);
    virtual Component* clone(QGraphicsItem *parent = 0) const = 0;
    virtual ~Component();

    int registerOutput(char *signal, const QString &componentName);
    int registerInput(char *slot, const QString &componentName);

    int registerSpecialOutput(char *signal, const QString &componentName);
    int registerSpecialInput(char *slot, const QString &componentName);

    bool connectInput(int in, Component *component, int out);
    bool connectOutput(int out, Component *component, int in);

    bool connectSpecialInput(int in, Component *component, int out);
    bool connectSpecialOutput(int out, Component *component, int in);

    virtual void settingsActivated();
    virtual bool closeComponent();

    void setMenu(QMenu *menu);

    void removeFromWorkspace();

    // To implement
    virtual QString componentCategory() const = 0;
    virtual QString componentDescription() const = 0;
    virtual QString componentAuthor() const = 0;
    virtual QString componentVersion() const = 0;
    virtual QString componentAuthorContact() const = 0;
//    virtual QString componentName() const = 0;
//    virtual QString componentId() const = 0;
//    virtual QIcon componentIcon() const = 0;

private:
    QMenu *m_menu;

private slots:
    void closeButtonClicked(const QPoint &pos);
    void settingsButtonClicked(const QPoint &pos);
    void menuButtonClicked(const QPoint &pos);

};

} // namesapce Hako

#endif // COMPONENT_H
