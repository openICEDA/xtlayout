#ifndef TOOL_H
#define TOOL_H
#include <QObject>
#include <QPoint>
class QMouseEvent;
class QPainter;
class QKeyEvent;
class Tool: public QObject
{
    Q_OBJECT
public:
    Tool();
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
    virtual void keyPressEvent(QKeyEvent *event) = 0;
};

#endif // TOOL_H
