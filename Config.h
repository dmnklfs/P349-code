#ifndef CONFIG_H
#define CONFIG_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "CommonFunctions.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TClonesArray.h"
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TGaxis.h>
#include <TF1.h>

class Config
{
public:
	Config();
	~Config();

	// simple calibraton
	int no_of_iterations_in_simple_calibration;
	int no_of_bins_in_simple_calibration;

	// configuration
	// ---START---
	// no of correct signals (leading & trailing edge) in up (down) layer
	int start_hits;
	// time range for signals
	double start_time_min;
	double start_time_max;
	// detector position
	// ...

	// ---TOF---
	// no of correct signals (leading & trailing edge) in up (down) layer
	int TOF_hits;
	// time range for signals
	double TOF_time_min;
	double TOF_time_max;
	// range of selected elements (1 - 10)
	int TOF_element_min;
	int TOF_element_max;
	// detector position
	// ...

	// ---Intermediate---
	// no of correct signals (leading & trailing edge) in up (down) layer
	int Intermediate_hits;
	// time range for signals
	double Intermediate_time_min;
	double Intermediate_time_max;
	// range of selected elements (1 - 10)
	int Intermediate_element_min;
	int Intermediate_element_max;
	// detector position
	// ...

	// tracks angles
	double track_angle_min;
	double track_angle_max;

	// ---DRIFT CHAMBER D1---
	bool fit_with_inclined;
	bool unbiased_fit;
	// min and max number of hits in layers (if set to -1: any value is ok)
	int D1_layer_max_hits[8];
	int D1_layer_min_hits[8];
	double D1_half_x_dim;
    double D1_half_z_dim;
    double D1_x_lab_position;
    double D1_z_lab_position;
    double D1_z_offset;
    double D1_x_offset;
    double D1_y_rotation_angle;
    double D1_layer_wire_frame_offset[8];
    double D1_distance_to_1st_layer; // distance from the DC frame to the 1st layer (looking from the beam direction)
    double D1_distance_between_straight_wires;
    double D1_distance_between_inclined_wires;
    double D1_distance_between_layers;
    double D1_layer_angle[8]; // (measured with respect to the y axis) ---- change, 13.01.17
    int    D1_no_of_wires[8];

	// drift time range
	double D1_drift_time_max[8];
	double D1_drift_time_min[8];

	// drift time offset ---> should be different for different layers
	std::vector<double> D1_L1_drift_time_offset;
	std::vector<double> D1_L2_drift_time_offset;
	std::vector<double> D1_L3_drift_time_offset;
	std::vector<double> D1_L4_drift_time_offset;
	std::vector<double> D1_L5_drift_time_offset;
	std::vector<double> D1_L6_drift_time_offset;
	std::vector<double> D1_L7_drift_time_offset;
	std::vector<double> D1_L8_drift_time_offset;

	std::vector<double> D2_L5_drift_time_offset;
	std::vector<double> D2_L6_drift_time_offset;

	// calibration ---> should be different for different layers
	std::vector<double> D1_L1_calibration_times;
	std::vector<double> D1_L1_calibration_distances;
	std::vector<double> D1_L2_calibration_times;
	std::vector<double> D1_L2_calibration_distances;
	std::vector<double> D1_L3_calibration_times;
	std::vector<double> D1_L3_calibration_distances;
	std::vector<double> D1_L4_calibration_times;
	std::vector<double> D1_L4_calibration_distances;
	std::vector<double> D1_L5_calibration_times;
	std::vector<double> D1_L5_calibration_distances;
	std::vector<double> D1_L6_calibration_times;
	std::vector<double> D1_L6_calibration_distances;
	std::vector<double> D1_L7_calibration_times;
	std::vector<double> D1_L7_calibration_distances;
	std::vector<double> D1_L8_calibration_times;
	std::vector<double> D1_L8_calibration_distances;
	// ---DRIFT CHEMBER D2---
	// min and max number of hits in layers (if set to -1: any value is ok)
	std::vector<double> D2_drift_time_offset;
	int D2_layer_max_hits[6];
	int D2_layer_min_hits[6];

	// drift time range
	double D2_drift_time_max[6];
	double D2_drift_time_min[6];

	// dimensions
	double D2_half_x_dim;
    double D2_half_z_dim;
    double D2_x_lab_position;
    double D2_z_lab_position;
    double D2_z_offset;
    double D2_x_offset;
    double D2_y_rotation_angle;
    double D2_layer_wire_frame_offset[7];
    double D2_distance_to_1st_layer; // distance from the DC frame to the 1st layer (looking from the beam direction)
    double D2_distance_between_wires;
    double D2_distance_between_layers;

	// ---HEX---
	// min and max number of hits in layers (if set to -1: any value is ok)
	std::vector<double> HEX_drift_time_offset;
	int HEX_layer_max_hits[7];
	int HEX_layer_min_hits[7];

	// drift time range
	double HEX_drift_time_max[7];
	double HEX_drift_time_min[7];

	// dimessions
	double HEX_half_x_dim;
    double HEX_half_z_dim;
    double HEX_x_lab_position;
    double HEX_z_lab_position;
    double HEX_z_offset;
    double HEX_x_offset;
    double HEX_y_rotation_angle;
    double HEX_layer_wire_frame_offset[7];
    double HEX_distance_to_1st_layer; // distance from the DC frame to the 1st layer (looking from the beam direction)
    double HEX_distance_between_wires;
    double HEX_distance_between_layers;

	// ---FIBER HODOSCOPE---
	// ranges of elements
	int element_V_min, element_V_max;
	int element_H_min, element_H_max;
	int element_D_min, element_D_max;
	int hit_V_min, hit_V_max;
	int hit_H_min, hit_H_max;
	int hit_D_min, hit_D_max;

};

#endif