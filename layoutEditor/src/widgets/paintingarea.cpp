#include "paintingarea.h"
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QDebug>
#include "tool.h"
#include "visualentity.h"
#include "grid.h"
#include "rectangle.h"
#include "quadtreenode.h"
#include "globalsetting.h"
PaintingArea::PaintingArea(QWidget *parent)
    : QWidget{parent}, mTool(nullptr), mQuadtree(0, QRect(QPoint(0, 0), GlobalSetting::canvasSize))
{
    insertVisualEntity(new Grid);
    QuadtreeNode<Rectangle> qtn(2, QRect(0,0,200,200));
    qtn.insert(QSharedPointer<Rectangle>(new Rectangle(0, 0, 50, 50)));
    qtn.insert(QSharedPointer<Rectangle>(new Rectangle(50, 50, 50, 50)));
    qtn.insert(QSharedPointer<Rectangle>(new Rectangle(100, 100, 50, 50)));

    QList<Rectangle*> res;
    qtn.getAllObjsOfSubtree(res);
    for(typename QList<Rectangle*>::iterator it = res.begin(); it != res.end(); it++)
    {
        insertVisualEntity((*it));
    }

    update();
}

void PaintingArea::paintEvent(QPaintEvent *)
{
    //TODO: Seperate the drawer
    QPainter painter(this);
    QPen pen;
    pen.setBrush(QBrush(QColor(0,255,0,255)));
    painter.setPen(pen);

    QSet<QSharedPointer<VisualEntity>>::const_iterator visualEntityIter = mAllVisualEntities.constBegin();
    while (visualEntityIter != mAllVisualEntities.constEnd()) {
        (*visualEntityIter)->draw(&painter);
        ++visualEntityIter;
    }
}

void PaintingArea::mousePressEvent(QMouseEvent *event)
{
    if(nullptr != mTool)
    {
        mTool->mousePressEvent(event);
    }
}

void PaintingArea::mouseMoveEvent(QMouseEvent *event)
{
    if(nullptr != mTool)
    {
        mTool->mouseMoveEvent(event);
    }
}

void PaintingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(nullptr != mTool)
    {
        mTool->mouseReleaseEvent(event);
    }
}

void PaintingArea::insertVisualEntity(VisualEntity *pVisualEntity)
{
    QSharedPointer<VisualEntity> tempVisualEntity;
    tempVisualEntity.reset(pVisualEntity);
    mAllVisualEntities.insert(std::move(tempVisualEntity));
}

void PaintingArea::deleteVisualEntity(VisualEntity *pVisualEntity)
{
    mAllVisualEntities.erase(mAllVisualEntities.find(QSharedPointer<VisualEntity>(pVisualEntity)));
//    mQuadtree.erase(mAllVisualEntities.find(pVisualEntity));
}

void PaintingArea::deleteTool()
{
    delete mTool;
    mTool = nullptr;
}
