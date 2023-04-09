#include "selectionbox.h"
#include "navigationtool.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include "paintingarea.h"

SelectionBox::SelectionBox()
{

}

void SelectionBox::draw(QPainter* pPainter)
{
    QPen pen;
    pen.setBrush(QBrush(QColor(0,0,0,255)));
    pPainter->setPen(pen);
    pPainter->setBrush(QColor(0,0,0,0));
    pPainter->drawRect(NavigationTool::worldCS2ViewportCS(getZone(), static_cast<PaintingArea*>(pPainter->device())->getBlock()));
}
