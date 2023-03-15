#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <QDebug>
class Matrix
{
private:
    friend class AccessDummy;
    std::vector<double> mEntries;
    size_t mRowNum;
    size_t mColNum;
public:
    static Matrix translateMat(const std::vector<double>& pVec)
    {
        return Matrix::mat3(1, 0, pVec[0],
                            0, 1, pVec[1],
                            0, 0, 1);
    }
    static std::vector<Matrix> transformPnts(const Matrix& pMat, const std::vector<Matrix>& pOrigPnts)
    {
        std::vector<Matrix> res;
        res.reserve(pMat.mEntries.capacity());
        for (std::vector<Matrix>::const_iterator it; it != pOrigPnts.cend(); it++)
        {
            res.push_back(pMat * (*it));
        }
        return res;
    }
    template <typename T>
    Matrix(size_t pRowNum, size_t pColNum, T&& pVec);
    template <typename ... T>
    static Matrix mat3(const T& ... pEntry);
    template <typename ... T>
    static Matrix mat2(const T& ... pEntry);
    template <typename ... T>
    static Matrix vec3(const T& ... pEntry);
    template <typename ... T>
    static Matrix vec2(const T& ... pEntry);
    template <typename ... T>
    static std::vector<Matrix> transformPnts(const Matrix& pMat, const std::vector<Matrix>& pOrigPnts);
    Matrix operator*(const Matrix& pRhs) const
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
    Matrix operator+(const Matrix& pRhs)
    {
        std::vector<double> temp;
        for(size_t lhsRow = 0; lhsRow < mRowNum; lhsRow++)
        for(size_t lhsCol = 0; lhsCol < mColNum; lhsCol++)
        {
            temp.push_back(mEntries[convert2dTo1d(mColNum, lhsRow, lhsCol)] + pRhs.mEntries[convert2dTo1d(mColNum, lhsRow, lhsCol)]);
        }
        return Matrix(mRowNum, mColNum, temp);
    }
    class AccessDummy
    {
    private:
        size_t mRow;
        Matrix* mMat;
    public:
        AccessDummy(size_t pRow, Matrix* pMat):mRow(pRow), mMat(pMat)
        {
        }
        double operator[](size_t pCol)
        {
            return mMat->mEntries[convert2dTo1d(mMat->mColNum, mRow, pCol)];
        }
    };
    AccessDummy operator[](size_t pRow)
    {
        return AccessDummy(pRow, this);
    }
    static constexpr inline int convert2dTo1d(size_t pColNum, size_t pRow, size_t pCol)
    {
        return pRow * pColNum + pCol;
    }
    friend std::ostream& operator << (std::ostream& pOstream, const Matrix& pMat);
};
template <typename T>
Matrix::Matrix(size_t pRowNum, size_t pColNum, T&& pVec):mRowNum(pRowNum), mColNum(pColNum)
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
