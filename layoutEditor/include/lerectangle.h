#ifndef LERECTANGLE_H
#define LERECTANGLE_H
#include "xtdb.h"
#include "visualentity.h"
#include <QRect>
class LERectangle: public VisualEntity
{
private:
    xtdb::XtRectangle* mRect;
    bool mSelected;
public:
    LERectangle();
    ~LERectangle();
    LERectangle(xtdb::XtRectangle* pRect);
    void draw(QPainter* pPainter) override;
    void setFirstPoint(const QPoint& pPoint);
    void setSecondPoint(const QPoint& pPoint);
    void setSelected(bool pSelected);
    QRect getZone();
};

#endif // LERECTANGLE_H
