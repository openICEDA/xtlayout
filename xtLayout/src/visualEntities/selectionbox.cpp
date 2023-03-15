#include "selectionbox.h"
#include "navigationtool.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

SelectionBox::SelectionBox(NavigationTool* pNavTool):mRect({0,0,0,0}), VisualEntity(pNavTool)
{

}

void SelectionBox::draw(QPainter* pPainter)
{
    QPen pen;
    pen.setBrush(QBrush(QColor(0,0,0,255)));
    pPainter->setPen(pen);
    pPainter->setBrush(QColor(0,0,0,0));
    pPainter->drawRect(mNavTool->worldCS2ViewportCS(getZone()));
}
