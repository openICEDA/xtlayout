#ifndef NAVIGATIONTOOL_H
#define NAVIGATIONTOOL_H
#include "tool.h"
#include <QRect>
class PaintingArea;
class NavigationTool : public Tool
{
private:
    QRect mViewport;
    PaintingArea* mPA;
public:
    NavigationTool(PaintingArea* pPA);
    QPoint viewportCS2WorldCS(QPoint pPnt);
    QRect viewportCS2WorldCS(const QRect& pRects);
    std::vector<QPoint> viewportCS2WorldCS(const std::vector<QPoint>& pPnts);
    QPoint worldCS2ViewportCS(QPoint pPnt);
    QRect worldCS2ViewportCS(const QRect& pRects);
    std::vector<QPoint> worldCS2ViewportCS(const std::vector<QPoint>& pPnts);
    ~NavigationTool() override {};
    void mousePressEvent(QMouseEvent* event) override {};
    void mouseMoveEvent(QMouseEvent* event) override {};
    void mouseReleaseEvent(QMouseEvent* event) override {};
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // NAVIGATIONTOOL_H
