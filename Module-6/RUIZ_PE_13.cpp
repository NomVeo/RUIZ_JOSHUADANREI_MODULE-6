#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

struct Vec4
{
    float x, y, z, w;
};

Vec4 rotateZ(Vec4 v, float degrees)
{
    float rad = degrees * 3.14159265f / 180.0f;

    float c = cosf(rad);
    float s = sinf(rad);

    Vec4 result;

    result.x = c * v.x - s * v.y;
    result.y = s * v.x + c * v.y;
    result.z = v.z;
    result.w = v.w;

    // Rotation affects direction vectors (w = 0)
    // because the rotation matrix has no translation component.
    // Unlike translation, rotation does not depend on w.
    return result;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Vec4 position = {1.0f, 0.0f, 0.0f, 1.0f};
    Vec4 direction = {1.0f, 0.0f, 0.0f, 0.0f};

    Vec4 rotatedPosition = rotateZ(position, 45.0f);
    Vec4 rotatedDirection = rotateZ(direction, 45.0f);

    cout << "Rotated Position: ("
         << rotatedPosition.x << ", "
         << rotatedPosition.y << ")" << endl;

    cout << "Rotated Direction: ("
         << rotatedDirection.x << ", "
         << rotatedDirection.y << ")" << endl;

    glPointSize(12.0f);

    glBegin(GL_POINTS);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(position.x, position.y);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(rotatedPosition.x, rotatedPosition.y);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(rotatedDirection.x, rotatedDirection.y);

    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q13");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
