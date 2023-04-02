#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include "tool.h"
#include "visualentity.h"
#include "grid.h"
#include "globalsetting.h"
#include <algorithm>
#include "mainwindow.h"
#include "xtliterals.h"
#include "xtdb.h"

PaintingArea::PaintingArea(QWidget* pMainWindow)
    : QWidget{pMainWindow}, mMainWindow(static_cast<MainWindow*>(pMainWindow))
{
    mBlock = xtdb::XtBlock::create();
    resize(pMainWindow->geometry().width(), pMainWindow->geometry().height());
//    insertVisualEntity(new Grid);
    mShapeQuery = new ShapeQuery(mBlock);
    update();
}

PaintingArea::~PaintingArea()
{
    delete mShapeQuery;
}

void PaintingArea::paintEvent(QPaintEvent*)
{
    //TODO: Seperate the drawer or let QPainter be member variable.
    QPainter painter(this);
    std::for_each(mAllVisualEntities.cbegin(), mAllVisualEntities.cend(), [&](VisualEntity* ve){ve->draw(&painter);});
}

void PaintingArea::mousePressEvent(QMouseEvent* event)
{
    std::vector<Tool*>& activeTools = static_cast<MainWindow*>(mMainWindow)->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->mousePressEvent(event, this);
        }
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent* event)
{
    std::vector<Tool*>& activeTools = static_cast<MainWindow*>(mMainWindow)->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->mouseMoveEvent(event, this);
        }
    }
}

void PaintingArea::mouseReleaseEvent(QMouseEvent* event)
{
    std::vector<Tool*>& activeTools = static_cast<MainWindow*>(mMainWindow)->getActiveTools();
    for (std::vector<Tool*>::const_iterator it = activeTools.cbegin(); it != activeTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->mouseReleaseEvent(event, this);
        }
    }
}

void PaintingArea::insertVisualEntity(VisualEntity* pVisualEntity)
{
    mAllVisualEntities.insert(pVisualEntity);
}

void PaintingArea::removeVisualEntity(VisualEntity* pVisualEntity)
{
    QSet<VisualEntity*>::const_iterator it = mAllVisualEntities.find(pVisualEntity);
    if (mAllVisualEntities.cend() != it)
    {
        mAllVisualEntities.erase(it);
    }
}

xtdb::XtBlock* PaintingArea::getBlock()
{
    return mBlock;
}

void PaintingArea::ShapeQuery::onShapeFound(xtdb::XtShape* pShape)
{
    //TODO: execute onshapefound inside quadtree, instead of generating result at first, then iterate through it.
    LShape* shape = static_cast<LShape*>(pShape->getExtendedObj(XTLAYOUT));
    mFoundObjs.insert(shape);
}

void PaintingArea::searchShapes(const QRect& pZone, QSet<LShape*>& pFoundObjs)
{
    xtdb::XtRect region(pZone.left(), pZone.top(), pZone.right(), pZone.bottom());
    mShapeQuery->query(region);
    pFoundObjs = std::move(mShapeQuery->mFoundObjs);
}

PaintingArea::ShapeQuery::ShapeQuery(xtdb::XtBlock* pBlock):xtdb::XtShapeQuery(pBlock)
{

}
