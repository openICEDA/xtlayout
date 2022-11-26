#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <QPoint>
#include "rectangle.h"
#include "quadtreenode.h"
#include <QSharedPointer>


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
    void insertVisualEntity(const QSharedPointer<VisualEntity> &pVisualEntity);
    void deleteVisualEntity(VisualEntity *pVisualEntity);
    void setTool(Tool *pTool){mTool = pTool;};
    Tool* getTool(){return mTool;};
    void deleteTool();
    QuadtreeNode<Rectangle>& getQuadTree(){return mQuadtree;};
private:
    Tool *mTool;
    QSet<QSharedPointer<VisualEntity>> mAllVisualEntities;
    QSet<QSharedPointer<VisualEntity>> mSelectedEntities;
    QuadtreeNode<Rectangle> mQuadtree;
};
#endif // PAINTINGAREA_H
