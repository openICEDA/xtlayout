#include "grid.h"
#include <QPainter>
#include "globalsetting.h"
Grid::Grid()
{

}

void Grid::draw(QPainter* pPainter)
{
    QBrush brush(QColor(0,0,0,255));
    QPen pen(QColor(0,0,0,255));
    pen.setBrush(brush);
    pPainter->setPen(pen);
    pPainter->setBrush(brush);
    for(int i = 0; i < GlobalSetting::canvasSize.width()/GlobalSetting::gridWidth; i++)
    {
        pPainter->drawLine(QPoint((i + 1) * GlobalSetting::gridWidth, 0), QPoint((i + 1) * GlobalSetting::gridWidth, GlobalSetting::canvasSize.height()));
    }
    for(int i = 0; i < GlobalSetting::canvasSize.height()/GlobalSetting::gridWidth; i++)
    {
        pPainter->drawLine(QPoint(0, (i + 1) * GlobalSetting::gridWidth), QPoint(GlobalSetting::canvasSize.width(), (i + 1) * GlobalSetting::gridWidth));
    }
}
