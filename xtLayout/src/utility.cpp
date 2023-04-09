#include "utility.h"
#include <iostream>
#include "matrix.h"
#include "mainwindow.h"
QPoint MatUtil::translate(QPoint pTranslateVec, QPoint pPnt)
{
    return pPnt + pTranslateVec;
}
