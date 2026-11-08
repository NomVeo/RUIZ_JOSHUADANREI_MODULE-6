
#define GL_SILENCE_DEPRECATION
#include <cstdio>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#define BUFFER_OFFSET(i) ((void*)(i))

#include <cmath>
#include <cstdlib>

GLuint VBOid;

GLfloat positions[] = {
    // Top face
    -0.4f,  0.4f, -0.4f,
     0.4f,  0.4f, -0.4f,
     0.4f,  0.4f,  0.4f,
    -0.4f,  0.4f,  0.4f,

    // Front face
    -0.4f,  0.4f, 0.4f,
     0.4f,  0.4f, 0.4f,
     0.4f, -0.4f, 0.4f,
    -0.4f, -0.4f, 0.4f,

    // Right face
     0.4f,  0.4f,  0.4f,
     0.4f,  0.4f, -0.4f,
     0.4f, -0.4f, -0.4f,
     0.4f, -0.4f,  0.4f
};

GLfloat colors[] = {
    // Top - Green
    0,1,0, 0,1,0, 0,1,0, 0,1,0,

    // Front - Red
    1,0,0, 1,0,0, 1,0,0, 1,0,0,

    // Right - Blue
    0,0,1, 0,0,1, 0,0,1, 0,0,1
};

void rotateZ(float degrees, int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV == NULL)
        return;

    float rad = degrees * 3.14159265f / 180.0f;

    float c = cosf(rad);
    float s = sinf(rad);

    float x = mapV[startindex];
    float y = mapV[startindex + 1];

    mapV[startindex] = c * x - s * y;
    mapV[startindex + 1] = s * x + c * y;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void translate(float x, float y, float z, int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV == NULL)
        return;

    mapV[startindex] += x;
    mapV[startindex + 1] += y;
    mapV[startindex + 2] += z;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColorPointer(3, GL_FLOAT, 0,
                   BUFFER_OFFSET(sizeof(positions)));

    glDrawArrays(GL_QUADS, 0, 12);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

void animate(int value)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    // Rotate first, then translate each vertex.
    for (int i = 0; i < 36; i += 3)
    {
        rotateZ(15.0f, i);
        translate(0.05f, 0.05f, 0.0f, i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutPostRedisplay();
    glutTimerFunc(1000, animate, 0);
}

void monitorKeyboard(unsigned char key, int, int)
{
    if (key == 27)
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBOid);
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q20");

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

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(positions) + sizeof(colors),
                 NULL, GL_DYNAMIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    sizeof(positions), positions);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(positions),
                    sizeof(colors), colors);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);
    glutKeyboardFunc(monitorKeyboard);
    glutTimerFunc(1000, animate, 0);

    glutMainLoop();
    return 0;
}
