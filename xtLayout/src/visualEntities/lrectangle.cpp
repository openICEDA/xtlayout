#include "lrectangle.h"
#include "navigationtool.h"
#include <QPainter>

LRectangle::LRectangle(NavigationTool* pNavTool):x1(0), y1(0), x2(0), y2(0), mRect(nullptr), mSelected(false), mOwnerNode(nullptr), VisualEntity(pNavTool)
{

}

LRectangle::LRectangle(xtdb::XtRectangle* pRect, NavigationTool* pNavTool):mRect(pRect), mSelected(false), mOwnerNode(nullptr), VisualEntity(pNavTool)
{
}

LRectangle::~LRectangle()
{
    getOwnerQuadtreeNode()->deleteObj(this);
    if (mRect) {
        mRect->destroy();
    }
}

void LRectangle::storeToDB(xtdb::XtBlock* pBlock)
{
    mRect = xtdb::XtRectangle::create(pBlock);
    mRect->setX1(x1);
    mRect->setY1(y1);
    mRect->setX2(x2);
    mRect->setY2(y2);
}

QRect LRectangle::getZone()
{
    return QRect(QPoint(x1, y1),
                 QPoint(x2, y2));
}

void LRectangle::setSelected(bool pSelected)
{
    mSelected = pSelected;
}

QPoint LRectangle::getFirstPoint()
{
    return QPoint(x1, y1);
}

QPoint LRectangle::getSecondPoint()
{
    return QPoint(x2, y2);
}

void LRectangle::setFirstPoint(const QPoint& pPoint)
{
    x1 = pPoint.x();
    y1 = pPoint.y();
}

void LRectangle::setSecondPoint(const QPoint& pPoint)
{
    x2 = pPoint.x();
    y2 = pPoint.y();
}

void LRectangle::draw(QPainter* pPainter)
{
    if (mSelected) {
        pPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
        pPainter->setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
    }
    pPainter->drawRect(mNavTool->worldCS2ViewportCS(getZone()));
}

QuadtreeNode<LRectangle*>* LRectangle::getOwnerQuadtreeNode()
{
    return mOwnerNode;
}

void LRectangle::setOwnerNode(QuadtreeNode<LRectangle*>* pOwnerNode)
{
    mOwnerNode = pOwnerNode;
}
