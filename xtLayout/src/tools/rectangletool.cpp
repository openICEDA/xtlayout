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
RectangleTool::RectangleTool(PaintingArea* pPA, NavigationTool* pNavTool):mFirstPointFixed(false), Tool(RECTANGLE_TOOL), mRectangle(nullptr), mNavTool(pNavTool)
{

}

RectangleTool::~RectangleTool()
{
}

void RectangleTool::mousePressEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (!mFirstPointFixed)
    {
        pPA->setMouseTracking(true);
        mFirstPointFixed = true;
        mRectangle = new LRectangle(mNavTool);
        mRectangle->setFirstPoint(mNavTool->viewportCS2WorldCS(event->pos()));
        mRectangle->setSecondPoint(mNavTool->viewportCS2WorldCS(event->pos()));
        pPA->insertVisualEntity(mRectangle);
    }
    else
    {
        mRectangle->setSecondPoint(mNavTool->viewportCS2WorldCS(event->pos()));
        mRectangle->storeToDB(pPA->getBlock());
        pPA->setMouseTracking(false);
        emit completed();
    }
}

void RectangleTool::mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (mRectangle)
    {
        mRectangle->setSecondPoint(mNavTool->viewportCS2WorldCS(event->pos()));
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


