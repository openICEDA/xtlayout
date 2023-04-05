#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H

#include <QWidget>
#include <QSet>
#include <vector>
#include "lrectangle.h"
#include "tool.h"
class MainWindow;
class VisualEntity;
class PaintingArea : public QWidget
{
    Q_OBJECT
private:
    class ShapeQuery : public xtdb::XtShapeQuery
    {
    private:
        friend class PaintingArea;
        QSet<LShape*> mFoundObjs;
    public:
        ~ShapeQuery(){};
        ShapeQuery(xtdb::XtBlock* pBlock);
        void onShapeFound(xtdb::XtShape* pShape) override;
    };
    QSet<VisualEntity*> mAllVisualEntities;
    MainWindow* mMainWindow;
    xtdb::XtBlock* mBlock; //TODO: fileio
    ShapeQuery* mShapeQuery;
    QString mCurFile;
    QRect mViewport;
public:
    ~PaintingArea();
    explicit PaintingArea(QWidget* parent = nullptr);
    QRect getViewport(){return mViewport;};
    void setViewport(const QRect& pRect){mViewport = pRect;};
    xtdb::XtBlock* getBlock();
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void insertVisualEntity(VisualEntity* pVisualEntity);
    void removeVisualEntity(VisualEntity* pVisualEntity);
    QSet<VisualEntity*>& getAllVisualEntities(){return mAllVisualEntities;};
    void searchShapes(const QRect& pZone, QSet<LShape*>& pFoundObjs, bool ONLY_FULLY_CONTAINED = false);
    bool saveAs();
    bool saveFile(const QString &fileName);
    bool loadFile(const QString &pFileName);
    QString getCurrentFile(){return mCurFile;};
};
#endif // PAINTINGAREA_H
