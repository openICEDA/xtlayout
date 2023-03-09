#include "rectangletool.h"
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "commandcontrol.h"
#include "drawcommand.h"
#include "paintingarea.h"
#include "quadtreenode.h"
#include "xtdb.h"
#include "lrectangle.h"
#include <iostream>
using namespace xtdb;
RectangleTool::RectangleTool(PaintingArea* pPA):mFirstPointFixed(false), mPA(pPA), Tool(RECTANGLE_TOOL), mRectangle(nullptr)
{

}

RectangleTool::~RectangleTool()
{
}

void RectangleTool::mousePressEvent(QMouseEvent* event)
{
    if(!mFirstPointFixed)
    {
        mPA->setMouseTracking(true);
        mFirstPointFixed = true;
        mRectangle = new LRectangle();
        mRectangle->setFirstPoint(event->pos());
        mPA->insertVisualEntity(mRectangle);
    }
    else
    {
        mPA->getQuadTree().insert(mRectangle);
        mRectangle->storeToDB(mPA->mBlock);
        mPA->setMouseTracking(false);
        emit completed();
    }
}

void RectangleTool::mouseMoveEvent(QMouseEvent* event)
{
    if(nullptr != mRectangle)
    {
        mRectangle->setSecondPoint(event->pos());
        mPA->update();
    }
}

void RectangleTool::mouseReleaseEvent(QMouseEvent* event)
{
//    delete mRectangle;
//    CommandControl::getInstance()->pushCommand(new DrawCommand(new Rectangle(mFirstPoint,mSecondPoint)));
}

void RectangleTool::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            //delete mRectangle, since it is not stored into database yet, no need to destroy
            mPA->removeVisualEntity(mRectangle);
            mPA->update();
            break;
        default:
            break;
    }
}


