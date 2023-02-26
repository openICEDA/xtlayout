#ifndef LERECTANGLE_H
#define LERECTANGLE_H
#include "xtdb.h"
#include "visualentity.h"
#include <QRect>
#include "quadtreenode.h"

class LERectangle: public VisualEntity
{
private:
    xtdb::XtRectangle* mRect;
    bool mSelected;
    QuadtreeNode<LERectangle*>* mOwnerNode;
public:
    LERectangle();
    ~LERectangle();
    LERectangle(xtdb::XtRectangle* pRect);
    void draw(QPainter* pPainter) override;
    void setFirstPoint(const QPoint& pPoint);
    void setSecondPoint(const QPoint& pPoint);
    void setSelected(bool pSelected);
    void setOwnerNode(QuadtreeNode<LERectangle*>* pOwnerNode);
    void destroy();
    QuadtreeNode<LERectangle*>* getOwnerNode();
    QRect getZone();
};

#endif // LERECTANGLE_H
