#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <visualentity.h>
#include <QRect>

class NavigationTool;
class SelectionBox : public VisualEntity
{
private:
    QRect mRect;
public:
    SelectionBox(NavigationTool* pNavTool);
    QRect getZone(){return mRect;};
    void setFirstPoint(const QPoint &pPoint){mRect.setTopLeft(pPoint);};
    void setSecondPoint(const QPoint &pPoint){mRect.setBottomRight(pPoint);};
    void reset(){mRect = QRect(0,0,0,0);};
    void draw(QPainter* pPainter);
};

#endif // SELECTIONBOX_H
