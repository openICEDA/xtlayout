#ifndef GRID_H
#define GRID_H

#include "visualentity.h"
class NavigationTool;
class QPainter;
class Grid : public VisualEntity
{
public:
    Grid();
    void draw(QPainter* pPainter) override;
};

#endif // GRID_H
