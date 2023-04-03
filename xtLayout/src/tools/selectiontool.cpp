#include "selectiontool.h"
#include "navigationtool.h"
#include <QMouseEvent>
#include <memory>
#include <QDebug>
#include "xtliterals.h"

SelectionTool::SelectionTool(PaintingArea* pPA, NavigationTool* pNavTool):mIsPressed(false), Tool(SELECTION_TOOL), mSelectionBox(nullptr), mNavTool(pNavTool)
{
}

SelectionTool::~SelectionTool()
{
}

void SelectionTool::mousePressEvent(QMouseEvent* event, PaintingArea* pPA)
{
    mIsPressed = true;
    mSelectionBox = new SelectionBox;
    mFirstPoint = NavigationTool::viewportCS2WorldCS(event->pos(), pPA);
    pPA->insertVisualEntity(mSelectionBox);
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (mIsPressed)
    {//TODO: deselect selected objects when the selection box doesn't contain them.
        QPoint secondpnt = NavigationTool::viewportCS2WorldCS(event->pos(), pPA);
        QSet<VisualEntity*>& allVisualEntities = pPA->getAllVisualEntities();
        mSelectionBox->setFirstPoint(mFirstPoint);
        mSelectionBox->setSecondPoint(secondpnt);
        pPA->searchShapes(mSelectionBox->getZone(), mSelectedObjs);
        for (QSet<LShape*>::Iterator it_sel = mSelectedObjs.begin(); it_sel != mSelectedObjs.end(); it_sel++)
        {
            (*it_sel)->select();
        }
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

void SelectionTool::keyPressEvent(QKeyEvent* event, PaintingArea* pPA)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            for (QSet<LShape*>::Iterator it_sel = mSelectedObjs.begin(); it_sel != mSelectedObjs.end(); it_sel++)
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
