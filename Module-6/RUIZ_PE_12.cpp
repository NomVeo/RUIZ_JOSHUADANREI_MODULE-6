
#define GL_SILENCE_DEPRECATION
#include <cstdio>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

GLuint VBOid;

GLfloat vertices[] = {
     0.0f,  0.2f, 0.0f,
    -0.3f, -0.3f, 0.0f,
     0.3f, -0.3f, 0.0f
};

void translate(float x, float y, float z, int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV == NULL)
        return;

    float w = 1.0f;

    float tx = mapV[startindex] + x * w;
    float ty = mapV[startindex + 1] + y * w;
    float tz = mapV[startindex + 2] + z * w;

    mapV[startindex] = tx;
    mapV[startindex + 1] = ty;
    mapV[startindex + 2] = tz;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.0f, 0.8f, 0.2f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

void moveTriangle(int value)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    for (int i = 0; i < 9; i += 3)
        translate(0.0f, 0.1f, 0.0f, i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutPostRedisplay();

    // Repeat once every second.
    glutTimerFunc(1000, moveTriangle, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q12");

#ifndef __APPLE__
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        std::fprintf(stderr, "GLEW initialization failed: %s\n",
                     glewGetErrorString(glewStatus));
        return 1;
    }
#endif

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);
    glutTimerFunc(1000, moveTriangle, 0);

    glutMainLoop();
    return 0;
}
