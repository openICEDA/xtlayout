#ifndef VISUALENTITY_H
#define VISUALENTITY_H

class QPainter;
class VisualEntity
{
public:
    virtual void draw(QPainter* painter) = 0;
    VisualEntity();
};

#endif // VISUALENTITY_H
