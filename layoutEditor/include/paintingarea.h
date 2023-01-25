#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <QPoint>
#include "rectangle.h"
#include "quadtreenode.h"


class Tool;
class VisualEntity;
class PaintingArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintingArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void insertVisualEntity(std::shared_ptr<VisualEntity> pVisualEntity);
    void deleteVisualEntity(VisualEntity *pVisualEntity);
    QSet<std::shared_ptr<VisualEntity>>& getAllVisualEntities(){return mAllVisualEntities;};
    void setTool(Tool *pTool){mTool = pTool;};
    Tool* getTool(){return mTool;};
    void deleteTool();
    QuadtreeNode<Rectangle>& getQuadTree(){return mQuadtree;};
private:
    Tool *mTool;
    QSet<std::shared_ptr<VisualEntity>> mAllVisualEntities; //TODO:Try to involve array or vector to take advantage of cache during iteration
    QSet<std::shared_ptr<VisualEntity>> mSelectedEntities;
    QuadtreeNode<Rectangle> mQuadtree;
};
#endif // PAINTINGAREA_H
