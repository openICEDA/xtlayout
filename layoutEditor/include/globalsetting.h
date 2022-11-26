#ifndef GLOBALSETTING_H
#define GLOBALSETTING_H
#include <QSize>
#include <QHash>
#include <QColor>
//TODO: implement reading ini files and singleton
class GlobalSetting
{
public:
    GlobalSetting();
    static QSize canvasSize;
    static int gridWidth;
    enum layer_type
    {
        METAL1,
        METAL2,
        METAL3,
        POLY
    };
    static QHash<layer_type, QColor> textureOfLayer;
};

#endif // GLOBALSETTING_H
