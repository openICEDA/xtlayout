#include "navigationtool.h"
#include <QKeyEvent>

navigationTool::navigationTool():Tool(NAVIGATION_TOOL)
{

}

void navigationTool::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
        case Qt::Key_Direction_R:

            break;
        default:
            break;
    }

}
