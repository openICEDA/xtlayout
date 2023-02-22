#include "selectiontool.h"
#include <QMouseEvent>
#include <memory>
#include <QDebug>

SelectionTool::SelectionTool(PaintingArea *pPA):mIsPressed(false), mPA(pPA), Tool(SELECTION_TOOL)
{
    mSelectionBox = new SelectionBox(); //do not use this raw pointer to initialize another shared_ptr by shared_ptr::reset().
    pPA->insertVisualEntity(mSelectionBox);
}

void SelectionTool::mousePressEvent(QMouseEvent *event)
{
    mIsPressed = true;
    mFirstPoint = event->pos();
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event)
{
    if (mIsPressed)
    {
        mPA->getQuadTree().search(mSelectionBox->getZone(), mSelectedObjs);
        for(typename QSet<LERectangle*>::iterator it = mSelectedObjs.begin(); it != mSelectedObjs.end(); it++)
        {
            (*it)->setSelected(true);
        }
        QSet<VisualEntity*>& allVisualEntities = mPA->getAllVisualEntities();

        mSelectionBox->setFirstPoint(mFirstPoint);
        mSelectionBox->setSecondPoint(event->pos());
        mPA->update();
    }
}

void SelectionTool::mouseReleaseEvent(QMouseEvent *event)
{
    resetSelectionBox();
    mPA->update();
//    delete mRectangle;
//    CommandControl::getInstance()->pushCommand(new DrawCommand(new Rectangle(mFirstPoint,mSecondPoint)));
}

void SelectionTool::resetSelectionBox()
{
    mSelectionBox->reset();
    mIsPressed = false;
}

void SelectionTool::keyPressEvent(QKeyEvent *event)
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
