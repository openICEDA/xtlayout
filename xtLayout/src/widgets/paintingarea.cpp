#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include "tool.h"
#include "visualentity.h"
#include "grid.h"
#include "quadtreenode.h"
#include "globalsetting.h"

PaintingArea::PaintingArea(QWidget *parent)
    : QWidget{parent}, mQuadtree(QRect(QPoint(0, 0), GlobalSetting::canvasSize))
{
    mBlock = xtdb::XtBlock::create();
    insertVisualEntity(new Grid);
    //load gds2 file into quadtree, the coordinates in gds2 is in global coordinate system.
    //there should exist another data structure to store the shapes inside view ports. After loading
    // all shapes into quadtree, i search for the shapes inside view ports and store the result in this
    // new data structre
    update();
}

void PaintingArea::paintEvent(QPaintEvent*)
{
    //TODO: Seperate the drawer or let QPainter be member variable.
    QPainter painter(this);

    QSet<VisualEntity*>::const_iterator visualEntityIter = mAllVisualEntities.constBegin();
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

void PaintingArea::insertVisualEntity(VisualEntity* pVisualEntity)
{
    mAllVisualEntities.insert(pVisualEntity);
}

void PaintingArea::deleteVisualEntity(VisualEntity* pVisualEntity)
{
    QSet<VisualEntity*>::Iterator it = mAllVisualEntities.find(pVisualEntity);
    if (mAllVisualEntities.end() != it)
    {
        mAllVisualEntities.erase(it);
    }
}

void PaintingArea::deleteTool()
{
    delete mTool;
    mTool = nullptr;
}
