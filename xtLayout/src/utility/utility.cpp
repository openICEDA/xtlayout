#include <iostream>
#include "matrix.h"
constexpr inline size_t convert2dTo1d(size_t pColNum, size_t pRow, size_t pCol)
{
    return pRow * pColNum + pCol;
}
std::ostream& operator << (std::ostream &pOstream, const Matrix &pMat)
{
    for (size_t row = 0; row < pMat.mRowNum; row++)
    {
        for (size_t col = 0; col < pMat.mColNum; col++)
        {
            pOstream << pMat.mEntries[Matrix::convert2dTo1d(pMat.mColNum, row, col)];
        }
        pOstream << endl;
    }
    return pOstream;
}
