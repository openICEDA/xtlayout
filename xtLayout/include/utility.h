#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include "matrix.h"
#include "lrectangle.h"
#include <QPoint>
class MatUtil
{
public:
    enum coordinate_system{
        VIEWPORT,
        WORLD,
    };
public:
    static QPoint translate(QPoint pTranslateVec, QPoint pPnt);
};

#endif // UTILITY_H
