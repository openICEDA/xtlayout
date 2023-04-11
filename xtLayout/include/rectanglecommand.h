#ifndef RECTANGLECOMMAND_H
#define RECTANGLECOMMAND_H

#include <QUndoCommand>
class LBlock;
class LRectangle;
class RectangleCommand : public QUndoCommand
{
private:
    int x1;
    int y1;
    int x2;
    int y2;
    LBlock* mBlock;
    LRectangle* mRect;
public:
    RectangleCommand(LRectangle* pRect);
    void undo() override;
    void redo() override;
};

#endif // RECTANGLECOMMAND_H
