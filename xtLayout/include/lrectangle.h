#ifndef LRECTANGLE_H
#define LRECTANGLE_H
#include "xtdb.h"
#include "lshape.h"
#include <QRect>

class NavigationTool;
class LRectangle: public LShape
{
private:
    xtdb::XtRectangle* mRect;
public:
    int x1;
    int y1;
    int x2;
    int y2;
public:
    LRectangle(NavigationTool* pTool);
    ~LRectangle() override;
    LRectangle(xtdb::XtRectangle* pRect, NavigationTool* pTool);
    void draw(QPainter* pPainter) override;
    void storeToDB(xtdb::XtBlock* pBlock);
    QPoint getFirstPoint();
    QPoint getSecondPoint();
    void setFirstPoint(const QPoint& pPoint);
    void setSecondPoint(const QPoint& pPoint);
    QRect getZone();
};

#endif // LRECTANGLE_H
