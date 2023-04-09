#include "selectiontool.h"
#include "navigationtool.h"
#include <QMouseEvent>
#include <memory>
#include <QDebug>
#include "xtliterals.h"
#include "lblock.h"
#include "lshape.h"

SelectionTool::SelectionTool():mIsPressed(false), Tool(SELECTION_TOOL), mSelectionBox(nullptr)
{
}

SelectionTool::~SelectionTool()
{
}

void SelectionTool::mousePressEvent(QMouseEvent* event, LBlock* pBlock)
{
    mIsPressed = true;
    mSelectionBox = new SelectionBox;
    mFirstPointViewportCS = event->pos();
    pBlock->insertVisualEntity(mSelectionBox);
}

void SelectionTool::mouseMoveEvent(QMouseEvent* event, LBlock* pBlock)
{
    if (mIsPressed)
    {
        QPoint secondpnt = NavigationTool::viewportCS2WorldCS(event->pos(), pBlock);
        QPoint firstpnt = NavigationTool::viewportCS2WorldCS(mFirstPointViewportCS, pBlock);
        mSelectionBox->setFirstPoint(firstpnt);
        mSelectionBox->setSecondPoint(secondpnt);
        QSet<LShape*> shapesInLeftOuterRegion;
        QSet<LShape*> shapesInRightOuterRegion;
        QSet<LShape*> shapesInUpperOuterRegion;
        QSet<LShape*> shapesInBottomOuterRegion;
        QRect leftOuterRegion(NavigationTool::viewportCS2WorldCS({0, 0}, pBlock), NavigationTool::viewportCS2WorldCS({mFirstPointViewportCS.x(), pBlock->getViewport().height()}, pBlock));
        QRect rightOuterRegion(NavigationTool::viewportCS2WorldCS({secondpnt.x(), 0}, pBlock), NavigationTool::viewportCS2WorldCS({pBlock->getViewport().width(), pBlock->getViewport().height()}, pBlock));
        QRect upperOuterRegion(NavigationTool::viewportCS2WorldCS({mFirstPointViewportCS.x(), 0}, pBlock), NavigationTool::viewportCS2WorldCS({secondpnt.x(), mFirstPointViewportCS.y()}, pBlock));
        QRect bottomOuterRegion(NavigationTool::viewportCS2WorldCS({mFirstPointViewportCS.x(), secondpnt.y()}, pBlock), NavigationTool::viewportCS2WorldCS({secondpnt.x(), pBlock->getViewport().height()}, pBlock));
        pBlock->searchShapes(leftOuterRegion, shapesInLeftOuterRegion);
        pBlock->searchShapes(rightOuterRegion, shapesInRightOuterRegion);
        pBlock->searchShapes(upperOuterRegion, shapesInUpperOuterRegion);
        pBlock->searchShapes(bottomOuterRegion, shapesInBottomOuterRegion);
        std::for_each(shapesInLeftOuterRegion.begin(), shapesInLeftOuterRegion.end(), [](LShape* shape){shape->deselect();});
        std::for_each(shapesInRightOuterRegion.begin(), shapesInRightOuterRegion.end(), [](LShape* shape){shape->deselect();});
        std::for_each(shapesInUpperOuterRegion.begin(), shapesInUpperOuterRegion.end(), [](LShape* shape){shape->deselect();});
        std::for_each(shapesInBottomOuterRegion.begin(), shapesInBottomOuterRegion.end(), [](LShape* shape){shape->deselect();});
        pBlock->selectShapesInZone(mSelectionBox->getZone());
    }
}

void SelectionTool::mouseReleaseEvent(QMouseEvent* event, LBlock* pBlock)
{
    if (mSelectionBox) {
        pBlock->removeVisualEntity(mSelectionBox);
        delete mSelectionBox;
        mSelectionBox = nullptr;
    }
    mIsPressed = false;
}

void SelectionTool::keyPressEvent(QKeyEvent* event, LBlock* pBlock)
{
    switch(event->key())
    {
        case Qt::Key_Delete:
            pBlock->deleteSelectedShapes();
            break;
        default:
            break;
    }
}
