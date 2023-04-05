#include "selectiontool.h"
#include "navigationtool.h"
#include <QMouseEvent>
#include <memory>
#include <QDebug>
#include "xtliterals.h"

SelectionTool::SelectionTool():mIsPressed(false), Tool(SELECTION_TOOL), mSelectionBox(nullptr)
{
}

SelectionTool::~SelectionTool()
{
}

void SelectionTool::mousePressEvent(QMouseEvent* event, PaintingArea* pPA)
{
    mIsPressed = true;
    mSelectionBox = new SelectionBox;
    mFirstPointViewportCS = event->pos();
    pPA->insertVisualEntity(mSelectionBox);
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA)
{
    if (mIsPressed)
    {
        QPoint secondpnt = NavigationTool::viewportCS2WorldCS(event->pos(), pPA);
        QPoint firstpnt = NavigationTool::viewportCS2WorldCS(mFirstPointViewportCS, pPA);
        mSelectionBox->setFirstPoint(firstpnt);
        mSelectionBox->setSecondPoint(secondpnt);
        QSet<LShape*> shapesInLeftOuterRegion;
        QSet<LShape*> shapesInRightOuterRegion;
        QSet<LShape*> shapesInUpperOuterRegion;
        QSet<LShape*> shapesInBottomOuterRegion;
        QRect leftOuterRegion(NavigationTool::viewportCS2WorldCS({0, 0}, pPA), NavigationTool::viewportCS2WorldCS({mFirstPointViewportCS.x(), pPA->geometry().height()}, pPA));
        QRect rightOuterRegion(NavigationTool::viewportCS2WorldCS({secondpnt.x(), 0}, pPA), NavigationTool::viewportCS2WorldCS({pPA->geometry().width(), pPA->geometry().height()}, pPA));
        QRect upperOuterRegion(NavigationTool::viewportCS2WorldCS({mFirstPointViewportCS.x(), 0}, pPA), NavigationTool::viewportCS2WorldCS({secondpnt.x(), mFirstPointViewportCS.y()}, pPA));
        QRect bottomOuterRegion(NavigationTool::viewportCS2WorldCS({mFirstPointViewportCS.x(), secondpnt.y()}, pPA), NavigationTool::viewportCS2WorldCS({secondpnt.x(), pPA->geometry().height()}, pPA));
        pPA->searchShapes(leftOuterRegion, shapesInLeftOuterRegion);
        pPA->searchShapes(rightOuterRegion, shapesInRightOuterRegion);
        pPA->searchShapes(upperOuterRegion, shapesInUpperOuterRegion);
        pPA->searchShapes(bottomOuterRegion, shapesInBottomOuterRegion);
        std::for_each(shapesInLeftOuterRegion.begin(), shapesInLeftOuterRegion.end(), [](LShape* shape){shape->deselect();});
        std::for_each(shapesInRightOuterRegion.begin(), shapesInRightOuterRegion.end(), [](LShape* shape){shape->deselect();});
        std::for_each(shapesInUpperOuterRegion.begin(), shapesInUpperOuterRegion.end(), [](LShape* shape){shape->deselect();});
        std::for_each(shapesInBottomOuterRegion.begin(), shapesInBottomOuterRegion.end(), [](LShape* shape){shape->deselect();});
        pPA->searchShapes(mSelectionBox->getZone(), mSelectedObjs);
        std::for_each(mSelectedObjs.begin(), mSelectedObjs.end(), [](LShape* shape){shape->select();});
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
