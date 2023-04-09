#include "navigationtool.h"
#include <QKeyEvent>
#include "utility.h"
#include "lblock.h"
#include "visualentity.h"

NavigationTool::NavigationTool():Tool(NAVIGATION_TOOL)
{
}

void NavigationTool::keyPressEvent(QKeyEvent* event, LBlock* pBlock)
{
    QPoint moveVector;
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            moveVector = QPoint(0, -50);
            break;
        }
        case Qt::Key_Down:
        {
            moveVector = QPoint(0, 50);
            break;
        }
        case Qt::Key_Left:
        {
            moveVector = QPoint(-50, 0);
            break;
        }
        case Qt::Key_Right:
        {
            moveVector = QPoint(50, 0);
            break;
        }
        default:
            break;
    }
    QPoint movedFirstPnt = MatUtil::translate(moveVector, pBlock->getViewport().topLeft());
    QPoint movedSecondPnt = MatUtil::translate(moveVector, pBlock->getViewport().bottomRight());
    pBlock->setViewport({movedFirstPnt, movedSecondPnt});
    QSet<LShape*> shapesInViewport;
    pBlock->searchShapes(pBlock->getViewport(), shapesInViewport);
    pBlock->clearAllVisualEntities();
    for (QSet<LShape*>::const_iterator it = shapesInViewport.cbegin(); it != shapesInViewport.cend(); it++)
    {
        pBlock->insertVisualEntity(*it);
    }
}

QPoint NavigationTool::viewportCS2WorldCS(const QPoint& pPnt, LBlock* pBlock)
{
    return pPnt + pBlock->getViewport().topLeft(); //TODO: consider scalation
}

QRect NavigationTool::viewportCS2WorldCS(const QRect& pRects, LBlock* pBlock)
{
    return QRect(pRects.topLeft() + pBlock->getViewport().topLeft(), pRects.bottomRight() + pBlock->getViewport().topLeft()); //TODO: consider scaling
}

std::vector<QPoint> NavigationTool::viewportCS2WorldCS(const std::vector<QPoint>& pPnts, LBlock* pBlock)
{
    std::vector<QPoint> pntsInWorldCS;
    pntsInWorldCS.reserve(pPnts.size());
    std::for_each(pntsInWorldCS.cbegin(), pntsInWorldCS.cend(), [&](auto& pnt){pntsInWorldCS.push_back(viewportCS2WorldCS(pnt, pBlock));});
    return pntsInWorldCS; //TODO: consider scalation
}

QPoint NavigationTool::worldCS2ViewportCS(const QPoint& pPnt, LBlock* pBlock)
{
    return pPnt - pBlock->getViewport().topLeft(); //TODO: consider scalation
}

QRect NavigationTool::worldCS2ViewportCS(const QRect& pRects, LBlock* pBlock)
{
    return QRect(pRects.topLeft() - pBlock->getViewport().topLeft(), pRects.bottomRight() - pBlock->getViewport().topLeft()); //TODO: consider scaling
}

std::vector<QPoint> NavigationTool::worldCS2ViewportCS(const std::vector<QPoint>& pPnts, LBlock* pBlock)
{
    std::vector<QPoint> pntsInWorldCS;
    pntsInWorldCS.reserve(pPnts.size());
    std::for_each(pntsInWorldCS.cbegin(), pntsInWorldCS.cend(), [&](auto& pnt){pntsInWorldCS.push_back(worldCS2ViewportCS(pnt, pBlock));});
    return pntsInWorldCS; //TODO: consider scalation
}

