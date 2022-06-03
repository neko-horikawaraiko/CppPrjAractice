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
    GLfloat orbit_radius;	// 轨道半径
    GLfloat revo_speed;		// 公转速度
    GLfloat rota_speed;		// 自转速度
    GLfloat color[4];	    // 颜色
    GLfloat revo_angle;     // 公转角度
    GLfloat rota_angle;     // 自转角度
    GLfloat radius;         // 星球半径大小
    Star* parent_star;		// 父星球
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
