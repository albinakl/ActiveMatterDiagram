#include <iostream>
#include <glut.h>

//#include <fstream>
//#include <string>

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

    //Particles Group(320);
    //int stop_flag = 0;
    //double chi;

    //ofstream outfile;
    //outfile.open("PhaseDiagramData.txt");
    //
    //for (int N = 10; N < 510; N += 50) {
    //    for (int chi_fract = 0; chi_fract < 35; chi_fract += 5) {
    //        chi = 0.01 * chi_fract;
    //        Particles Group(N, chi);
    //        stop_flag = 0;

    //        while (Group.t < 1000 && stop_flag == 0) {
    //            Group.update_vel();
    //            Group.update_pos();

    //            if (Group.t % 10 == 0)
    //                stop_flag = Group.count_lanes();
    //        }

    //        if (stop_flag == 0) {
    //            //case chaotic
    //            outfile << N << ' ' << chi << ' ' << "-1" << endl;
    //            cout << N << ' ' << chi << ' ' << "-1" << endl;
    //        }
    //        else {
    //            //case lanes
    //            outfile << N << ' ' << chi << ' ' << Group.nlanes << endl;
    //            cout << N << ' ' << chi << ' ' << Group.nlanes << endl;
    //        }

    //    }
    //}
    //outfile.close();
}



