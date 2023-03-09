#ifndef LRectangle_H
#define LRectangle_H
#include "xtdb.h"
#include "visualentity.h"
#include <QRect>
#include "quadtreenode.h"

class LRectangle: public VisualEntity
{
private:
    int mX1;
    int mY1;
    int mX2;
    int mY2;
    xtdb::XtRectangle* mRect;
    bool mSelected;
    QuadtreeNode<LRectangle*>* mOwnerNode;
public:
    LRectangle();
    ~LRectangle();
    LRectangle(xtdb::XtRectangle* pRect);
    void draw(QPainter* pPainter) override;
    void storeToDB(xtdb::XtBlock* pBlock);
    void setFirstPoint(const QPoint& pPoint);
    void setSecondPoint(const QPoint& pPoint);
    void setSelected(bool pSelected);
    void setOwnerNode(QuadtreeNode<LRectangle*>* pOwnerNode);
    void destroy();
    QuadtreeNode<LRectangle*>* getOwnerQuadtreeNode();
    QRect getZone();
};

#endif // LRectangle_H
