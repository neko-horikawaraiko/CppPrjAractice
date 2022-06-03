#pragma once

#include "Star.h"

class SolarSystem
{
public:
    SolarSystem();
    ~SolarSystem();
    void onDisplay();
    void onUpdate();
    void onKeyboard(unsigned char key, int x, int y);

private:
    enum { stars_num = 10 };
    Star* stars[stars_num];
    GLdouble view_x, view_y, view_z;		// 摄像机位置
    GLdouble center_x, center_y, center_z;  // 目标点位置
    GLdouble up_x, up_y, up_z;              // 朝上方向向量
};