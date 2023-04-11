#ifndef LRECTANGLE_H
#define LRECTANGLE_H
#include "xtdb.h"
#include "lshape.h"
#include <QRect>

class LBlock;
class NavigationTool;
class LRectangle: public LShape
{
private:
    xtdb::XtRectangle* mRect;
    LBlock* mBlock;
public:
    int x1;
    int y1;
    int x2;
    int y2;
public:
    LRectangle(LBlock* pBlock);
    LRectangle(int pX1, int pY1, int pX2, int pY2, LBlock* pBlock);
    ~LRectangle() override;
//    LRectangle(xtdb::XtRectangle* pRect);
    void draw(QPainter* pPainter) override;
    void connectDBObj(xtdb::XtRectangle* pRect);
    void syncFromDB();
    void syncToDB();
    QPoint getFirstPoint();
    QPoint getSecondPoint();
    void setFirstPoint(const QPoint& pPoint);
    void setSecondPoint(const QPoint& pPoint);
    QRect getZone();
    LBlock* getBlock(){return mBlock;};
};

#endif // LRECTANGLE_H
