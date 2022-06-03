#include "SolarSystem.h"

const int WINDOW_X_POS = 50;
const int WINDOW_Y_POS = 50;
const int WIDTH = 700;
const int HEIGHT = 700;

SolarSystem solarSystem;

void onDisplay() 
{
    solarSystem.onDisplay();
}

void onUpdate()
{
    solarSystem.onUpdate();
}

void onKeyboard(unsigned char key, int x, int y)
{
    solarSystem.onKeyboard(key, x, y);
}

int main()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Solar System");

    glutDisplayFunc(onDisplay);
    glutIdleFunc(onUpdate);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();
    
    return 0;
}
