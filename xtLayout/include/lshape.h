#ifndef LSHAPE_H
#define LSHAPE_H

#include "visualentity.h"

class LShape : public VisualEntity
{
private:
    bool mIsSelected;
protected:
    LShape();
public:
    virtual ~LShape(){};
    void select();
    void deselect();
    bool isSelected();
};

inline void LShape::select()
{
    mIsSelected = true;
}

inline void LShape::deselect()
{
    mIsSelected = false;
}

inline bool LShape::isSelected()
{
    return mIsSelected;
}

#endif // LSHAPE_H
