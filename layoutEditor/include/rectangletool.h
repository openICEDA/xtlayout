#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "tool.h"
#include <QPoint>
#include "globalsetting.h"
#include <QSharedPointer>
class Rectangle;
class QMouseEvent;
class PaintingArea;
class RectangleTool : public Tool
{
public:
    RectangleTool(PaintingArea *pPA);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    GlobalSetting::layer_type mLayer;
    bool mFirstPointFixed;
    QSharedPointer<Rectangle> mRectangle;
    PaintingArea *mPA;
};

#endif // RECTANGLETOOL_H
