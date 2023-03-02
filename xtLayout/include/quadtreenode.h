#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include <QRect>
#include <QSet>
#include "visualentity.h"
#include <memory>
#include <QDebug>
//TODO:是不是可以判断T是不是指针，决定->还是.s
template <typename T>
class QuadtreeNode
{
public:
    QRect mZone;
    QSet<T> mObjs;
    int mLevel;
    static const int maxLevel;
    std::unique_ptr<QuadtreeNode<T>> mChildren[4];
    QRect mChildrenZones[4];
public:
    QuadtreeNode(const QRect& pZone, int pLevel = 0);
    ~QuadtreeNode(){};
    bool contains(const QRect& pZone) const;
    bool intersects(const QRect& pZone) const;
    void insert(const T& pObj);
    void search(const QRect& pZone, QSet<T>& pFoundObjs); //TODO:is QSet<T&> better?
    void getAllObjsOfSubtree(QSet<T>& pResList);
    void deleteAllObjsOfSubtree();
    void deleteObj(const T& pObj);
    void resize(const QRect& pZone);
    void deleteObjsIn(const QRect& pZone);
};

template <typename T>
const int QuadtreeNode<T>::maxLevel = 1;

template <typename T>
QuadtreeNode<T>::QuadtreeNode(const QRect& pZone, int pLevel):
    mLevel(pLevel), mZone(pZone),
    mChildrenZones{
        {mZone.left() + mZone.width()/2, mZone.top(), mZone.width()/2, mZone.height()/2},
        {mZone.left(), mZone.top(), mZone.width()/2, mZone.height()/2},
        {mZone.left(), mZone.top() + mZone.height()/2, mZone.width()/2, mZone.height()/2},
        {mZone.left() + mZone.width()/2, mZone.top() + mZone.height()/2, mZone.width()/2, mZone.height()/2}
    }
{
}

template <typename T>
void QuadtreeNode<T>::resize(const QRect& pZone)
{

}

template <typename T>
void QuadtreeNode<T>::deleteObjsIn(const QRect& pZone)
{
    for (typename QSet<T>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
    {
        if((*it)->getZone().intersects(pZone))
        {
            mObjs.erase(it);
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (nullptr != mChildren[i])
        {
            if (pZone.contains(mChildrenZones[i]))
            {
                mChildren[i]->deleteAllObjsOfSubtree();
            }
            else if (pZone.intersects(mChildrenZones[i]))
            {
                mChildren[i]->deleteObjsIn(pZone);
            }
        }
    }
}

template <typename T>
void QuadtreeNode<T>::deleteObj(const T& pObj)
{
    typename QSet<T>::const_iterator it = mObjs.find(pObj);
    if (mObjs.end() != it)
    {
        mObjs.erase(it);
    }
}
//template <typename T>
//QuadtreeNode<T>::~QuadtreeNode()
//{
//    qDebug() << "quadtreenode killed!";
//}

template <typename T>
bool QuadtreeNode<T>::contains(const QRect& pZone) const
{
    if(mZone.contains(pZone))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool QuadtreeNode<T>::intersects(const QRect& pZone) const
{
    if(mZone.intersects(pZone))
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
void QuadtreeNode<T>::insert(const T& pObj)
{
    if(!contains(pObj->getZone()))
    {
        return;
    }
    if(mLevel == maxLevel)
    {
        mObjs.insert(pObj);
        pObj->setOwnerNode(this);
        return;
    }
    for(int i = 0; i < 4; i++)
    {
        if(mChildrenZones[i].contains(pObj->getZone()))
        {
            if(nullptr == mChildren[i])
            {
                mChildren[i] = std::make_unique<QuadtreeNode<T>>(mChildrenZones[i], mLevel + 1);
            }
            mChildren[i]->insert(pObj);
            return;
        }
    }
    mObjs.insert(pObj);
    pObj->setOwnerNode(this);
    return;
}

template <typename T>
void QuadtreeNode<T>::search(const QRect& pZone, QSet<T>& pFoundObjs)
{
    for(typename QSet<T>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
    {
        if((*it)->getZone().intersects(pZone))
        {
            pFoundObjs.insert(*it);
        }
    }
    for(int i = 0; i < 4; i++)
    {
        if (nullptr != mChildren[i])
        {
            if(pZone.contains(mChildrenZones[i]))
            {
                mChildren[i]->getAllObjsOfSubtree(pFoundObjs);
            }
            else if(pZone.intersects(mChildrenZones[i]))
            {
                mChildren[i]->search(pZone, pFoundObjs);
            }
        }
    }
}

template <typename T>
void QuadtreeNode<T>::getAllObjsOfSubtree(QSet<T>& pResList)
{
    for(typename QSet<T>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
    {
        pResList.insert(*it);
    }
    for(int i = 0; i < 4; i++)
    {
        if(nullptr != mChildren[i])
        {
            mChildren[i]->getAllObjsOfSubtree(pResList);
        }
    }
}

template <typename T>
void QuadtreeNode<T>::deleteAllObjsOfSubtree()
{
    mObjs.clear();
    for(int i = 0; i < 4; i++)
    {
        if(nullptr != mChildren[i])
        {
            mChildren[i]->deleteAllObjsOfSubtree();
        }
    }
}
#endif // QUADTREENODE_H
