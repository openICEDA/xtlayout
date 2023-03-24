#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <vector>
#include "quadtreenode.h"
#include "xtdb.h"
#include "lrectangle.h"
#include "tool.h"
class MainWindow;
class VisualEntity;
class PaintingArea : public QWidget
{
    Q_OBJECT
private:
    QSet<VisualEntity*> mAllVisualEntities;
    QuadtreeNode<LRectangle*> mQuadtree;
    MainWindow* mMainWindow;
public:
    xtdb::XtBlock* mBlock; //TODO: fileio
    explicit PaintingArea(QWidget* parent = nullptr);
//    PaintingArea(MainWindow* pMainWindow);
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void insertVisualEntity(VisualEntity* pVisualEntity);
    void removeVisualEntity(VisualEntity* pVisualEntity);
    QSet<VisualEntity*>& getAllVisualEntities(){return mAllVisualEntities;};
    QuadtreeNode<LRectangle*>& getQuadTree(){return mQuadtree;};
    void searchRects(const QRect& pZone, QSet<LRectangle*>& pFoundObjs);
};
#endif // PAINTINGAREA_H
