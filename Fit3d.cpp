#include "Fit3d.h"

Fit3d::Fit3d()
{

}

Fit3d::~Fit3d()
{

}

void Fit3d::set_values(double *_x, double *_y, double *_errors)
{
	x_straight[0] = _x[0];
	z_straight[0] = _y[0];
	errors_straight[0] = _errors[0];
	x_straight[1] = _x[1];
	z_straight[1] = _y[1];
	errors_straight[1] = _errors[1];
	x_straight[2] = _x[6];
	z_straight[2] = _y[6];
	errors_straight[2] = _errors[6];
	x_straight[3] = _x[7];
	z_straight[3] = _y[7];
	errors_straight[3] = _errors[7];
	x_inclined1[0] = _x[3];
	z_inclined1[0] = _y[3];
	errors_inclined1[0] = _errors[3];
	x_inclined1[1] = _x[4];
	z_inclined1[1] = _y[4];
	errors_inclined1[1] = _errors[4];
	x_inclined2[0] = _x[5];
	z_inclined2[0] = _y[5];
	errors_inclined2[0] = _errors[5];
	x_inclined2[1] = _x[6];
	z_inclined2[1] = _y[6];
	errors_inclined2[1] = _errors[6];
}

void Fit3d::fit_straight_layer()
{
	std::vector<double> results;
	MinuitFit * fit = MinuitFit::GetInstance();
	fit -> set_no_of_points(4);		
	fit -> MinuitFit::set_values(x_straight, z_straight, errors_straight);
	fit -> MinuitFit::perform_simplified_fit();
	results = fit -> MinuitFit::fit_with_minuit();
	z_x_a[0] = results.at(0);
	z_x_b[0] = results.at(1);
	results.clear();
}

void Fit3d::fit_inclined_layers()
{

}

