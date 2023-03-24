#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "tool.h"
#include <QPoint>
#include <QObject>
#include "lrectangle.h"
#include "globalsetting.h"
#include "xtdb.h"


class QMouseEvent;
class PaintingArea;
class NavigationTool;
class RectangleTool : public Tool
{
    Q_OBJECT
private:
    GlobalSetting::layer_type mLayer;
    bool mFirstPointFixed;
    LRectangle* mRectangle;
    NavigationTool* mNavTool;
public:
    RectangleTool(PaintingArea* pPA, NavigationTool* pNavTool);
    ~RectangleTool() override;
    void mousePressEvent(QMouseEvent* event, PaintingArea* pPA) override;
    void mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA) override;
    void mouseReleaseEvent(QMouseEvent* event, PaintingArea* pPA) override;
    void keyPressEvent(QKeyEvent* event, PaintingArea* pPA) override;
signals:
    void completed();
};

#endif // RECTANGLETOOL_H
