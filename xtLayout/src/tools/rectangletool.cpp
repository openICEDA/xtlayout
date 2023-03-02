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
#include "lerectangle.h"

using namespace xtdb;
RectangleTool::RectangleTool(PaintingArea* pPA):mFirstPointFixed(false), mPA(pPA), Tool(RECTANGLE_TOOL), mRectangle(nullptr)
{

}

void RectangleTool::mousePressEvent(QMouseEvent* event)
{
    if(!mFirstPointFixed)
    {
        mPA->setMouseTracking(true);
        mFirstPointFixed = true;
        mRectangle = new LERectangle(XtRectangle::create(mPA->mBlock));
        mRectangle->setFirstPoint(event->pos());
        mPA->insertVisualEntity(mRectangle);
        mPA->getQuadTree().insert(mRectangle);
    }
    else
    {
        mPA->setMouseTracking(false);
        mRectangle = nullptr;
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
            mPA->deleteVisualEntity(mRectangle);
            mPA->update();
            break;
        default:
            break;
    }
}


