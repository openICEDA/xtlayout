#include "rectangletool.h"
#include "navigationtool.h"
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "commandcontrol.h"
#include "drawcommand.h"
#include "paintingarea.h"
#include "xtdb.h"
#include "lrectangle.h"
#include <iostream>
using namespace xtdb;
RectangleTool::RectangleTool(PaintingArea* pPA):mFirstPointFixed(false), Tool(RECTANGLE_TOOL), mRectangle(nullptr)
{

}

RectangleTool::~RectangleTool()
{
    //Don't delete mRectangle here, since mRectangle is inserted into allvisualentities
}

void RectangleTool::mousePressEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (!mFirstPointFixed)
    {
        pPA->setMouseTracking(true);
        mFirstPointFixed = true;
        mRectangle = new LRectangle;
        mRectangle->setFirstPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pPA));
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pPA));
        pPA->insertVisualEntity(mRectangle);
    }
    else
    {
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pPA));
        mRectangle->storeToDB(pPA->getBlock());
        pPA->setMouseTracking(false);
        emit completed();
    }
}

void RectangleTool::mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (mRectangle)
    {
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pPA));
        pPA->update();
    }
}

void RectangleTool::mouseReleaseEvent(QMouseEvent* event, PaintingArea* pPA)
{
//    delete mRectangle;
//    CommandControl::getInstance()->pushCommand(new DrawCommand(new Rectangle(mFirstPoint,mSecondPoint)));
}

void RectangleTool::keyPressEvent(QKeyEvent* event, PaintingArea* pPA)
{
    //TODO: esc to stop tool
    switch(event->key())
    {
        case Qt::Key_Escape:
            if (mRectangle)
            {
                //delete mRectangle, since it is not stored into database yet, no need to destroy
                pPA->removeVisualEntity(mRectangle);
                delete mRectangle;
                mRectangle = nullptr;
                mFirstPointFixed = false;
                pPA->update();
            }
            break;
        default:
            break;
    }
}


