#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <QPoint>
#include <vector>
#include "quadtreenode.h"
#include "xtdb.h"
#include "lrectangle.h"
#include "tool.h"

class VisualEntity;
class PaintingArea : public QWidget
{
    Q_OBJECT
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
    void activateTool(Tool* pTool){mActiveTools.push_back(pTool);};
    void deactivateTool(Tool::tool_type pTool);
    std::vector<Tool*>& getActiveTools(){return mActiveTools;};
    QuadtreeNode<LRectangle*>& getQuadTree(){return mQuadtree;};
private:
    std::vector<Tool*> mActiveTools;
    QSet<VisualEntity*> mAllVisualEntities; //TODO:Try to involve array or vector to take advantage of cache during iteration
    QSet<VisualEntity*> mSelectedEntities;
    QuadtreeNode<LRectangle*> mQuadtree;
};
#endif // PAINTINGAREA_H
