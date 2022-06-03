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
    GLdouble view_x, view_y, view_z;		// �����λ��
    GLdouble center_x, center_y, center_z;  // Ŀ���λ��
    GLdouble up_x, up_y, up_z;              // ���Ϸ�������
};