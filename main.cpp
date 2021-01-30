#include <iostream>
#include <glut.h>

#include "particles.h"
#include "anim.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 250);

    glutCreateWindow("Simulation");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    init();

    glutMainLoop();
}



