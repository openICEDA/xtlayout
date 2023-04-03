#include "navigationtool.h"
#include <QKeyEvent>
#include "utility.h"
#include "paintingarea.h"
#include "visualentity.h"

NavigationTool::NavigationTool():Tool(NAVIGATION_TOOL)
{
}

void NavigationTool::keyPressEvent(QKeyEvent* event, PaintingArea* pPA)
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
    QPoint movedFirstPnt = MatUtil::translate(moveVector, pPA->getViewport().topLeft());
    QPoint movedSecondPnt = MatUtil::translate(moveVector, pPA->getViewport().bottomRight());
    pPA->setViewport({movedFirstPnt, movedSecondPnt});
    QSet<LShape*> shapesInViewport;
    pPA->searchShapes(pPA->getViewport(), shapesInViewport);
    QSet<VisualEntity*>& av = pPA->getAllVisualEntities();
    av.clear();
    for (QSet<LShape*>::const_iterator it = shapesInViewport.cbegin(); it != shapesInViewport.cend(); it++)
    {
        av.insert(*it);
    }
    pPA->update();
}

QPoint NavigationTool::viewportCS2WorldCS(const QPoint& pPnt, PaintingArea* pPA)
{
    return pPnt + pPA->getViewport().topLeft(); //TODO: consider scalation
}

QRect NavigationTool::viewportCS2WorldCS(const QRect& pRects, PaintingArea* pPA)
{
    return QRect(pRects.topLeft() + pPA->getViewport().topLeft(), pRects.bottomRight() + pPA->getViewport().topLeft()); //TODO: consider scaling
}

std::vector<QPoint> NavigationTool::viewportCS2WorldCS(const std::vector<QPoint>& pPnts, PaintingArea* pPA)
{
    std::vector<QPoint> pntsInWorldCS;
    pntsInWorldCS.reserve(pPnts.size());
    std::for_each(pntsInWorldCS.cbegin(), pntsInWorldCS.cend(), [&](auto& pnt){pntsInWorldCS.push_back(viewportCS2WorldCS(pnt, pPA));});
    return pntsInWorldCS; //TODO: consider scalation
}

QPoint NavigationTool::worldCS2ViewportCS(const QPoint& pPnt, PaintingArea* pPA)
{
    return pPnt - pPA->getViewport().topLeft(); //TODO: consider scalation
}

QRect NavigationTool::worldCS2ViewportCS(const QRect& pRects, PaintingArea* pPA)
{
    return QRect(pRects.topLeft() - pPA->getViewport().topLeft(), pRects.bottomRight() - pPA->getViewport().topLeft()); //TODO: consider scaling
}

std::vector<QPoint> NavigationTool::worldCS2ViewportCS(const std::vector<QPoint>& pPnts, PaintingArea* pPA)
{
    std::vector<QPoint> pntsInWorldCS;
    pntsInWorldCS.reserve(pPnts.size());
    std::for_each(pntsInWorldCS.cbegin(), pntsInWorldCS.cend(), [&](auto& pnt){pntsInWorldCS.push_back(worldCS2ViewportCS(pnt, pPA));});
    return pntsInWorldCS; //TODO: consider scalation
}

