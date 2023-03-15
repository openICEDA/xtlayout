#ifndef VISUALENTITY_H
#define VISUALENTITY_H

class QPainter;
class NavigationTool;
class VisualEntity
{
protected:
    NavigationTool* mNavTool;
public:
    virtual void draw(QPainter* pPainter) = 0;
    VisualEntity(NavigationTool* pNavTool);
};

#endif // VISUALENTITY_H
