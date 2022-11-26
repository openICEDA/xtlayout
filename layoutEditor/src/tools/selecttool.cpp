#include "selecttool.h"

SelectTool::SelectTool(PaintingArea *pPA):mPA(pPA)
{

}

void SelectTool::mousePressEvent(QMouseEvent *event)
{

}

void SelectTool::mouseMoveEvent(QMouseEvent *event)
{
//    if(nullptr != mRectangle)
//    {
//        mRectangle->setSecondPoint(event->pos());
//        mPA->update();
//    }
}

void SelectTool::mouseReleaseEvent(QMouseEvent *event)
{
//    delete mRectangle;
//    CommandControl::getInstance()->pushCommand(new DrawCommand(new Rectangle(mFirstPoint,mSecondPoint)));
}

void SelectTool::keyPressEvent(QKeyEvent *event)
{
//    switch(event->key())
//    {
//        case Qt::Key_Escape:
//            mPA->deleteVisualEntity(mRectangle);
//            break;
//        default:
//            break;
//    }
}
