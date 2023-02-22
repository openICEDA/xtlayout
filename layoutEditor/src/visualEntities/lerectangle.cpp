#include "lerectangle.h"
#include <QPainter>

LERectangle::LERectangle():mRect(nullptr), mSelected(false)
{

}

LERectangle::LERectangle(xtdb::XtRectangle* pRect):mRect(pRect), mSelected(false)
{
}

LERectangle::~LERectangle()
{
    //TODO: add destroy function in xtrectangle and call it here
//    mRect->
}

QRect LERectangle::getZone()
{
    return QRect(QPoint(mRect->getX1(), mRect->getY1()),
                 QPoint(mRect->getX2(), mRect->getY2()));
}

void LERectangle::setSelected(bool pSelected)
{
    mSelected = pSelected;
}

void LERectangle::setFirstPoint(const QPoint& pPoint)
{
    mRect->setX1(pPoint.x());
    mRect->setY1(pPoint.y());
}

void LERectangle::setSecondPoint(const QPoint& pPoint)
{
    mRect->setX2(pPoint.x());
    mRect->setY2(pPoint.y());
}

void LERectangle::draw(QPainter* pPainter)
{
    if (mSelected) {
        pPainter->setBrush(QBrush(Qt::white, Qt::SolidPattern));
    } else {
        pPainter->setBrush(QBrush(QColor(255, 0, 0), Qt::SolidPattern));
    }
    pPainter->drawRect(getZone());
}
