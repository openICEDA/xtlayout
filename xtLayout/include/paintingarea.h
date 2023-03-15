#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <vector>
#include "quadtreenode.h"
#include "xtdb.h"
#include "lrectangle.h"
#include "tool.h"

class VisualEntity;
class PaintingArea : public QWidget
{
    Q_OBJECT
private:
    std::vector<Tool*> mActiveTools;//TODO: rename to ToolInsts, tool should have a state to indicate whether it is active or not
    QSet<VisualEntity*> mAllVisualEntities; //TODO:change to vector, since iteration is much more frequent than searching
    QuadtreeNode<LRectangle*> mQuadtree;
public:
    xtdb::XtBlock* mBlock; //TODO: fileio
    explicit PaintingArea(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void insertVisualEntity(VisualEntity* pVisualEntity);
    void removeVisualEntity(VisualEntity* pVisualEntity);
    QSet<VisualEntity*>& getAllVisualEntities(){return mAllVisualEntities;};
    void activateTool(Tool* pTool);
    void deactivateTool(Tool::tool_type pTool);
    Tool* findActiveTool(Tool::tool_type pTool);
    std::vector<Tool*>& getActiveTools(){return mActiveTools;};
    QuadtreeNode<LRectangle*>& getQuadTree(){return mQuadtree;};
    void searchRects(const QRect& pZone, QSet<LRectangle*>& pFoundObjs);
};
#endif // PAINTINGAREA_H
