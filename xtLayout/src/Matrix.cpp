#include "matrix.h"
#include <iostream>
std::ostream& operator<<(std::ostream &pOstream, const Matrix &pMat)
{
    for (size_t row = 0; row < pMat.mRowNum; row++)
    {
        for (size_t col = 0; col < pMat.mColNum; col++)
        {
            pOstream << pMat.mEntries[Matrix::convert2dTo1d(pMat.mColNum, row, col)];
        }
        pOstream << std::endl;
    }
    return pOstream;
}
