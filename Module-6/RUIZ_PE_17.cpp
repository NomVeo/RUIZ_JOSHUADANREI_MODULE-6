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

void APIENTRY debugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    cout << "OpenGL Debug Message: " << message << endl;
    cout << "Error ID: " << id << endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

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
    glutCreateWindow("Ruiz_Q17");

#ifndef __APPLE__
    if (glewInit() != GLEW_OK)
    {
        cout << "GLEW initialization failed." << endl;
        return 1;
    }
#endif

    if (GLEW_KHR_debug || GLEW_VERSION_4_3)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(debugCallback, NULL);

        cout << "Debug callback registered." << endl;

        // Deliberately invalid enum to trigger the callback.
        glEnable(0xFFFFFFFF);
    }
    else
    {
        cout << "OpenGL debug output is not supported." << endl;
    }

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
