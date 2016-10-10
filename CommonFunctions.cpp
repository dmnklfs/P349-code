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

double calc_position_in_detector(double element_no, double element_width, double offset_in_detector)
{
	double position_in_detector;
	position_in_detector = element_width*element_no + offset_in_detector;
	return position_in_detector;
}

double calc_position_in_lab(double position_in_detector, double detector_position, double detector_offset)
{
	// apply global offsets
	double position_in_lab;
	position_in_lab = position_in_detector + detector_position + detector_offset;
	return position_in_lab;
}

