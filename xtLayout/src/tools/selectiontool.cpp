#include "selectiontool.h"
#include "navigationtool.h"
#include <QMouseEvent>
#include <memory>
#include <QDebug>

SelectionTool::SelectionTool(PaintingArea* pPA, NavigationTool* pNavTool):mIsPressed(false), mPA(pPA), Tool(SELECTION_TOOL), mSelectionBox(nullptr), mNavTool(pNavTool)
{
}

SelectionTool::~SelectionTool()
{
}

void SelectionTool::mousePressEvent(QMouseEvent* event)
{
    mIsPressed = true;
    mSelectionBox = new SelectionBox(mNavTool);
    mFirstPoint = mNavTool->viewportCS2WorldCS(event->pos());
    mPA->insertVisualEntity(mSelectionBox);
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event)
{
    if (mIsPressed)
    {//TODO: deselect a selected object when the selection box doesn't contain the object.
        mPA->getQuadTree().search(mSelectionBox->getZone(), mSelectedObjs);
        for(typename QSet<LRectangle*>::iterator it = mSelectedObjs.begin(); it != mSelectedObjs.end(); it++)
        {
            (*it)->setSelected(true);
        }
        QSet<VisualEntity*>& allVisualEntities = mPA->getAllVisualEntities();

        mSelectionBox->setFirstPoint(mFirstPoint);
        mSelectionBox->setSecondPoint(mNavTool->viewportCS2WorldCS(event->pos()));
        mPA->update();
    }
}

void SelectionTool::mouseReleaseEvent(QMouseEvent* event)
{
    if (mSelectionBox) {
        mPA->removeVisualEntity(mSelectionBox);
        delete mSelectionBox;
        mSelectionBox = nullptr;
    }
    mIsPressed = false;
    mPA->update();
}

void SelectionTool::resetSelectionBox()
{
    mSelectionBox->reset();
    mIsPressed = false;
}

void SelectionTool::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            for (QSet<LRectangle*>::Iterator it_sel = mSelectedObjs.begin(); it_sel != mSelectedObjs.end(); it_sel++)
            {
                mPA->removeVisualEntity(*it_sel);
                delete *it_sel;
            }
            mSelectedObjs.clear();
            mPA->update();
            break;
        default:
            break;
    }
}
