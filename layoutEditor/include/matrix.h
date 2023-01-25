#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <QDebug>
using namespace std;
class Matrix
{
public:
    std::vector<double> mEntries;
    size_t mRowNum;
    size_t mColNum;
    template <typename T>
    Matrix(size_t pRowNum, size_t pColNum, T &&pVec);
    template <typename ... T>
    static Matrix mat3(const T& ... pEntry);
    template <typename ... T>
    static Matrix mat2(const T& ... pEntry);
    template <typename ... T>
    static Matrix vec3(const T& ... pEntry);
    template <typename ... T>
    static Matrix vec2(const T& ... pEntry);
    Matrix operator*(const Matrix &pRhs)
    {
        std::vector<double> temp;
        for(size_t lhsRow = 0; lhsRow < mRowNum; lhsRow++)
        for(size_t rhsCol = 0; rhsCol < pRhs.mColNum; rhsCol++)
        {
            double resEntry = 0;
            for(size_t lhsCol = 0; lhsCol < mColNum; lhsCol++)
            {
                resEntry += mEntries[convert2dTo1d(mColNum, lhsRow, lhsCol)] * pRhs.mEntries[convert2dTo1d(pRhs.mColNum, lhsCol, rhsCol)];
            }
            temp.push_back(resEntry);
        }
        return Matrix(mRowNum, pRhs.mColNum, temp);
    }
    Matrix operator+(const Matrix &pRhs)
    {
        std::vector<double> temp;
        for(size_t lhsRow = 0; lhsRow < mRowNum; lhsRow++)
        for(size_t lhsCol = 0; lhsCol < mColNum; lhsCol++)
        {
            temp.push_back(mEntries[convert2dTo1d(mColNum, lhsRow, lhsCol)] + pRhs.mEntries[convert2dTo1d(mColNum, lhsRow, lhsCol)]);
        }
        return Matrix(mRowNum, mColNum, temp);
    }
    static constexpr inline int convert2dTo1d(size_t pColNum, size_t pRow, size_t pCol)
    {
        return pRow * pColNum + pCol;
    }
    friend ostream& operator << (ostream &pOstream, const Matrix &pMat);
};
template <typename T>
Matrix::Matrix(size_t pRowNum, size_t pColNum, T &&pVec):mRowNum(pRowNum), mColNum(pColNum)
{
    mEntries = std::forward<T>(pVec);
}
template <typename ... T>
Matrix Matrix::mat3(const T& ... pEntry)
{
    static_assert(sizeof...(pEntry) == 9, "invalid number of entries");
    std::vector<double> temp;
    (temp.push_back(pEntry), ...);
    return Matrix(3, 3, std::move(temp));
}
template <typename ... T>
Matrix Matrix::mat2(const T& ... pEntry)
{
    static_assert(sizeof...(pEntry) == 4, "invalid number of entries");
    std::vector<double> temp;
    (temp.push_back(pEntry), ...);
    return Matrix(2, 2, std::move(temp));
}
template <typename ... T>
Matrix Matrix::vec3(const T& ... pEntry)
{
    static_assert(sizeof...(pEntry) == 3, "invalid number of entries");
    std::vector<double> temp;
    (temp.push_back(pEntry), ...);
    return Matrix(3, 1, std::move(temp));
}
template <typename ... T>
Matrix Matrix::vec2(const T& ... pEntry)
{
    static_assert(sizeof...(pEntry) == 2, "invalid number of entries");
    std::vector<double> temp;
    (temp.push_back(pEntry), ...);
    return Matrix(2, 1, std::move(temp));
}

#endif // MATRIX_H
