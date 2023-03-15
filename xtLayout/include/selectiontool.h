#ifndef SELECTTOOL_H
#define SELECTTOOL_H
#include "tool.h"
#include "paintingarea.h"
#include <memory>
#include "selectionbox.h"
#include "lrectangle.h"

class SelectionTool: public Tool
{
private:
    bool mIsPressed;
    QPoint mFirstPoint;
    QSet<LRectangle*> mSelectedObjs;
    PaintingArea* mPA;
    SelectionBox* mSelectionBox;
    NavigationTool* mNavTool;
public:
    SelectionTool(PaintingArea* pPA, NavigationTool* pNavTool);
    ~SelectionTool() override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    bool isPressed(){return mIsPressed;};
    void resetSelectionBox();
};

#endif // SELECTTOOL_H
