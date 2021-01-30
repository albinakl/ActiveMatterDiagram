#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "particles.h"
#include "anim.h"

Particles::Particles(int Size)
{	
	vector <double> x;
	vector <double> y;
	vector <double> vx;
	vector <double> vy;
	vector <double> v_des;

	double vx_max = 1.0, vx_min = -1.0;
	double vy_max = 1.0, vy_min = -1.0;

	//srand(73);

	for (int i = 0; i < Size; i++) {
		x.push_back((double)rand() / (double)RAND_MAX * (Particles::x_max - Particles::x_min)  + Particles::x_min );
		y.push_back((double)rand() / (double)RAND_MAX * (Particles::y_max - Particles::y_min) * 0.8 + Particles::y_min + (Particles::y_max - Particles::y_min) * 0.1);

		vx.push_back((double)rand() / (double)RAND_MAX * (vx_max - vx_min) + vx_min);
		vy.push_back((double)rand() / (double)RAND_MAX * (vy_max - vy_min) + vy_min);
		
		if ((int)rand() % 2)
			v_des.push_back(Particles::v_des_1);
		else
			v_des.push_back(Particles::v_des_2);
	}

	Particles::Size = Size;
	Particles::x = x;
	Particles::y = y;
	Particles::vx = vx;
	Particles::vy = vy;
	Particles::v_des = v_des;
}

Particles::~Particles()
{
	Particles::x.clear();
	Particles::y.clear();
	Particles::vx.clear();
	Particles::vy.clear();
	Particles::v_des.clear();
}

void Particles::update_vel()
{
	vector<double> F_x(Particles::Size);
	vector<double> F_y(Particles::Size);
	
	double d, cx, cy, eps;
	double a, b;

	//F_des
	for (int i = 0; i < Particles::Size; i++) {
		F_x[i] = (-Particles::vx[i] + Particles::v_des[i]) / Particles::tau;
		F_y[i] = (-Particles::vy[i]) / Particles::tau;
	}
	//F_fluct
	for (int i = 0; i < Particles::Size; i++) {
		F_x[i] += Particles::sigma * 2 * ((double)rand() / (double)RAND_MAX - 0.5);
		F_y[i] += Particles::sigma * 2 * ((double)rand() / (double)RAND_MAX - 0.5);
	}
	//F_wall
	for (int i = 0; i < Particles::Size; i++) {
		//F_x[i] += 0;
		F_y[i] += Particles::U_0 / Particles::Delta_L * (exp(-Particles::y[i] / Particles::Delta_L) - exp((Particles::y[i] - Particles::y_max) / Particles::Delta_L));
	}
	//F_par
	for (int i = 0; i < Particles::Size; i++) {
		for (int k = 0; k < Particles::Size; k++) { //k != i
			if (k != i) {
				d = sqrt(pow(Particles::x[k] - Particles::x[i], 2) + pow(Particles::y[k] - Particles::y[i], 2));
				eps = d - 2 * Particles::R;
				cx = Particles::vx[k] / sqrt(pow(Particles::vx[k], 2) + pow(Particles::vy[k], 2));
				cy = Particles::vy[k] / sqrt(pow(Particles::vx[k], 2) + pow(Particles::vy[k], 2));
				F_x[k] += Particles::A * exp(-eps / Particles::B) * 1 / 2 * (Particles::x[k] - Particles::x[i]) / d * (1 - cx * (Particles::x[k] - Particles::x[i]) / d);
				F_y[k] += Particles::A * exp(-eps / Particles::B) * 1 / 2 * (Particles::y[k] - Particles::y[i]) / d * (1 - cy * (Particles::y[k] - Particles::y[i]) / d);
			}
		}
	}
	//F_chir
	for (int i = 0; i < Particles::Size; i++) {
		for (int j = 0; j < Particles::Size; j++) { //j != i
			if (j != i) {
				if ((Particles::vx[i] - Particles::vx[j]) * (Particles::x[j] - Particles::x[i]) + (Particles::vy[i] - Particles::vy[j]) * (Particles::y[j] - Particles::y[i]) > 0)
					if (Particles::vx[i] * Particles::vx[j] + Particles::vy[i] * Particles::vy[j] < 0)
						if (D - sqrt(pow(Particles::x[j] - Particles::x[i], 2) + pow(Particles::y[j] - Particles::y[i], 2)) > 0)
						{
							a = (Particles::x[j] - Particles::x[i]) / (pow((Particles::x[j] - Particles::x[i]), 2) + pow((Particles::y[j] - Particles::y[i]), 2));
							b = (Particles::y[j] - Particles::y[i]) / (pow((Particles::x[j] - Particles::x[i]), 2) + pow((Particles::y[j] - Particles::y[i]), 2));
							F_x[i] += b * Particles::chi;
							F_y[i] += -a * Particles::chi;
							F_x[j] += -b * Particles::chi;
							F_y[j] += a * Particles::chi;
						}
			}
		}
	}

	//update vel
	for (int i = 0; i < Particles::Size; i++) {
		Particles::vx[i] += Particles::dt * F_x[i];
		Particles::vy[i] += Particles::dt * F_y[i];
		/*if (Particles::vy[i] > 3)
			Particles::vy[i] = 3;
		if (Particles::vy[i] < -3)
			Particles::vy[i] = -3;*/
	}
}
	

void Particles::update_pos()
{
	for (int i = 0; i < Particles::Size; i++) {
		Particles::x[i] += Particles::vx[i] * Particles::dt;
		Particles::y[i] += Particles::vy[i] * Particles::dt;

		//periodic boundary conditions
		if (Particles::x[i] >= Particles::x_max)
			Particles::x[i] -= (Particles::x_max - Particles::x_min);
		else if (Particles::x[i] <= Particles::x_min)
			Particles::x[i] += (Particles::x_max - Particles::x_min);

		//reflecting boundary conditions
		if (Particles::y[i] >= Particles::y_max or Particles::y[i] <= Particles::y_min)
			Particles::vy[i] = -Particles::vy[i];
	}
	Particles::t += 1;
}

