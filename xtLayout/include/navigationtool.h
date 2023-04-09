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
    static QPoint viewportCS2WorldCS(const QPoint& pPnt, LBlock* pBlock);
    static QRect viewportCS2WorldCS(const QRect& pRects, LBlock* pBlock);
    static std::vector<QPoint> viewportCS2WorldCS(const std::vector<QPoint>& pPnts, LBlock* pBlock);
    static QPoint worldCS2ViewportCS(const QPoint& pPnt, LBlock* pBlock);
    static QRect worldCS2ViewportCS(const QRect& pRects, LBlock* pBlock);
    static std::vector<QPoint> worldCS2ViewportCS(const std::vector<QPoint>& pPnts, LBlock* pBlock);
    void mousePressEvent(QMouseEvent* event, LBlock* pBlock) override {};
    void mouseMoveEvent(QMouseEvent* event, LBlock* pBlock) override {};
    void mouseReleaseEvent(QMouseEvent* event, LBlock* pBlock) override{};
    void keyPressEvent(QKeyEvent* event, LBlock* pBlock) override;
};

#endif // NAVIGATIONTOOL_H
