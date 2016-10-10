#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

// rotation around y axis
double get_x_after_rot_Y(double x, double z, double angle);
double get_z_after_rot_Y(double x, double z, double angle);

// !!! add rotation arout the x axis

// calculates position in the detector with respect to its center
double calc_position_in_detector(double element_no, double element_width, double offset_in_detector);
	// offset_in_detector - additional shift in the detector, like the distance from the frame of DC to its 1st wire in each layer

// calculates position in the lab with respect to some chosen point
double calc_position_in_lab(double position_in_detector, double detector_position, double detector_offset);
	// detector position - nominal position
	// detector_offset - offset from the nominal position

#endif