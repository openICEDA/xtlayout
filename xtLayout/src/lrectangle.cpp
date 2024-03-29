#include "lrectangle.h"
#include "navigationtool.h"
#include "xtliterals.h"
#include <QPainter>
#include "paintingarea.h"
#include "lblock.h"

LRectangle::LRectangle(LBlock* pBlock):x1(0), y1(0), x2(0), y2(0), mRect(nullptr), mBlock(pBlock)
{
}

LRectangle::LRectangle(int pX1, int pY1, int pX2, int pY2, LBlock* pBlock):x1(pX1), y1(pY1), x2(pX2), y2(pY2), mRect(nullptr), mBlock(pBlock)
{
}

LRectangle::~LRectangle()
{
    mBlock->removeVisualEntityInViewport(this);
    mBlock->removeSelectedShape(this);
    if (mRect)
    {
        mRect->destroy();
    }
}

void LRectangle::connectDBObj(xtdb::XtRectangle* pRect)
{
    mRect = pRect;
    mRect->setExtendedObj(XTLAYOUT, this);
}

void LRectangle::syncFromDB()
{
    //TODO: check if mRect is nullptr
    x1 = mRect->getX1();
    y1 = mRect->getY1();
    x2 = mRect->getX2();
    y2 = mRect->getY2();
}

void LRectangle::syncToDB()
{
    mRect = xtdb::XtRectangle::create(mBlock->getDBBlock());
    mRect->setX1(x1);
    mRect->setY1(y1);
    mRect->setX2(x2);
    mRect->setY2(y2);
    mRect->setExtendedObj(XTLAYOUT, this);
}

QRect LRectangle::getZone()
{
    return QRect(QPoint(x1, y1),
                 QPoint(x2, y2));
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
    if (isSelected()) {
        pPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
        pPainter->setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
    }
    pPainter->drawRect(NavigationTool::worldCS2ViewportCS(getZone(), static_cast<PaintingArea*>(pPainter->device())->getBlock()));
}
