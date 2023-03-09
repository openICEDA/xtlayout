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
    enum tool_type
    {
        SELECTION_TOOL,
        RECTANGLE_TOOL,
        NAVIGATION_TOOL
    };
    Tool(tool_type pToolType);
    virtual ~Tool(){};
    virtual void mousePressEvent(QMouseEvent* event) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    virtual tool_type getToolType(){return mToolType;};
protected:
    tool_type mToolType;
};

#endif // TOOL_H
