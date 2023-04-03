#ifndef SELECTTOOL_H
#define SELECTTOOL_H
#include "tool.h"
#include "paintingarea.h"
#include <memory>
#include "selectionbox.h"
#include "xtshapequery.h"

class LShape;
class SelectionTool : public Tool
{
private:
    bool mIsPressed;
    QPoint mFirstPoint;
    QSet<LShape*> mSelectedObjs;
    SelectionBox* mSelectionBox;
    NavigationTool* mNavTool;
public:
    SelectionTool(PaintingArea* pPA, NavigationTool* pNavTool);
    ~SelectionTool() override;
    void mousePressEvent(QMouseEvent* event, PaintingArea* pPA) override;
    void mouseMoveEvent(QMouseEvent* event, PaintingArea* pPA) override;
    void mouseReleaseEvent(QMouseEvent* event, PaintingArea* pPA) override;
    void keyPressEvent(QKeyEvent* event, PaintingArea* pPA) override;
    bool isPressed(){return mIsPressed;};
};

#endif // SELECTTOOL_H
