#ifndef LBLOCK_H
#define LBLOCK_H
#include "xtdb.h"
#include <QRect>
#include <QSet>
class LShape;
class VisualEntity;
class PaintingArea;
class LBlock
{
private:
    class ShapeQuery : public xtdb::XtShapeQuery
    {
    private:
        friend class LBlock;
        QSet<LShape*> mFoundObjs;
    public:
        ~ShapeQuery(){};
        ShapeQuery(xtdb::XtBlock* pBlock);
        void onShapeFound(xtdb::XtShape* pShape) override;
    };
    PaintingArea* mPA;
    QRect mViewport;
    xtdb::XtBlock* mBlock;
    QSet<LShape*> mSelectedShapes;
    QSet<VisualEntity*> mVisualEntitiesInViewport;
    QSet<VisualEntity*>::iterator mCurVisualEntityItr;
    QSet<LShape*>::iterator mCurSelectedShapeItr;
    ShapeQuery* mShapeQuery;
    QString mCurFile;
public:
    LBlock(PaintingArea* pPA, unsigned int pViewportWidth, unsigned int pViewportHeight);
    ~LBlock();
    PaintingArea* getPaintingArea(){return mPA;};
    xtdb::XtBlock* getDBBlock(){return mBlock;};

    QRect getViewport(){return mViewport;};
    void setViewport(const QRect& pRect){mViewport = pRect;};

    void insertVisualEntityInViewport(VisualEntity* pVisualEntity);
    void removeVisualEntityInViewport(VisualEntity* pVisualEntity);
    void initVisualEntityInViewPortPtr();
    VisualEntity* nextVisualEntityInViewportPtr();
    void clearVisualEntitiesInViewport();

    void selectShapesInZone(const QRect& pZone);
    void deselectShapesInZone(const QRect& pZone);
    void initSelectedShapePtr();
    bool nextSelectedShape();
    void deleteSelectedShapes();
    void removeSelectedShape(LShape* pShape);

    void searchShapes(const QRect& pZone, QSet<LShape*>& pFoundShapes, bool ONLY_FULLY_CONTAINED = false);
    bool open(const QString& pFileName);
    bool saveAs();
    bool write(const QString &fileName);
    QString getCurrentFile(){return mCurFile;};
};

#endif // LBLOCK_H
