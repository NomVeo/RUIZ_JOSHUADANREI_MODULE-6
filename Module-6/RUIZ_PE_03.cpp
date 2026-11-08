
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
using namespace std;

// Original point
float x = -0.4f;
float y = -0.3f;

// Scalar matrix value
float s = 2.0f;

// Transformed point
float newX;
float newY;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(12.0f);

    glBegin(GL_POINTS);

        // Original point - Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(x, y);

        // Transformed point - Red
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(newX, newY);

    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    // Scalar product matrix:
    // [ 2  0 ]
    // [ 0  2 ]

    newX = (s * x) + (0.0f * y);
    newY = (0.0f * x) + (s * y);

    // Print original and transformed coordinates.
    cout << "Scalar Product Matrix: " << endl;
    cout << "[ 2  0 ]" << endl;
    cout << "[ 0  2 ]" << endl;

    cout << "\nBefore: (" << x << ", " << y << ")" << endl;

    cout << "After:  (" << newX << ", " << newY << ")" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_PE_03");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK)
        return 1;
#endif

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
