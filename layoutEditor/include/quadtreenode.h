#ifndef QUADTREENODE_H
#define QUADTREENODE_H
#include <QRect>
#include <QList>
#include "visualentity.h"
#include <QSharedPointer>
#include <memory>
#include <QDebug>

template <typename T>
class QuadtreeNode
{
public:
    QuadtreeNode(int pLevel, const QRect &pZone);
    ~QuadtreeNode(){};
    bool contains(const QRect &pZone) const;
    bool intersects(const QRect &pZone) const;
    void insert(QSharedPointer<T> pObj);
    void search(const QRect &pZone, QList<T*> &foundObjs);
    void getAllObjsOfSubtree(QList<T*> &pResList);
    void resize(const QRect &pZone);
    QRect mZone;
    QList<QSharedPointer<T>> mObjs;
    int mLevel;
    static const int maxLevel;
    std::unique_ptr<QuadtreeNode<T>> mChildren[4];
    QRect mChildrenZones[4];
};

template <typename T>
const int QuadtreeNode<T>::maxLevel = 3;

template <typename T>
QuadtreeNode<T>::QuadtreeNode(int pLevel, const QRect &pZone):
    mLevel(pLevel), mZone(pZone),
    mChildrenZones{
        {mZone.left() + mZone.width()/2, mZone.top(), mZone.width(), mZone.height()},
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
void QuadtreeNode<T>::insert(QSharedPointer<T> pObj)
{
    if(!contains(pObj->getZone()))
    {
        return;
    }
    if(mLevel == maxLevel)
    {
        mObjs.push_back(std::move(pObj));
        return;
    }
    for(int i = 0; i < 4; i++)
    {
        if(mChildrenZones[i].contains(pObj->getZone()))
        {
            if(nullptr == mChildren[i])
            {
                mChildren[i] = std::make_unique<QuadtreeNode<T>>(mLevel + 1, mChildrenZones[i]);
            }
            mChildren[i]->insert(pObj);
            return;
        }
    }
    mObjs.push_back(std::move(pObj));
    return;
}

template <typename T>
void QuadtreeNode<T>::search(const QRect &pZone, QList<T*> &foundObjs)
{
    if(pZone.intersects(mZone))
    {
        for(typename QList<T*>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
        {
            if((*it)->getZone().intersects(pZone))
            {
                foundObjs.push_back(*it);
            }
        }
        for(int i = 0; i < 4; i++)
        {
            if(pZone.contains(mChildrenZones[i]))
            {
                mChildren[i]->getAllObjsOfSubstree(foundObjs);
            }
            else if(pZone.intersects(mChildrenZones[i]))
            {
                mChildren[i]->search(pZone);
            }
        }
    }
}

template <typename T>
void QuadtreeNode<T>::getAllObjsOfSubtree(QList<T*>& pResList)
{
    for(typename QList<QSharedPointer<T>>::iterator it = mObjs.begin(); it != mObjs.end(); it++)
    {
        pResList.push_back((*it).get());
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
