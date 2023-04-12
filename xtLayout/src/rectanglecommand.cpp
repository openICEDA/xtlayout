#include "rectanglecommand.h"
#include "lrectangle.h"
#include "lblock.h"
#include "paintingarea.h"
#include <QDebug>

RectangleCommand::RectangleCommand(LRectangle* pRect):mRect(pRect)
{
    mBlock = pRect->getBlock();
    x1 = pRect->x1;
    y1 = pRect->y1;
    x2 = pRect->x2;
    y2 = pRect->y2;
}

void RectangleCommand::undo()
{
    if (mRect)
    {
        delete mRect;
        mRect = nullptr;
    }
    mBlock->getPaintingArea()->update();
}

void RectangleCommand::redo()
{
    if (!mRect)
    {
        mRect = new LRectangle(x1, y1, x2, y2, mBlock);
        mRect->syncToDB();
        mBlock->insertVisualEntityInViewport(mRect);
    }
    mBlock->getPaintingArea()->update();
}
