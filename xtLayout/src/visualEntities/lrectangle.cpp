#include "lrectangle.h"
#include <QPainter>

LRectangle::LRectangle():mX1(0), mY1(0), mX2(0), mY2(0), mRect(nullptr), mSelected(false), mOwnerNode(nullptr)
{

}

LRectangle::LRectangle(xtdb::XtRectangle* pRect):mRect(pRect), mSelected(false), mOwnerNode(nullptr)
{
}

LRectangle::~LRectangle()
{
    if (mRect) {
        mRect->destroy();
    }
}

void LRectangle::storeToDB(xtdb::XtBlock* pBlock)
{
    mRect = xtdb::XtRectangle::create(pBlock);
    mRect->setX1(mX1);
    mRect->setY1(mY1);
    mRect->setX2(mX2);
    mRect->setY2(mY2);
}

QRect LRectangle::getZone()
{
    return QRect(QPoint(mX1, mY1),
                 QPoint(mX2, mY2));
}

void LRectangle::setSelected(bool pSelected)
{
    mSelected = pSelected;
}

void LRectangle::setFirstPoint(const QPoint& pPoint)
{
    mX1 = pPoint.x();
    mY1 = pPoint.y();
}

void LRectangle::setSecondPoint(const QPoint& pPoint)
{
    mX2 = pPoint.x();
    mY2 = pPoint.y();
}

void LRectangle::draw(QPainter* pPainter)
{
    if (mSelected) {
        pPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
        pPainter->setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
    }
    pPainter->drawRect(getZone());
}

void LRectangle::destroy()
{
    getOwnerQuadtreeNode()->deleteObj(this);
    if (mRect) {
        mRect->destroy();
    }
}

QuadtreeNode<LRectangle*>* LRectangle::getOwnerQuadtreeNode()
{
    return mOwnerNode;
}

void LRectangle::setOwnerNode(QuadtreeNode<LRectangle*>* pOwnerNode)
{
    mOwnerNode = pOwnerNode;
}
