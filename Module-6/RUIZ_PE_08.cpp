
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
    -0.3f,  0.3f, 0.0f,
     0.3f,  0.3f, 0.0f,
     0.3f, -0.3f, 0.0f,
    -0.3f, -0.3f, 0.0f
};

void scale(float sx, float sy, float sz, int startindex)
{
    GLfloat* mapV = (GLfloat*)glMapBuffer(
        GL_ARRAY_BUFFER, GL_READ_WRITE
    );

    if (mapV == NULL)
        return;

    GLfloat sa[] = {
        sx,   0.0f, 0.0f, 0.0f,
        0.0f, sy,   0.0f, 0.0f,
        0.0f, 0.0f, sz,   0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat w = 1.0f;

    GLfloat x = mapV[startindex];
    GLfloat y = mapV[startindex + 1];
    GLfloat z = mapV[startindex + 2];

    mapV[startindex] =
        sa[0] * x + sa[1] * y + sa[2] * z + sa[3] * w;

    mapV[startindex + 1] =
        sa[4] * x + sa[5] * y + sa[6] * z + sa[7] * w;

    mapV[startindex + 2] =
        sa[8] * x + sa[9] * y + sa[10] * z + sa[11] * w;

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(1.0f, 0.5f, 0.0f);
    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q08");

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

    // Scale every vertex by 2.
    for (int i = 0; i < 12; i += 3)
        scale(2.0f, 2.0f, 2.0f, i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
