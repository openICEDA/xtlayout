#include "globalsetting.h"
QSize GlobalSetting::canvasSize{800, 800};
int GlobalSetting::gridWidth = 50;
QHash<GlobalSetting::layer_type, QColor> GlobalSetting::textureOfLayer = {
    {GlobalSetting::METAL1, QColor{55,216,1,255}},
    {GlobalSetting::METAL2, QColor{104,216,204,255}},
    {GlobalSetting::METAL3, QColor{55,216,1,255}},
    {GlobalSetting::POLY, QColor{0,100,22,255}},
};
GlobalSetting::GlobalSetting()
{

}
