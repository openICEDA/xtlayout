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
    QPoint mFirstPointViewportCS;
    SelectionBox* mSelectionBox;
public:
    SelectionTool();
    ~SelectionTool() override;
    void mousePressEvent(QMouseEvent* event, LBlock* pBlock) override;
    void mouseMoveEvent(QMouseEvent* event, LBlock* pBlock) override;
    void mouseReleaseEvent(QMouseEvent* event, LBlock* pBlock) override;
    void keyPressEvent(QKeyEvent* event, LBlock* pBlock) override;
    bool isPressed(){return mIsPressed;};
};

#endif // SELECTTOOL_H
