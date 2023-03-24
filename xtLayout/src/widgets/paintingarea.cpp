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
#include <algorithm>
#include "mainwindow.h"

PaintingArea::PaintingArea(QWidget* pMainWindow)
    : QWidget{pMainWindow}, mQuadtree(QRect(QPoint(0, 0), GlobalSetting::canvasSize)), mMainWindow(static_cast<MainWindow*>(pMainWindow))
{
    mBlock = xtdb::XtBlock::create();
    resize(pMainWindow->geometry().width(), pMainWindow->geometry().height());
//    insertVisualEntity(new Grid);
    update();
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

void PaintingArea::searchRects(const QRect& pZone, QSet<LRectangle*>& pFoundObjs)
{
    mQuadtree.search(pZone, pFoundObjs);
}
