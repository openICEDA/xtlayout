#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include "globalsetting.h"
#include <QRect>
class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(int pX1, int pY1, int pW, int pH, GlobalSetting::layer_type layer = GlobalSetting::METAL1);
    Rectangle(QPoint pFirstPoint, QPoint pSecondPoint, GlobalSetting::layer_type layer = GlobalSetting::METAL1);
    void setSecondPoint(QPoint pPoint){mRect.setBottomRight(pPoint);};
    void draw(QPainter* pPainter) override;
    QRect getZone(){return mRect;};
private:
    GlobalSetting::layer_type mLayer;
    QRect mRect;
};

#endif // RECTANGLE_H
