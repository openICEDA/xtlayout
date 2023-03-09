#ifndef NAVIGATIONTOOL_H
#define NAVIGATIONTOOL_H
#include "tool.h"
class PaintingArea;
class LRectangle;
class navigationTool : public Tool
{
private:
    PaintingArea* mPA;
    LRectangle* mViewport;
public:
    navigationTool();
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // NAVIGATIONTOOL_H
