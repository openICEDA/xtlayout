#include "drawcommand.h"
#include <QPainter>
DrawCommand::DrawCommand(Shape *pShape)
    :mShape(pShape)
{

}

void DrawCommand::execute()
{
}

void DrawCommand::undo()
{

}

void DrawCommand::redo()
{

}
