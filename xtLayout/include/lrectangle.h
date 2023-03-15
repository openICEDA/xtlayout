#ifndef LRECTANGLE_H
#define LRECTANGLE_H
#include "xtdb.h"
#include "visualentity.h"
#include <QRect>
#include "quadtreenode.h"
class NavigationTool;
class LRectangle: public VisualEntity
{
private:
    xtdb::XtRectangle* mRect;
    bool mSelected;
    QuadtreeNode<LRectangle*>* mOwnerNode;
public:
    int x1;
    int y1;
    int x2;
    int y2;
public:
    LRectangle(NavigationTool* pTool);
    ~LRectangle();
    LRectangle(xtdb::XtRectangle* pRect, NavigationTool* pTool);
    void draw(QPainter* pPainter) override;
    void storeToDB(xtdb::XtBlock* pBlock);
    QPoint getFirstPoint();
    QPoint getSecondPoint();
    void setFirstPoint(const QPoint& pPoint);
    void setSecondPoint(const QPoint& pPoint);
    void setSelected(bool pSelected);
    void setOwnerNode(QuadtreeNode<LRectangle*>* pOwnerNode);
    QuadtreeNode<LRectangle*>* getOwnerQuadtreeNode();
    QRect getZone();
};

#endif // LRECTANGLE_H
