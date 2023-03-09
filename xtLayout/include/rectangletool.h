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
class RectangleTool : public Tool
{
public:
    Q_OBJECT
public:
    RectangleTool(PaintingArea* pPA);
    ~RectangleTool() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
signals:
    void completed();
private:
    GlobalSetting::layer_type mLayer;
    bool mFirstPointFixed;
    PaintingArea* mPA;
    LRectangle* mRectangle;
};

#endif // RECTANGLETOOL_H
