#include "SolarSystem.h"
#include <stdlib.h>

#define SET_VALUE_3(name, value0, value1, value2) \
                   ((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)

const int TIMEPAST = 1;
const int CAMMOVESTEP = 200;
const int INIT_VIEW = 700;

// 自身半径
const float SUN_RADIUS = 69.63f;
const float MER_RADIUS =  6.05f * 2;
const float VEN_RADIUS =  6.38f * 2;
const float EAR_RADIUS = 19.13f * 2;
const float MOO_RADIUS =  1.74f * 5;
const float MAR_RADIUS =  3.39f * 2;
const float JUP_RADIUS = 71.49f * 2;
const float SAT_RADIUS = 60.29f * 2;
const float URA_RADIUS = 25.56f * 2;
const float NEP_RADIUS = 24.77f * 2;

// 轨道半径
const float MER_DIS =   57.91f * 2;
const float VEN_DIS =  108.20f * 2;
const float EAR_DIS =  149.60f * 2;
const float MOO_DIS =    0.38f * 150;
const float MAR_DIS =  227.94f * 2;
const float JUP_DIS =  778.33f * 2;
const float SAT_DIS = 1429.40f * 2;
const float URA_DIS = 2870.99f * 2;
const float NEP_DIS = 4504.00f * 2;

// 绕行天数
const float MER_SPEED =    88.0 * 10;
const float VEN_SPEED =   224.7 * 10;
const float EAR_SPEED =   365.3 * 10;
const float MOO_SPEED =    29.5 * 10;
const float MAR_SPEED =   687.0 * 10;
const float JUP_SPEED =  4332.6 * 10;
const float SAT_SPEED = 10759.2 * 10;
const float URA_SPEED = 30688.5 * 10;
const float NEP_SPEED = 60195.0 * 10;

const int SELFROTATE = 3;

enum Stars
{
    Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune
};

SolarSystem::SolarSystem()
    :view_x(0), view_y(-INIT_VIEW), view_z(INIT_VIEW), center_x(0), center_y(0), center_z(0),
    up_x(0), up_y(0), up_z(1)
{
    // 太阳
    GLfloat rgbColor[3] = { 1, 0, 0 };
    stars[Sun] = new LightPlanet(SUN_RADIUS, 0, 0, SELFROTATE, 0, rgbColor);
    // 水星
    SET_VALUE_3(rgbColor, .2, .2, .5);
    stars[Mercury] = new Planet(MER_RADIUS, MER_DIS, 360 / MER_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 金星
    SET_VALUE_3(rgbColor, 1, .7, 0);
    stars[Venus] = new Planet(VEN_RADIUS, VEN_DIS, 360 / VEN_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 地球
    SET_VALUE_3(rgbColor, 0, 1, 0);
    stars[Earth] = new Planet(EAR_RADIUS, EAR_DIS, 360 / EAR_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 月亮
    SET_VALUE_3(rgbColor, 1, 1, 0);
    stars[Moon] = new Planet(MOO_RADIUS, MOO_DIS, 360 / MOO_SPEED, SELFROTATE, stars[Earth], rgbColor);
    // 火星
    SET_VALUE_3(rgbColor, 1, .5, .5);
    stars[Mars] = new Planet(MAR_RADIUS, MAR_DIS, 360 / MAR_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 木星
    SET_VALUE_3(rgbColor, 1, 1, .5);
    stars[Jupiter] = new Planet(JUP_RADIUS, JUP_DIS, 360 / JUP_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 土星
    SET_VALUE_3(rgbColor, .5, 1, .5);
    stars[Saturn] = new Planet(SAT_RADIUS, SAT_DIS, 360 / SAT_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 天王星
    SET_VALUE_3(rgbColor, .4, .4, .4);
    stars[Uranus] = new Planet(URA_RADIUS, URA_DIS, 360 / URA_SPEED, SELFROTATE, stars[Sun], rgbColor);
    // 海王星
    SET_VALUE_3(rgbColor, .5, .5, 1);
    stars[Neptune] = new Planet(NEP_RADIUS, NEP_DIS, 360 / NEP_SPEED, SELFROTATE, stars[Sun], rgbColor);
}

SolarSystem::~SolarSystem()
{
    for (int i = 0; i < stars_num; ++i)
        delete stars[i];
}

void SolarSystem::onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除viewport缓冲区
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);				// 设置清除后的颜色

    glMatrixMode(GL_PROJECTION);						// 进入设置投影矩阵部分
    glLoadIdentity();									// 设一个单位阵，将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
    gluPerspective(75.0f, 1.0f, 1.0f, 40000000);		// 视景体，参数分别为视角大小、宽高比、近端投影面、远端距离

    glMatrixMode(GL_MODELVIEW);							// 进入设置对模型的视图变换部分
    glLoadIdentity();
    gluLookAt(view_x, view_y, view_z, center_x, center_y, center_z,		// 视角
        up_x, up_y, up_z); 

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);							// 深度测试，自动隐藏被遮挡部分

    for (int i = 0; i < stars_num; ++i)
        stars[i]->draw();

    glutSwapBuffers();									// 双缓冲区的交换
}

void SolarSystem::onUpdate()
{
    for (int i = 0; i < stars_num; ++i)
        stars[i]->update(TIMEPAST);
    this->onDisplay();
}

void SolarSystem::onKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        view_y += CAMMOVESTEP;
        break;
    case 's':
        view_y -= CAMMOVESTEP;
        break;
    case 'a':
        view_z += CAMMOVESTEP;
        break;
    case 'd':
        view_z -= CAMMOVESTEP;
        break;
    case 'z':
        view_x += CAMMOVESTEP;
        break;
    case 'x':
        view_x -= CAMMOVESTEP;
        break;
    case 'r':
        view_x = 0;
        view_y = -INIT_VIEW;
        view_z = INIT_VIEW;
        center_x = center_y = center_z = 0;
        up_x = up_y = 0;
        up_z = 1;
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}
