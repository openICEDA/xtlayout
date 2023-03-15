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

PaintingArea::PaintingArea(QWidget *parent)
    : QWidget{parent}, mQuadtree(QRect(QPoint(0, 0), GlobalSetting::canvasSize))
{
    mBlock = xtdb::XtBlock::create();
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
    for (std::vector<Tool*>::const_iterator it = mActiveTools.cbegin(); it != mActiveTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->mousePressEvent(event);
        }
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent* event)
{
    for (std::vector<Tool*>::const_iterator it = mActiveTools.cbegin(); it != mActiveTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->mouseMoveEvent(event);
        }
    }
}

void PaintingArea::mouseReleaseEvent(QMouseEvent* event)
{
    for (std::vector<Tool*>::const_iterator it = mActiveTools.cbegin(); it != mActiveTools.cend(); it++)
    {
        Tool* tool = *it;
        if (tool) {
            tool->mouseReleaseEvent(event);
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

void PaintingArea::deactivateTool(Tool::tool_type pToolType)
{
    //TODO: deal with case with tools of same type
    std::vector<Tool*>::iterator it = std::find_if(mActiveTools.begin(), mActiveTools.end(), [&](const auto& tool){return pToolType == tool->getToolType();});
    if (mActiveTools.cend() != it)
    {
        delete (*it);
        mActiveTools.erase(it);
    }
}

void PaintingArea::activateTool(Tool* pTool)
{
    if (!findActiveTool(pTool->getToolType()))
    {
        mActiveTools.push_back(pTool);
    }
}

Tool* PaintingArea::findActiveTool(Tool::tool_type pToolType)
{
    std::vector<Tool*>::iterator it = std::find_if(mActiveTools.begin(), mActiveTools.end(), [&](const auto& tool){return pToolType == tool->getToolType();});
    if (mActiveTools.cend() != it)
    {
        return *it;
    }
    else
    {
        return nullptr;
    }
}

void PaintingArea::searchRects(const QRect& pZone, QSet<LRectangle*>& pFoundObjs)
{
    mQuadtree.search(pZone, pFoundObjs);
}
