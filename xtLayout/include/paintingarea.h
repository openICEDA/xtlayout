#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <QPoint>
#include "quadtreenode.h"
#include "xtdb.h"
#include "lerectangle.h"

class Tool;
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
    void deleteVisualEntity(VisualEntity* pVisualEntity);
    QSet<VisualEntity*>& getAllVisualEntities(){return mAllVisualEntities;};
    void setTool(Tool *pTool){mTool = pTool;};
    Tool* getTool(){return mTool;};
    void deleteTool();
    QuadtreeNode<LERectangle*>& getQuadTree(){return mQuadtree;};
private:
    Tool* mTool;
    QSet<VisualEntity*> mAllVisualEntities; //TODO:Try to involve array or vector to take advantage of cache during iteration
    QSet<VisualEntity*> mSelectedEntities;
    QuadtreeNode<LERectangle*> mQuadtree;
};
#endif // PAINTINGAREA_H
