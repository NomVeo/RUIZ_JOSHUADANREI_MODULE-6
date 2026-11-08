
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

// Pyramid face: 3 vertices.
GLfloat pyramidPositions[] = {
     0.0f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

GLfloat pyramidColors[] = {
    1,0,0,
    0,1,0,
    0,0,1
};

// Cube face: 4 vertices.
GLfloat cubePositions[] = {
    -0.4f,  0.4f, 0.0f,
     0.4f,  0.4f, 0.0f,
     0.4f, -0.4f, 0.0f,
    -0.4f, -0.4f, 0.0f
};

GLfloat cubeColors[] = {
    1,1,0,
    0,1,1,
    1,0,1,
    1,0.5f,0
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, VBOid);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Draw pyramid on the left.
    glVertexPointer(3, GL_FLOAT, 0,
                    BUFFER_OFFSET(0));

    glColorPointer(3, GL_FLOAT, 0,
                   BUFFER_OFFSET(
                       sizeof(pyramidPositions) +
                       sizeof(cubePositions)
                   ));

    glPushMatrix();
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glPopMatrix();

    // Draw cube face on the right.
    glVertexPointer(3, GL_FLOAT, 0,
                    BUFFER_OFFSET(sizeof(pyramidPositions)));

    glColorPointer(3, GL_FLOAT, 0,
                   BUFFER_OFFSET(
                       sizeof(pyramidPositions) +
                       sizeof(cubePositions) +
                       sizeof(pyramidColors)
                   ));

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Ruiz_Q18");

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

    // Reserve space for all four data blocks.
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(pyramidPositions) +
                 sizeof(cubePositions) +
                 sizeof(pyramidColors) +
                 sizeof(cubeColors),
                 NULL, GL_STATIC_DRAW);

    // Upload the four blocks.
    glBufferSubData(GL_ARRAY_BUFFER, 0,
                    sizeof(pyramidPositions), pyramidPositions);

    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(pyramidPositions),
                    sizeof(cubePositions), cubePositions);

    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(pyramidPositions) + sizeof(cubePositions),
                    sizeof(pyramidColors), pyramidColors);

    glBufferSubData(GL_ARRAY_BUFFER,
                    sizeof(pyramidPositions) + sizeof(cubePositions) +
                    sizeof(pyramidColors),
                    sizeof(cubeColors), cubeColors);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
