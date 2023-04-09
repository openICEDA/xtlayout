#ifndef TOOL_H
#define TOOL_H
#include <QObject>
#include <QPoint>

class PaintingArea;
class QMouseEvent;
class LBlock;
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
    virtual void mousePressEvent(QMouseEvent* event, LBlock* pBlock) = 0;
    virtual void mouseMoveEvent(QMouseEvent* event, LBlock* pBlock) = 0;
    virtual void mouseReleaseEvent(QMouseEvent* event, LBlock* pBlock) = 0;
    virtual void keyPressEvent(QKeyEvent* event, LBlock* pBlock) = 0;
    tool_type getToolType(){return mToolType;};
protected:
    tool_type mToolType;
};

#endif // TOOL_H
