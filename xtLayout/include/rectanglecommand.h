#ifndef RECTANGLECOMMAND_H
#define RECTANGLECOMMAND_H

#include <QUndoCommand>
class LBlock;
class LRectangle;
class RectangleCommand : public QUndoCommand
{
private:
    LRectangle* mRect;
public:
    RectangleCommand(int pX1, int pY1, int pX2, int pY2, LBlock* pBlock);
    void undo() override;
    void redo() override;
};

#endif // RECTANGLECOMMAND_H
