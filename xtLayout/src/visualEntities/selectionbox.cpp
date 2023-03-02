#include "selectionbox.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

SelectionBox::SelectionBox():mRect({0,0,0,0})
{

}

void SelectionBox::draw(QPainter* pPainter)
{
    QPen pen;
    pen.setBrush(QBrush(QColor(0,0,0,255)));
    pPainter->setPen(pen);
    pPainter->setBrush(QColor(0,0,0,0));
    pPainter->drawRect(mRect);
}
