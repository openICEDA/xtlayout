#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include "tool.h"
#include "visualentity.h"
#include "grid.h"
#include "rectangle.h"
#include "quadtreenode.h"
#include "globalsetting.h"

PaintingArea::PaintingArea(QWidget *parent)
    : QWidget{parent}, mQuadtree(QRect(QPoint(0, 0), GlobalSetting::canvasSize))
{
    insertVisualEntity(std::shared_ptr<VisualEntity>(new Grid));
    //load gds2 file into quadtree, the coordinates in gds2 is in global coordinate system.
    //there should exist another data structure to store the shapes inside view ports. After loading
    // all shapes into quadtree, i search for the shapes inside view ports and store the result in this
    // new data structre
    update();
}

void PaintingArea::paintEvent(QPaintEvent *)
{
    //TODO: Seperate the drawer
    QPainter painter(this);

    QSet<std::shared_ptr<VisualEntity>>::const_iterator visualEntityIter = mAllVisualEntities.constBegin();
    while (visualEntityIter != mAllVisualEntities.constEnd()) {
        (*visualEntityIter)->draw(&painter);
        ++visualEntityIter;
    }
}

void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    if(nullptr != mTool)
    {
        mTool->mousePressEvent(event);
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    if(nullptr != mTool)
    {
        mTool->mouseMoveEvent(event);
    }
}

void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(nullptr != mTool)
    {
        mTool->mouseReleaseEvent(event);
    }
}

void PaintingArea::insertVisualEntity(std::shared_ptr<VisualEntity> pVisualEntity)
{
    mAllVisualEntities.insert(std::move(pVisualEntity));
}

void PaintingArea::deleteVisualEntity(VisualEntity *pVisualEntity)
{
    mAllVisualEntities.erase(mAllVisualEntities.find(std::shared_ptr<VisualEntity>(pVisualEntity)));
//    mQuadtree.erase(mAllVisualEntities.find(pVisualEntity));
}

void PaintingArea::deleteTool()
{
    delete mTool;
    mTool = nullptr;
}
