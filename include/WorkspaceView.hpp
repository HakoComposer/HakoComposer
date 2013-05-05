/*
*  Copyright (c) HakoComposer & Mehrez Kristou (kristou.com), distributed
*  as-is and without warranty under the MIT License. See
*  [root]/license.txt for more. This information must remain intact.
*/

#ifndef WORKSPACEVIEW_H
#define WORKSPACEVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class WorkspaceView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorkspaceView(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent* event);
    
signals:
    
public slots:
    
};

#endif // WORKSPACEVIEW_H
