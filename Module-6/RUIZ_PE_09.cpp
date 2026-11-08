
#define GL_SILENCE_DEPRECATION
#include <cstdio>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <cmath>

GLuint VBOid;

GLfloat vertices[] = {
    -0.3f,  0.3f, 0.0f,
     0.3f,  0.3f, 0.0f,
     0.3f, -0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f
};

void rotateZ(float degrees, int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV == NULL)
        return;

    float rad = degrees * 3.14159265f / 180.0f;

    GLfloat c = cosf(rad);
    GLfloat s = sinf(rad);

    GLfloat x = mapV[startindex];
    GLfloat y = mapV[startindex + 1];

    GLfloat rx = c * x - s * y;
    GLfloat ry = s * x + c * y;

    mapV[startindex] = rx;
    mapV[startindex + 1] = ry;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(0.0f, 0.3f, 1.0f);
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q09");

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

    // Rotate each vertex once by 45 degrees.
    for (int i = 0; i < 12; i += 3)
        rotateZ(45.0f, i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
