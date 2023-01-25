#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "tool.h"
#include <QPoint>
#include <QObject>
#include "globalsetting.h"
class Rectangle;
class QMouseEvent;
class PaintingArea;
class RectangleTool : public Tool
{
public:
    Q_OBJECT
public:
    RectangleTool(PaintingArea *pPA);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void completed();
private:
    GlobalSetting::layer_type mLayer;
    bool mFirstPointFixed;
    std::shared_ptr<Rectangle> mRectangle;
    PaintingArea *mPA;
};

#endif // RECTANGLETOOL_H
