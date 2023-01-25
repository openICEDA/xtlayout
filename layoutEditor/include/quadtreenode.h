#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include <QRect>
#include <QSet>
#include "visualentity.h"
#include <memory>
#include <QDebug>

template <typename T>
class QuadtreeNode
{
public:
    QuadtreeNode(const QRect &pZone, int pLevel = 0);
    ~QuadtreeNode(){};
    bool contains(const QRect &pZone) const;
    bool intersects(const QRect &pZone) const;
    void insert(std::shared_ptr<T> pObj);
    void search(const QRect &pZone, QSet<std::shared_ptr<T>> &foundObjs);
    void getAllObjsOfSubtree(QSet<std::shared_ptr<T>> &pResList);
    void resize(const QRect &pZone);
    QRect mZone;
    QSet<std::shared_ptr<T>> mObjs;
    int mLevel;
    static const int maxLevel;
    std::unique_ptr<QuadtreeNode<T>> mChildren[4];
    QRect mChildrenZones[4];
};

template <typename T>
const int QuadtreeNode<T>::maxLevel = 1;

template <typename T>
QuadtreeNode<T>::QuadtreeNode(const QRect &pZone, int pLevel):
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
void QuadtreeNode<T>::resize(const QRect &pZone)
{

}

//template <typename T>
//QuadtreeNode<T>::~QuadtreeNode()
//{
//    qDebug() << "quadtreenode killed!";
//}

template <typename T>
bool QuadtreeNode<T>::contains(const QRect &pZone) const
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
bool QuadtreeNode<T>::intersects(const QRect &pZone) const
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
void QuadtreeNode<T>::insert(std::shared_ptr<T> pObj)
{
    if(!contains(pObj->getZone()))
    {
        return;
    }
    if(mLevel == maxLevel)
    {
        mObjs.insert(std::move(pObj));
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
    mObjs.insert(std::move(pObj));
    return;
}

template <typename T>
void QuadtreeNode<T>::search(const QRect &pZone, QSet<std::shared_ptr<T>> &foundObjs)
{
    for(typename QSet<std::shared_ptr<T>>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
    {
        if((*it)->getZone().intersects(pZone))
        {
            foundObjs.insert(*it);
        }
    }
//    if(mLevel == maxLevel)
//    {
//        return;
//    }
    for(int i = 0; i < 4; i++)
    {
        if (nullptr != mChildren[i])
        {
            if(pZone.contains(mChildrenZones[i]))
            {
                mChildren[i]->getAllObjsOfSubtree(foundObjs);
            }
            else if(pZone.intersects(mChildrenZones[i]))
            {
                mChildren[i]->search(pZone, foundObjs);
            }
        }
    }
}

template <typename T>
void QuadtreeNode<T>::getAllObjsOfSubtree(QSet<std::shared_ptr<T>> &pResList)
{
    for(typename QSet<std::shared_ptr<T>>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
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

#endif // QUADTREENODE_H
