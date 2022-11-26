#include "rectangle.h"
#include "globalsetting.h"
#include <QPainter>
Rectangle::Rectangle()
{

}

Rectangle::Rectangle(int pX1, int pY1, int pW, int pH, GlobalSetting::layer_type layer):
    mRect(pX1, pY1, pW, pH), mLayer(layer)
{

}

Rectangle::Rectangle(QPoint pFirstPoint, QPoint pSecondPoint, GlobalSetting::layer_type layer)
    :mRect(pFirstPoint, pSecondPoint), mLayer(layer)
{

}

void Rectangle::draw(QPainter *pPainter)
{
    QBrush brush(GlobalSetting::textureOfLayer.value(mLayer));
    pPainter->setBrush(brush);
    pPainter->drawRect(mRect);
}
