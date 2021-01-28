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

//private:
	int Size;
	double dt = 0.1;
	double tau = 0.5;
	double x_max = 60, x_min = 0;
	double y_max = 20, y_min = 0;

	vector<double> x;
	vector<double> y;
	vector<double> vx;
	vector<double> vy;
	vector<double> v_des;
};

#endif 