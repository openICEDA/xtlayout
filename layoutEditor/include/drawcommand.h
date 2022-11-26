#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include "command.h"
class Shape;
class QPainter;
class DrawCommand: public Command
{
public:
    DrawCommand(Shape *pShape);
    void execute();
    void undo();
    void redo();
private:
    Shape *mShape;
};

#endif // DRAWCOMMAND_H
