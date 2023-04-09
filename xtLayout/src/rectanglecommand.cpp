#include "rectanglecommand.h"
#include "lrectangle.h"
#include "lblock.h"

RectangleCommand::RectangleCommand(int pX1, int pY1, int pX2, int pY2, LBlock* pBlock):mRect(new LRectangle(pX1, pY1, pX2, pY2, pBlock))
{
}

void RectangleCommand::undo()
{
    delete mRect;
}

void RectangleCommand::redo()
{

}
