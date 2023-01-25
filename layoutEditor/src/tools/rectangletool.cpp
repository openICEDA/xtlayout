#include "rectangletool.h"
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include "commandcontrol.h"
#include "drawcommand.h"
#include "rectangle.h"
#include "paintingarea.h"
#include "quadtreenode.h"

RectangleTool::RectangleTool(PaintingArea *pPA):mFirstPointFixed(false), mRectangle(nullptr), mPA(pPA), Tool(RECTANGLE_TOOL)
{

}

void RectangleTool::mousePressEvent(QMouseEvent *event)
{
    if(!mFirstPointFixed)
    {
        mPA->setMouseTracking(true);
        mFirstPointFixed = true;
        mRectangle = std::shared_ptr<Rectangle>(new Rectangle(event->pos(), event->pos()));
        QuadtreeNode<Rectangle> &quadtree = mPA->getQuadTree(); //TODO: it is not elegant to let custom to initialize a tree node, compare with better solution
        quadtree.insert(mRectangle);
        mPA->insertVisualEntity(mRectangle);
    }
    else
    {
        mPA->setMouseTracking(false);
        emit completed();
    }
}

void RectangleTool::mouseMoveEvent(QMouseEvent *event)
{
    if(nullptr != mRectangle)
    {
        mRectangle->setSecondPoint(event->pos());
        mPA->update();
    }
}

void RectangleTool::mouseReleaseEvent(QMouseEvent *event)
{
//    delete mRectangle;
//    CommandControl::getInstance()->pushCommand(new DrawCommand(new Rectangle(mFirstPoint,mSecondPoint)));
}

void RectangleTool::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            mPA->deleteVisualEntity(mRectangle.get());
            break;
        default:
            break;
    }
}


