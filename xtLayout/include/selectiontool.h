#ifndef SELECTTOOL_H
#define SELECTTOOL_H
#include "tool.h"
#include "paintingarea.h"
#include <memory>
#include "selectionbox.h"
#include "lerectangle.h"

class SelectionTool: public Tool
{
public:
    SelectionTool(PaintingArea *pPA);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    bool isPressed(){return mIsPressed;};
    void resetSelectionBox();
private:
    bool mIsPressed;
    QPoint mFirstPoint;
    QSet<LERectangle*> mSelectedObjs;
    PaintingArea *mPA;
    SelectionBox *mSelectionBox;
};

#endif // SELECTTOOL_H
