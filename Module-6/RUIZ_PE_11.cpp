
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

GLfloat positions[] = {
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Adjust the viewing angle.
    glRotatef(35.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(35.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -1.0f, 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, 0);

    glColorPointer(
        3, GL_FLOAT, 0,
        BUFFER_OFFSET(sizeof(positions))
    );

    glDrawArrays(GL_QUADS, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);

    glutCreateWindow("Ruiz_PE_11");

#ifndef __APPLE__
    GLenum glewStatus = glewInit();

    if (glewStatus != GLEW_OK)
    {
        std::fprintf(stderr, "GLEW initialization failed: %s\n",
                     glewGetErrorString(glewStatus));
        return 1;
    }
#endif

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -5.0, 5.0);

    glMatrixMode(GL_MODELVIEW);

    glGenBuffers(1, &VBOid);
    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(positions) + sizeof(colors),
        NULL,
        GL_STATIC_DRAW
    );

    // Upload position data.
    glBufferSubData(
        GL_ARRAY_BUFFER, 0,
        sizeof(positions), positions
    );

    // Upload color data.
    glBufferSubData(
        GL_ARRAY_BUFFER, sizeof(positions),
        sizeof(colors), colors
    );

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
