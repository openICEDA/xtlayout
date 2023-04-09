#include "rectangletool.h"
#include "navigationtool.h"
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include "lblock.h"
#include "xtdb.h"
#include "lrectangle.h"
#include <iostream>
#include "paintingarea.h"

using namespace xtdb;
RectangleTool::RectangleTool(PaintingArea* pBlock):mFirstPointFixed(false), Tool(RECTANGLE_TOOL), mRectangle(nullptr)
{

}

RectangleTool::~RectangleTool()
{
    //Don't delete mRectangle here, since mRectangle is inserted into allvisualentities
}

void RectangleTool::mousePressEvent(QMouseEvent* event, LBlock* pBlock)
{
    if (!mFirstPointFixed)
    {
        pBlock->getPaintingArea()->setMouseTracking(true);
        mFirstPointFixed = true;
        mRectangle = new LRectangle;
        mRectangle->setFirstPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
        pBlock->insertVisualEntity(mRectangle);
    }
    else
    {
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
        mRectangle->storeToDB(pBlock->getBlock());
        pBlock->getPaintingArea()->setMouseTracking(false);
        emit completed();
    }
}

void RectangleTool::mouseMoveEvent(QMouseEvent* event, LBlock* pBlock)
{
    if (mRectangle)
    {
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
    }
}

void RectangleTool::mouseReleaseEvent(QMouseEvent* event, LBlock* pBlock)
{
//    delete mRectangle;
//    CommandControl::getInstance()->pushCommand(new DrawCommand(new Rectangle(mFirstPoint,mSecondPoint)));
}

void RectangleTool::keyPressEvent(QKeyEvent* event, LBlock* pBlock)
{
    //TODO: esc to stop tool
    switch(event->key())
    {
        case Qt::Key_Escape:
            if (mRectangle)
            {
                //delete mRectangle, since it is not stored into database yet, no need to destroy
                pBlock->removeVisualEntity(mRectangle);
                delete mRectangle;
                mRectangle = nullptr;
                mFirstPointFixed = false;
            }
            break;
        default:
            break;
    }
}


