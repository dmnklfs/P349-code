#include "CommonFunctions.h"

double get_x_after_rot_Y(double x, double z, double angle)
{
	double x_prim;
	x_prim = x*cos(angle) + z*sin(angle);
	return x_prim;
}

double get_z_after_rot_Y(double x, double z, double angle)
{
	double z_prim;
	z_prim = -x*sin(angle) + z*cos(angle);
	return z_prim;
}
