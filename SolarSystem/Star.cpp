#include "Star.h"
#include <cmath>

const double PI = 3.14159265359;

Star::Star(GLfloat selfRadius, GLfloat orbitRadius, GLfloat revolutionSpeed, GLfloat rotationSpeed, Star* parentStar, GLfloat rgbColor[3])
    :radius(selfRadius), orbit_radius(orbitRadius), revo_speed(revolutionSpeed), rota_speed(rotationSpeed), 
    parent_star(parentStar), revo_angle(0), rota_angle(0)
{
    color[0] = rgbColor[0];
    color[1] = rgbColor[1];
    color[2] = rgbColor[2];
    color[3] = 1.0f;
}

void Star::drawStar()
{
    glEnable(GL_LINE_SMOOTH);	// 启用线条抗锯齿
    glEnable(GL_BLEND);			// 启用颜色混合，为带有alpha通道的颜色进行混合，此处配合上一句实现线条抗锯齿

    glPushMatrix();

    // 父星体位置变换
    if (parent_star != nullptr && parent_star->orbit_radius > 0)
    {
        glRotatef(parent_star->revo_angle, 0, 0, 1);
        glTranslatef(parent_star->orbit_radius, 0, 0);
    }

    // 多边形模拟圆形轨道
    int n = 1440;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; ++i)
        glVertex2f(orbit_radius * cos(2 * PI * i / n), orbit_radius * sin(2 * PI * i / n));
    glEnd();

    // 星体自己位置变换
    glRotatef(revo_angle, 0, 0, 1);
    glTranslatef(orbit_radius, 0, 0);
    glRotatef(rota_angle, 0, 0, 1);

    // 星体颜色
    glColor3f(color[0], color[1], color[2]);
    glutSolidSphere(radius, 40, 32);		// 后两参数分别为经线分成的片数、纬线分成的层数

    glPopMatrix();
}

void Star::update(long duration)
{
    revo_angle += duration * revo_speed;
    rota_angle += duration * rota_speed;
}


Planet::Planet(GLfloat selfRadius, GLfloat orbitRadius, GLfloat revolutionSpeed, GLfloat rotationSpeed, Star* parentStar, GLfloat rgbColor[3])
    :Star(selfRadius, orbitRadius, revolutionSpeed, rotationSpeed, parentStar, rgbColor)
{
}

void Planet::drawPlanet()
{
    GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };						// 环境光照在物体上反射出的颜色
    GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };						// 漫反光照在物体上反射出的颜色，常与环境光相同
    GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };					// 镜面光照在物体上反射出的颜色
    GLfloat mat_emission[] = { color[0], color[1], color[2], color[3] };	// 物体本身产生的微弱光的颜色
    GLfloat mat_shininess = 90.0f;											// 镜面指数，表示某个面接近镜面的程度，取值0-128
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);						// 设置材质特性，参数一为将材质设定给一个面的正面或背面或两面
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

LightPlanet::LightPlanet(GLfloat selfRadius, GLfloat orbitRadius, GLfloat revolutionSpeed, GLfloat rotationSpeed, Star* parentStar, GLfloat rgbColor[3])
    :Planet(selfRadius, orbitRadius, revolutionSpeed, rotationSpeed, parentStar, rgbColor)
{
}

void LightPlanet::drawLight()
{
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// 光源位置
    GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// 光源的环境光分量
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };					// 光源的漫反光分量
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };					// 光源的镜面光分量
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);;
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
