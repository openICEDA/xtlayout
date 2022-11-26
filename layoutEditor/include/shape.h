#ifndef SHAPE_H
#define SHAPE_H
#include "visualentity.h"
#include "globalsetting.h"
class QPainter;
class Shape: public VisualEntity
{
public:
    Shape();
    void select();
    void move();
    void stretch();
protected:
    GlobalSetting::layer_type mLayer;
};

#endif // SHAPE_H
