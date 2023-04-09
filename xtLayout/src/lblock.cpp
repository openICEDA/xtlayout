#include "lblock.h"
#include "xtdb.h"
#include "lrectangle.h"
#include "xtliterals.h"
#include <QSaveFile>
#include <QMessageBox>
#include <QFileInfo>

LBlock::LBlock(PaintingArea* pPA, unsigned int pViewportWidth, unsigned int pViewportHeight):mPA(pPA), mViewport(5000, 5000, pViewportWidth, pViewportHeight), mBlock(xtdb::XtBlock::create())
{
    mShapeQuery = new ShapeQuery(mBlock);

}

LBlock::~LBlock()
{
    xtdb::XtBlock::destroy(mBlock);
    delete mShapeQuery;
}

bool LBlock::write(const QString& pFileName)
{
    //TODO: consider possible failure of writting process
    mBlock->write(pFileName.toStdString().c_str());
    mCurFile = QFileInfo(pFileName).canonicalFilePath();
    return true;
}

bool LBlock::open(const QString& pFileName)
{
    //TODO: consider possible failure of loading process
    mBlock->load(pFileName.toStdString().c_str());
    xtdb::XtSet<xtdb::XtShape*> allShapes = mBlock->getAllShapes();
    for (xtdb::XtIterator<xtdb::XtShape*> shapeIt = allShapes.begin(); shapeIt != allShapes.end(); shapeIt++)
    {
        //TODO: get class ID and cast to the corresponding class
        xtdb::XtRectangle* xtrect = static_cast<xtdb::XtRectangle*>(*shapeIt);
        LRectangle* lrect = new LRectangle(xtrect);
        insertVisualEntity(lrect);
    }
    mCurFile = QFileInfo(pFileName).canonicalFilePath();
    return true;
}

void LBlock::initVisualEntityPtr()
{
    mCurVisualEntityItr = mAllVisualEntities.begin();
}

void LBlock::insertVisualEntity(VisualEntity* pVisualEntity)
{
    mAllVisualEntities.insert(pVisualEntity);
}

void LBlock::removeVisualEntity(VisualEntity* pVisualEntity)
{
    QSet<VisualEntity*>::const_iterator it = mAllVisualEntities.find(pVisualEntity);
    if (mAllVisualEntities.cend() != it)
    {
        mAllVisualEntities.erase(it);
    }
}

VisualEntity* LBlock::nextVisualEntityPtr()
{
    if (mAllVisualEntities.end() == mCurVisualEntityItr)
    {
        return nullptr;
    }
    VisualEntity* visualEntity = *mCurVisualEntityItr;
    mCurVisualEntityItr++;
    return visualEntity;
}

void LBlock::initSelectedShapePtr()
{
    mCurSelectedShapeItr = mSelectedShapes.begin();
}

void LBlock::ShapeQuery::onShapeFound(xtdb::XtShape* pShape)
{
    //TODO: execute onshapefound inside quadtree, instead of generating result at first, then iterate through it.
    LShape* shape = static_cast<LShape*>(pShape->getExtendedObj(XTLAYOUT));
    mFoundObjs.insert(shape);
}

void LBlock::searchShapes(const QRect& pZone, QSet<LShape*>& pFoundShapes, bool ONLY_FULLY_CONTAINED)
{
    pFoundShapes.clear();
    xtdb::XtRect region(pZone.left(), pZone.top(), pZone.right(), pZone.bottom());
    mShapeQuery->query(region, ONLY_FULLY_CONTAINED);
    pFoundShapes = std::move(mShapeQuery->mFoundObjs);
}

void LBlock::selectShapesInZone(const QRect& pZone)
{
    QSet<LShape*> foundShapes;
    searchShapes(pZone, foundShapes);
    std::for_each(foundShapes.begin(), foundShapes.end(), [](LShape* shape){shape->select();});
    mSelectedShapes = std::move(foundShapes);
}

void LBlock::deleteSelectedShapes()
{
    std::for_each(mSelectedShapes.begin(), mSelectedShapes.end(), [this](LShape* shape){
        mAllVisualEntities.remove(shape);
        delete shape;});
    mSelectedShapes.clear();
}

LBlock::ShapeQuery::ShapeQuery(xtdb::XtBlock* pBlock):xtdb::XtShapeQuery(pBlock)
{

}

void LBlock::clearAllVisualEntities()
{
    mAllVisualEntities.clear();
}
