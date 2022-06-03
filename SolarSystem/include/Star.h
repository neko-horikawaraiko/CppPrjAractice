#pragma once
#include <glut/glut.h>

class Star
{
public:
    Star(GLfloat selfRadius, GLfloat orbitRadius, GLfloat revolutionSpeed, GLfloat rotationSpeed, Star* parentStar, GLfloat color[3]);
    virtual ~Star() = 0 {};

    void drawStar();
    virtual void draw() { drawStar(); }
    virtual void update(long duration);

protected:
    GLfloat orbit_radius;	// ����뾶
    GLfloat revo_speed;		// ��ת�ٶ�
    GLfloat rota_speed;		// ��ת�ٶ�
    GLfloat color[4];	    // ��ɫ
    GLfloat revo_angle;     // ��ת�Ƕ�
    GLfloat rota_angle;     // ��ת�Ƕ�
    GLfloat radius;         // ����뾶��С
    Star* parent_star;		// ������
};

class Planet :public Star
{
public:
    Planet(GLfloat selfRadius, GLfloat orbitRadius, GLfloat revolutionSpeed, GLfloat rotationSpeed, Star* parentStar, GLfloat color[3]);
    virtual ~Planet() = default;

    void drawPlanet();
    virtual void draw() override 
    { 
        drawPlanet(); 
        drawStar(); 
    }
};

class LightPlanet :public Planet
{
public:
    LightPlanet(GLfloat selfRadius, GLfloat orbitRadius, GLfloat revolutionSpeed, GLfloat rotationSpeed, Star* parentStar, GLfloat color[3]);
    ~LightPlanet() = default;

    void drawLight();
    virtual void draw() override {
        drawLight(); 
        drawPlanet(); 
        drawStar();
    }

};
