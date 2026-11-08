
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

GLuint VBOid;
bool ready = false;

GLfloat positions[] = {
    // Top face
    -0.4f, 0.4f, -0.4f,
     0.4f, 0.4f, -0.4f,
     0.4f, 0.4f,  0.4f,
    -0.4f, 0.4f,  0.4f,

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

void animate(int value)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    // Move each of the 12 vertices diagonally.
    for (int i = 0; i < 36; i += 3)
        translate(0.05f, 0.05f, 0.0f, i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutPostRedisplay();
    glutTimerFunc(1000, animate, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q15");

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

    // Scale the position data down by half once.
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV != NULL)
    {
        for (int i = 0; i < 36; i += 3)
        {
            mapV[i] *= 0.5f;
            mapV[i + 1] *= 0.5f;
            mapV[i + 2] *= 0.5f;
        }

        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ready = true;

    glutDisplayFunc(display);
    glutTimerFunc(1000, animate, 0);

    glutMainLoop();
    return 0;
}
