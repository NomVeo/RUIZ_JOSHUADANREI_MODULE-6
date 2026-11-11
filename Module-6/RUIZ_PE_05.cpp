#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <iostream>
using namespace std;

float A[4] = {
    1.0f, 2.0f,
    3.0f, 4.0f
};

float B[4] = {
    5.0f, 6.0f,
    7.0f, 8.0f
};

float C[4];

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    cout << "Result of Matrix Addition:" << endl;

    for (int i = 0; i < 4; i++)
        C[i] = A[i] + B[i];

    cout << C[0] << " " << C[1] << endl;
    cout << C[2] << " " << C[3] << endl;

    // Draw a simple triangle.
    glColor3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q05");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
