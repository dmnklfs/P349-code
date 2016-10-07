#include "Config.h"

// in order to set the coincidence between detectors see SingleEvent::was_correct_event() in SingleEvent.cpp
// in order to provide specific conditions for certain detector see function was_correct_event() in appropriate .cpp file

Config::Config()
{
	// here hit = one correct singal (leading and trailing edge corresponding to TWO hits from easyparser)
	start_hits = 1;
	start_time_min = -1500;
	start_time_max = 1500;

	TOF_hits  = 1; // if -1 is set - any number of hits is accepted
	TOF_time_min = -1500;
	TOF_time_max = 1500;
	TOF_element_min = 1;
	TOF_element_max = 10;

	Intermediate_hits  = -1; // if -1 is set - any number of hits is accepted
	Intermediate_time_min = -1500;
	Intermediate_time_max = 1500;
	Intermediate_element_min = 1;
	Intermediate_element_max = 16;

	// ---------DRIFT CHEMBER D1---------
	// detector position (all in cm)
	D1_x_det_center = 0.5*193.5; // 0.5 * detector dimensions
	D1_z_det_center = 0.5*19.2;
	D1_z_offset = 138.2; // up to the beginning of the detector (not: 1st layer)
	D1_x_offset = 2;
	D1_y_rotation_angle = (0)*3.14/180; // rad
	// drift time offset
	for (int i = 0; i < 120; i++) // for now, later: different vectors for all layers
	{
		D1_drift_time_offset.push_back(-50); // for now constant value
	}

	// time-space calibration
	double D1_drift_time[201]=
    {   0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 
    	60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 
    	114, 117, 120, 123, 126, 129, 132, 135, 138, 141, 144, 147, 150, 153, 156, 159, 
    	162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 192, 195, 198, 201, 204, 207, 
    	210, 213, 216, 219, 222, 225, 228, 231, 234, 237, 240, 243, 246, 249, 252, 255, 
    	258, 261, 264, 267, 270, 273, 276, 279, 282, 285, 288, 291, 294, 297, 300, 303, 
    	306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 345, 348, 351, 
    	354, 357, 360, 363, 366, 369, 372, 375, 378, 381, 384, 387, 390, 393, 396, 399, 
    	402, 405, 408, 411, 414, 417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 
    	450, 453, 456, 459, 462, 465, 468, 471, 474, 477, 480, 483, 486, 489, 492, 495, 
    	498, 501, 504, 507, 510, 513, 516, 519, 522, 525, 528, 531, 534, 537, 540, 543, 
    	546, 549, 552, 555, 558, 561, 564, 567, 570, 573, 576, 579, 582, 585, 588, 591, 594, 597, 600

    };

    double D1_distance[201]=
    {   0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 
    	0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 
    	0.28, 0.29, 0.30, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.40, 0.41, 
    	0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 
    	0.56, 0.57, 0.58, 0.59, 0.60, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 
    	0.70, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.80, 0.81, 0.82, 0.83, 
    	0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 
    	0.98, 0.99, 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.10, 1.11, 
    	1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 
    	1.26, 1.27, 1.28, 1.29, 1.30, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 
    	1.40, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.50, 1.51, 1.52, 1.53, 
    	1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.60, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67, 
    	1.68, 1.69, 1.70, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.80, 1.81, 
    	1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.90, 1.91, 1.92, 1.93, 1.94, 1.95, 
    	1.96, 1.97, 1.98, 1.99, 2.0

    };
    
    // calibration should be read from the file
	for (int i = 0; i < 201; i++)
	{
		D1_calibration_times.push_back(D1_drift_time[i]);
		D1_calibration_distances.push_back(D1_distance[i]);
	}
	
	
	for (int i = 0; i < 8; i++)
	{
		D1_layer_min_hits[i] = 1;
		D1_layer_max_hits[i] = 19;
		D1_drift_time_min[i] = 0;
		D1_drift_time_max[i] = 597;
	}
	
	// ---DRIFT CHEMBER D2---
	for (int i = 0; i < 6; i++)
	{
		D2_layer_min_hits[i] = 1;
		D2_layer_max_hits[i] = 19;
		D2_drift_time_min[i] = -1500;
		D2_drift_time_max[i] = 1500;
	}

	// ---HEX---
	for (int i = 0; i < 7; i++)
	{
		HEX_layer_min_hits[i] = 1;
		HEX_layer_max_hits[i] = 19;
		HEX_drift_time_min[i] = -1500;
		HEX_drift_time_max[i] = 1500;
	}

	// ---FIBER HODOSCOPE---
	// ranges of elements
	element_V_min = 0;
	element_V_max = 70;
	element_H_min = 0;
	element_H_max = 70;
	element_D_min = 0;
	element_D_max = 160;
	hit_V_min = 1;
	hit_V_max = 100;
	hit_H_min = 1;
	hit_H_max = 100;
	hit_D_min = 1;
	hit_D_max = 100;
}

Config::~Config()
{

}
