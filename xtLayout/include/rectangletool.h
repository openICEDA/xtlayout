#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "tool.h"
#include <QPoint>
#include <QObject>
#include "lrectangle.h"
#include "globalsetting.h"
#include "xtdb.h"


class QMouseEvent;
class LBlock;
class NavigationTool;
class RectangleTool : public Tool
{
    Q_OBJECT
private:
    GlobalSetting::layer_type mLayer;
    bool mFirstPointFixed;
    LRectangle* mRectangle;
public:
    RectangleTool(PaintingArea* pPA);
    ~RectangleTool() override;
    void mousePressEvent(QMouseEvent* event, LBlock* pBlock) override;
    void mouseMoveEvent(QMouseEvent* event, LBlock* pBlock) override;
    void mouseReleaseEvent(QMouseEvent* event, LBlock* pBlock) override;
    void keyPressEvent(QKeyEvent* event, LBlock* pBlock) override;
signals:
    void completed(LRectangle*);
};

#endif // RECTANGLETOOL_H
