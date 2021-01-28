#include <glut.h>
#include "anim.h"
#include "particles.h"

float x_position = 0.0;
int state = 1;
float angle = 0;
Particles Group(120);

void init()
{
    glClearColor(0, 0, 0, 1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //glShadeModel(GL_SMOOTH);
    glPointSize(5.0);

    //draw
    glBegin(GL_POINTS);

    // specify vertexes
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(x_position, 1.0);

    glEnd();

    //glFlush();
    glutSwapBuffers();
}

void display_particles()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //glShadeModel(GL_SMOOTH);
    glPointSize(5.0);

    //draw
    glBegin(GL_POINTS);
    
    // specify vertexes
    for (int i = 0; i < Group.Size; i++) {
        /*if (Group.vx[i] > 0)
            glColor3f(0.0, 1.0, 1.0);
        else
            glColor3f(0.0, 0.0, 1.0);*/
        glColor3f(0.0, 0.5 + 0.4 * Group.v_des[i], 1.0);
        glVertex2f(Group.x[i], Group.y[i]);
    }
    
    glEnd();

    //glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Group.x_min, Group.x_max, Group.y_min, Group.y_max);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    Group.update_vel();
    Group.update_pos();
    /*switch (state)
    {
    case 1:
    {
        if (x_position < 5)
            x_position += 0.15;
        else
            state = -1;
        break;
    }
    case -1:
    {
        if (x_position > -5)
            x_position -= 0.15;
        else
            state = 1;
        break;
    }
    }*/
}