#include "selectiontool.h"
#include "navigationtool.h"
#include <QMouseEvent>
#include <memory>
#include <QDebug>

SelectionTool::SelectionTool(PaintingArea* pPA, NavigationTool* pNavTool):mIsPressed(false), Tool(SELECTION_TOOL), mSelectionBox(nullptr), mNavTool(pNavTool)
{
}

SelectionTool::~SelectionTool()
{
}

void SelectionTool::mousePressEvent(QMouseEvent* event, PaintingArea* pPA)
{
    mIsPressed = true;
    mSelectionBox = new SelectionBox(mNavTool);
    mFirstPoint = mNavTool->viewportCS2WorldCS(event->pos());
    pPA->insertVisualEntity(mSelectionBox);
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (mIsPressed)
    {//TODO: deselect a selected object when the selection box doesn't contain the object.
        pPA->getQuadTree().search(mSelectionBox->getZone(), mSelectedObjs);
        for(typename QSet<LRectangle*>::iterator it = mSelectedObjs.begin(); it != mSelectedObjs.end(); it++)
        {
            (*it)->setSelected(true);
        }
        QSet<VisualEntity*>& allVisualEntities = pPA->getAllVisualEntities();

        mSelectionBox->setFirstPoint(mFirstPoint);
        mSelectionBox->setSecondPoint(mNavTool->viewportCS2WorldCS(event->pos()));
        pPA->update();
    }
}

void SelectionTool::mouseReleaseEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (mSelectionBox) {
        pPA->removeVisualEntity(mSelectionBox);
        delete mSelectionBox;
        mSelectionBox = nullptr;
    }
    mIsPressed = false;
    pPA->update();
}

void SelectionTool::resetSelectionBox()
{
    mSelectionBox->reset();
    mIsPressed = false;
}

void SelectionTool::keyPressEvent(QKeyEvent* event, PaintingArea* pPA)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            for (QSet<LRectangle*>::Iterator it_sel = mSelectedObjs.begin(); it_sel != mSelectedObjs.end(); it_sel++)
            {
                pPA->removeVisualEntity(*it_sel);
                delete *it_sel;
            }
            mSelectedObjs.clear();
            pPA->update();
            break;
        default:
            break;
    }
}
