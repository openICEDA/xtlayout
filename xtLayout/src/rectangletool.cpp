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
#include "rectanglecommand.h"
#include "mainwindow.h"
#include <QUndoStack>
#include "rectanglecommand.h"

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
        mRectangle = new LRectangle(pBlock);
        mRectangle->setFirstPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
        pBlock->insertVisualEntityInViewport(mRectangle);
    }
    else
    {
        mRectangle->setSecondPoint(NavigationTool::viewportCS2WorldCS(event->pos(), pBlock));
//       pBlock->getPaintingArea()->getMainWindow()->getUndoStack()->push(new RectangleCommand(mRectangle));
        mRectangle->syncToDB();
        pBlock->getPaintingArea()->setMouseTracking(false);        
        emit completed(mRectangle);
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
                pBlock->removeVisualEntityInViewport(mRectangle);
                delete mRectangle;
                mRectangle = nullptr;
                mFirstPointFixed = false;
            }
            break;
        default:
            break;
    }
}


