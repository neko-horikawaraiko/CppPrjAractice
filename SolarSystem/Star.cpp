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
    glEnable(GL_LINE_SMOOTH);	// �������������
    glEnable(GL_BLEND);			// ������ɫ��ϣ�Ϊ����alphaͨ������ɫ���л�ϣ��˴������һ��ʵ�����������

    glPushMatrix();

    // ������λ�ñ任
    if (parent_star != nullptr && parent_star->orbit_radius > 0)
    {
        glRotatef(parent_star->revo_angle, 0, 0, 1);
        glTranslatef(parent_star->orbit_radius, 0, 0);
    }

    // �����ģ��Բ�ι��
    int n = 1440;
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; ++i)
        glVertex2f(orbit_radius * cos(2 * PI * i / n), orbit_radius * sin(2 * PI * i / n));
    glEnd();

    // �����Լ�λ�ñ任
    glRotatef(revo_angle, 0, 0, 1);
    glTranslatef(orbit_radius, 0, 0);
    glRotatef(rota_angle, 0, 0, 1);

    // ������ɫ
    glColor3f(color[0], color[1], color[2]);
    glutSolidSphere(radius, 40, 32);		// ���������ֱ�Ϊ���߷ֳɵ�Ƭ����γ�߷ֳɵĲ���

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
    GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };						// ���������������Ϸ��������ɫ
    GLfloat mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };						// ���������������Ϸ��������ɫ�����뻷������ͬ
    GLfloat mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };					// ��������������Ϸ��������ɫ
    GLfloat mat_emission[] = { color[0], color[1], color[2], color[3] };	// ���屾�������΢�������ɫ
    GLfloat mat_shininess = 90.0f;											// ����ָ������ʾĳ����ӽ�����ĳ̶ȣ�ȡֵ0-128
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);						// ���ò������ԣ�����һΪ�������趨��һ�����������������
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
    GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// ��Դλ��
    GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };					// ��Դ�Ļ��������
    GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };					// ��Դ�����������
    GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };					// ��Դ�ľ�������
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);;
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}
