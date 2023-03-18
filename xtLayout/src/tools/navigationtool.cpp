#include "navigationtool.h"
#include <QKeyEvent>
#include "utility.h"
#include "paintingarea.h"
#include "visualentity.h"

NavigationTool::NavigationTool(PaintingArea* pPA):Tool(NAVIGATION_TOOL), mPA(pPA)
{
    mViewport.setTopLeft({100, 100});
    mViewport.setBottomRight({100 + pPA->geometry().width(), 100 + pPA->geometry().height()});
}

void NavigationTool::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            QPoint resFirstPnt = MatUtil::translate(QPoint(0, -50), mViewport.topLeft());
            QPoint resSecondPnt = MatUtil::translate(QPoint(0, -50), mViewport.bottomRight());
            mViewport.setTopLeft(resFirstPnt);
            mViewport.setBottomRight(resSecondPnt);
            break;
        }
        case Qt::Key_Down:
        {
            QPoint resFirstPnt = MatUtil::translate(QPoint(0, 50), mViewport.topLeft());
            QPoint resSecondPnt = MatUtil::translate(QPoint(0, 50), mViewport.bottomRight());
            mViewport.setTopLeft(resFirstPnt);
            mViewport.setBottomRight(resSecondPnt);
            break;
        }
        case Qt::Key_Left:
        {
            QPoint resFirstPnt = MatUtil::translate(QPoint(-50, 0), mViewport.topLeft());
            QPoint resSecondPnt = MatUtil::translate(QPoint(-50, 0), mViewport.bottomRight());
            mViewport.setTopLeft(resFirstPnt);
            mViewport.setBottomRight(resSecondPnt);
            break;
        }
        case Qt::Key_Right:
        {
            QPoint resFirstPnt = MatUtil::translate(QPoint(50, 0), mViewport.topLeft());
            QPoint resSecondPnt = MatUtil::translate(QPoint(50, 0), mViewport.bottomRight());
            mViewport.setTopLeft(resFirstPnt);
            mViewport.setBottomRight(resSecondPnt);
            break;
        }
        default:
            break;
    }
    QSet<LRectangle*> rectsInViewport;
    mPA->searchRects(mViewport, rectsInViewport);
    QSet<VisualEntity*>& av = mPA->getAllVisualEntities();
    av.clear();
    for (QSet<LRectangle*>::const_iterator it = rectsInViewport.cbegin(); it != rectsInViewport.cend(); it++)
    {
        av.insert(*it);
    }
    mPA->update();
}

QPoint NavigationTool::viewportCS2WorldCS(QPoint pPnt)
{
    return pPnt + mViewport.topLeft(); //TODO: consider scalation
}

QRect NavigationTool::viewportCS2WorldCS(const QRect& pRects)
{
    return QRect(pRects.topLeft() + mViewport.topLeft(), pRects.bottomRight() + mViewport.topLeft()); //TODO: consider scaling
}

std::vector<QPoint> NavigationTool::viewportCS2WorldCS(const std::vector<QPoint>& pPnts)
{
    std::vector<QPoint> pntsInWorldCS;
    pntsInWorldCS.reserve(pPnts.size());
    std::for_each(pntsInWorldCS.cbegin(), pntsInWorldCS.cend(), [&](auto& pnt){pntsInWorldCS.push_back(viewportCS2WorldCS(pnt));});
    return pntsInWorldCS; //TODO: consider scalation
}

QPoint NavigationTool::worldCS2ViewportCS(QPoint pPnt)
{
    return pPnt - mViewport.topLeft(); //TODO: consider scalation
}

QRect NavigationTool::worldCS2ViewportCS(const QRect& pRects)
{
    return QRect(pRects.topLeft() - mViewport.topLeft(), pRects.bottomRight() - mViewport.topLeft()); //TODO: consider scaling
}

std::vector<QPoint> NavigationTool::worldCS2ViewportCS(const std::vector<QPoint>& pPnts)
{
    std::vector<QPoint> pntsInWorldCS;
    pntsInWorldCS.reserve(pPnts.size());
    std::for_each(pntsInWorldCS.cbegin(), pntsInWorldCS.cend(), [&](auto& pnt){pntsInWorldCS.push_back(worldCS2ViewportCS(pnt));});
    return pntsInWorldCS; //TODO: consider scalation
}

