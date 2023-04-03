#ifndef NAVIGATIONTOOL_H
#define NAVIGATIONTOOL_H
#include "tool.h"
#include <QRect>
class PaintingArea;
class NavigationTool : public Tool
{
public:
    NavigationTool();
    ~NavigationTool() override {};
    static QPoint viewportCS2WorldCS(const QPoint& pPnt, PaintingArea* pPA);
    static QRect viewportCS2WorldCS(const QRect& pRects, PaintingArea* pPA);
    static std::vector<QPoint> viewportCS2WorldCS(const std::vector<QPoint>& pPnts, PaintingArea* pPA);
    static QPoint worldCS2ViewportCS(const QPoint& pPnt, PaintingArea* pPA);
    static QRect worldCS2ViewportCS(const QRect& pRects, PaintingArea* pPA);
    static std::vector<QPoint> worldCS2ViewportCS(const std::vector<QPoint>& pPnts, PaintingArea* pPA);
    void mousePressEvent(QMouseEvent* event, PaintingArea* pPA) override {};
    void mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA) override {};
    void mouseReleaseEvent(QMouseEvent* event, PaintingArea* pPA) override{};
    void keyPressEvent(QKeyEvent* event, PaintingArea* pPA) override;
};

#endif // NAVIGATIONTOOL_H
