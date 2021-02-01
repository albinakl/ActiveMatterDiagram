#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>

using namespace std;

class Particles
{
public:
	Particles(int Size = 10);
	~Particles();

	void update_vel();
	void update_pos();
	int count_lanes();

//private:
	int Size, t = 0;
	
	double dt = 0.1, tau = 0.5;
	double x_max = 60, x_min = 0;
	double y_max = 20, y_min = 0;
	double v_des_1 = 1.34, v_des_2 = -1.34;
	
	double sigma = 0.1;
	double U_0 = 10, Delta_L = 0.2;
	double R = 0.2, B = 0.3, A = 2.1;
	double D = 4, chi = 0.0;

	int nlanes, repetitions_of_nlanes;

	vector<double> x;
	vector<double> y;
	vector<double> vx;
	vector<double> vy;
	vector<double> v_des;
};

#endif 