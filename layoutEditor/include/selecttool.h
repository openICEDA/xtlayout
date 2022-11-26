#ifndef SELECTTOOL_H
#define SELECTTOOL_H
#include "tool.h"
#include "paintingarea.h"
class SelectTool: public Tool
{
public:
    SelectTool(PaintingArea *pPA);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    PaintingArea *mPA;
};

#endif // SELECTTOOL_H
