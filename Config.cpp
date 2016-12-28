#include "Config.h"

// in order to set the coincidence between detectors see SingleEvent::was_correct_event() in SingleEvent.cpp
// in order to provide specific conditions for certain detector see function was_correct_event() in appropriate .cpp file

Config::Config()
{
	// simple calibration
	no_of_iterations_in_simple_calibration = 1;
	no_of_bins_in_simple_calibration = 200;

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
	D1_half_x_dim = 0.5*168.0; // 0.5 * detector dimensions
	D1_half_z_dim = 0.5*19.2;
	D1_x_lab_position = 0;
    D1_z_lab_position = 0;
	D1_z_offset = 0; // up to the beginning of the detector (not: 1st layer)
	D1_x_offset = 0;
	D1_y_rotation_angle = (0)*3.14/180; // rad
	track_angle_min = 45;
	track_angle_max =130;
	// layers "offsets" - distances drom the frame
	D1_layer_wire_frame_offset[0] = 3;	// x
	D1_layer_wire_frame_offset[1] = 5;
	D1_layer_wire_frame_offset[2] = 0;
	D1_layer_wire_frame_offset[3] = 0;
	D1_layer_wire_frame_offset[4] = 0;
	D1_layer_wire_frame_offset[5] = 0;
	D1_layer_wire_frame_offset[6] = 3;
	D1_layer_wire_frame_offset[7] = 5;
	D1_distance_to_1st_layer = 3.3;	// z
	D1_distance_between_wires = 4;		// x
	D1_distance_between_layers = 1.8;	// z

	// drift time offset
	for (int i = 0; i < 120; i++) // for now, later: different vectors for all layers
	{
		D2_drift_time_offset.push_back(0);
		HEX_drift_time_offset.push_back(0);
	}

	D2_half_x_dim = 0.5*168.0; // 0.5 * detector dimensions
	D2_half_z_dim = 0.5*15.6;
	D2_x_lab_position = -18.4;
    D2_z_lab_position = -67.4;
	D2_z_offset = 0; // up to the beginning of the detector (not: 1st layer)
	D2_x_offset = 0;
	D2_y_rotation_angle = (0)*3.14/180; // rad
	D2_layer_wire_frame_offset[0] = -31.35;	// x
	D2_layer_wire_frame_offset[1] = -35.24;
	D2_layer_wire_frame_offset[2] = 7.18;
	D2_layer_wire_frame_offset[3] = 4.8433;
	D2_layer_wire_frame_offset[4] = 3.0;
	D2_layer_wire_frame_offset[5] = 5.0;
	D2_distance_to_1st_layer = 3.3;	// z
	D2_distance_between_wires = 4.0;		// x
	D2_distance_between_layers = 1.8;	// z

	HEX_half_x_dim = 0.5*150.0; // 0.5 * detector dimensions
	HEX_half_z_dim = 0.5*29.3;
	HEX_x_lab_position = -7.3;
    HEX_z_lab_position = -139.85;
	HEX_z_offset = 0; // up to the beginning of the detector (not: 1st layer)
	HEX_x_offset = 40;
	HEX_y_rotation_angle = (0)*3.14/180; // rad
	HEX_layer_wire_frame_offset[0] = 3.45;	// x
	HEX_layer_wire_frame_offset[1] = 10.65;
	HEX_layer_wire_frame_offset[2] = 9.75;
	HEX_layer_wire_frame_offset[3] = 4.35;
	HEX_layer_wire_frame_offset[4] = 3.5969;
	HEX_layer_wire_frame_offset[5] = 4.4969;
	HEX_layer_wire_frame_offset[6] = 3.35;
	HEX_distance_to_1st_layer = 6.0145;	// z
	HEX_distance_between_wires = 1.8;		// x
	HEX_distance_between_layers = 2.8785;	// z

	// this should be bear from somewhere
	double _D1_L1_drift_time_offset[41] =  {40, 40, 40, 46, 46, 46, 46, 46, 46, 46, 
											46, 46, 46, 40, 40, 40, 40, 40, 40, 40,
											34, 34, 34, 46, 40, 40, 40,  4, -2,  4,
											16, 10, 16, 16,  4, 16, 10, 10, 10, 10, 10};
	double _D1_L2_drift_time_offset[41] =  {28, 28, 28, 34, 28, 34, 34, 34, 34, 34,
											28, 28, 28, 28, 40, 40, 40, 40, 40, 40,
											40, 34, 34, 40, 46, 40, 40, 40, 16, 16,
											16, 10, 16, 16,  4, 16, 10, 10, 10 ,10 ,10};
	double _D1_L7_drift_time_offset[41] =  {28, 28, 46, 34, 28, 28, 28, 28, 28, 28,
											28, 28, 28, 40, 40, 40, 40, 40, 34, 34,
											34, 34, 34, 40, 40, 40, 40, 40, 40, 40,
											40, 40, 40, 40, 34, 40, 34, 40, 34, 28, 28};
	double _D1_L8_drift_time_offset[41] =  {28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
											28, 28, 28, 28, 34, 40, 40, 40, 34, 34,
											40, 34, 34, 34, 34, 34, 40, 40 ,40, 40,
											40, 40, 40, 40, 40, 40, 34, 40, 40, 40, 40};
	double _D2_L5_drift_time_offset[41] =  {46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 
											46, 46, 46, 46, 46, 46, 46, 46, 46, 43, 
											43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
											43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43};
	double _D2_L6_drift_time_offset[41] =  {43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 
											43, 43, 43, 43, 46, 46, 46, 46, 46, 46, 
											46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 
											46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46};


	for (int i = 0; i < 41; i++)
	{
		std::cout << i << std::endl;
		D1_L1_drift_time_offset.push_back(_D1_L1_drift_time_offset[i]); // for now constant value
		D1_L2_drift_time_offset.push_back(_D1_L2_drift_time_offset[i]);
		D1_L7_drift_time_offset.push_back(_D1_L7_drift_time_offset[i]);
		D1_L8_drift_time_offset.push_back(_D1_L8_drift_time_offset[i]);
		D2_L5_drift_time_offset.push_back(_D2_L5_drift_time_offset[i]);
		D2_L6_drift_time_offset.push_back(_D2_L6_drift_time_offset[i]);
	}

	// LINEAR CALIBRATION
	//double D1_drift_time[204]={ 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 114, 117, 120, 123, 126, 129, 132, 135, 138, 141, 144, 147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 192, 195, 198, 201, 204, 207, 210, 213, 216, 219, 222, 225, 228, 231, 234, 237, 240, 243, 246, 249, 252, 255, 258, 261, 264, 267, 270, 273, 276, 279, 282, 285, 288, 291, 294, 297, 300, 303, 306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 345, 348, 351, 354, 357, 360, 363, 366, 369, 372, 375, 378, 381, 384, 387, 390, 393, 396, 399, 402, 405, 408, 411, 414, 417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450, 453, 456, 459, 462, 465, 468, 471, 474, 477, 480, 483, 486, 489, 492, 495, 498, 501, 504, 507, 510, 513, 516, 519, 522, 525, 528, 531, 534, 537, 540, 543, 546, 549, 552, 555, 558, 561, 564, 567, 570, 573, 576, 579, 582, 585, 588, 591, 594, 597, 600, 603, 606, 609};
    //double D1_distance[204] = { 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.30, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.40, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.60, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.70, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.80, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.30, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 1.40, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.50, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.60, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67, 1.68, 1.69, 1.70, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.80, 1.81, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.90, 1.91, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2.0, 2.0, 2.0, 2.0};

	//GARFIELD CALIBRATION
    // drift times from garfield calibration, distances as in the linear calibration
    //double D1_drift_time[204]= { 0.000, 0.379, 1.097, 1.941, 2.772, 3.656, 4.474, 5.311, 6.355, 7.279, 8.229, 9.153, 10.170, 11.234, 12.231, 13.208, 14.232, 15.389, 16.539, 17.728, 18.932, 20.228, 21.597,  22.940, 24.243, 25.785, 27.301, 29.002, 30.372, 32.133, 33.735, 35.643, 37.358, 39.492, 41.293, 43.367, 45.202, 47.442, 49.469, 51.763, 53.936, 56.097, 58.536, 61.042, 63.103, 65.616, 68.108, 70.787, 72.961, 75.467, 77.980, 80.745, 83.510, 86.322, 88.868, 91.746, 94.492, 97.057, 100.235, 103.253, 105.659, 108.564, 111.502, 114.347, 117.618, 120.449, 123.693, 126.591, 129.583, 133.119, 135.904, 138.869, 142.379, 145.796, 148.175, 150.575, 154.623, 157.435, 161.138, 164.441, 167.645, 170.809, 174.133, 177.989, 180.734, 183.712, 187.654, 190.731, 194.693, 197.558, 200.603, 203.999, 207.695, 212.056, 215.047, 217.965, 221.083, 225.450, 228.787, 231.745, 235.036, 239.390, 242.920, 246.143, 249.979, 253.675, 256.706, 260.442, 263.613, 268.326, 271.649, 275.405, 278.735, 283.601, 286.220, 289.677, 294.097, 297.388, 301.290, 305.158, 309.320, 313.414, 316.173, 320.387, 323.571, 328.118, 331.296, 335.510, 339.638, 343.660, 348.153, 351.331, 355.066, 359.493, 363.090, 368.673, 372.609, 375.208, 378.731, 383.570, 387.525, 391.108, 396.153, 398.686, 403.937, 408.458, 412.619, 416.654, 421.068, 424.611, 428.619, 433.731, 436.921, 441.083, 446.214, 450.794, 454.184, 459.343, 463.597, 468.749, 472.239, 476.134, 480.488, 484.370, 489.329, 492.865, 500.084, 502.643, 506.771, 511.478, 516.975, 520.272, 523.762, 529.638, 533.660, 537.854,  540.832, 545.844, 549.534, 553.515, 556.001, 560.761, 563.207, 568.046, 570.453, 574.687, 577.878, 579.240, 583.648, 584.206, 588.135, 589.145, 590.641, 591.817, 594.689, 595.513, 598.245, 598.418, 599.335, 600.000, 602.000, 604.000, 606.000, 609.000};
	//double D1_distance[204]  = { 0.00, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.10, 0.11, 0.12, 0.13, 0.14, 0.15, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.26, 0.27, 0.28, 0.29, 0.30, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38, 0.39, 0.40, 0.41, 0.42, 0.43, 0.44, 0.45, 0.46, 0.47, 0.48, 0.49, 0.50, 0.51, 0.52, 0.53, 0.54, 0.55, 0.56, 0.57, 0.58, 0.59, 0.60, 0.61, 0.62, 0.63, 0.64, 0.65, 0.66, 0.67, 0.68, 0.69, 0.70, 0.71, 0.72, 0.73, 0.74, 0.75, 0.76, 0.77, 0.78, 0.79, 0.80, 0.81, 0.82, 0.83, 0.84, 0.85, 0.86, 0.87, 0.88, 0.89, 0.90, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.00, 1.01, 1.02, 1.03, 1.04, 1.05, 1.06, 1.07, 1.08, 1.09, 1.10, 1.11, 1.12, 1.13, 1.14, 1.15, 1.16, 1.17, 1.18, 1.19, 1.20, 1.21, 1.22, 1.23, 1.24, 1.25, 1.26, 1.27, 1.28, 1.29, 1.30, 1.31, 1.32, 1.33, 1.34, 1.35, 1.36, 1.37, 1.38, 1.39, 1.40, 1.41, 1.42, 1.43, 1.44, 1.45, 1.46, 1.47, 1.48, 1.49, 1.50, 1.51, 1.52, 1.53, 1.54, 1.55, 1.56, 1.57, 1.58, 1.59, 1.60, 1.61, 1.62, 1.63, 1.64, 1.65, 1.66, 1.67, 1.68, 1.69, 1.70, 1.71, 1.72, 1.73, 1.74, 1.75, 1.76, 1.77, 1.78, 1.79, 1.80, 1.81, 1.82, 1.83, 1.84, 1.85, 1.86, 1.87, 1.88, 1.89, 1.90, 1.91, 1.92, 1.93, 1.94, 1.95, 1.96, 1.97, 1.98, 1.99, 2.0, 2.0, 2.0, 2.0};

	// FOR LINEAR AND GARFIELD
//    for (int i = 0; i < 204; i++)
//	{
//		D1_L1_calibration_times.push_back(D1_drift_time[i]);
//		D1_L1_calibration_distances.push_back(D1_distance[i]);
//		D1_L2_calibration_times.push_back(D1_drift_time[i]);
//		D1_L2_calibration_distances.push_back(D1_distance[i]);
//		D1_L7_calibration_times.push_back(D1_drift_time[i]);
//		D1_L7_calibration_distances.push_back(D1_distance[i]);
//		D1_L8_calibration_times.push_back(D1_drift_time[i]);
//		D1_L8_calibration_distances.push_back(D1_distance[i]);
//	}

    //double D1_drift_time[201]= {0.000, 0.366, 1.060, 1.876, 2.680, 3.534, 4.325, 5.134, 6.143, 7.036, 7.955, 8.848, 9.831, 10.859, 11.823, 12.768, 13.758, 14.876, 15.987, 17.137, 18.301, 19.554, 20.877, 22.175, 23.435, 24.925, 26.391, 28.035, 29.359, 31.062, 32.611, 34.455, 36.113, 38.175, 39.917, 41.922, 43.695, 45.860, 47.820, 50.037, 52.138, 54.227, 56.585, 59.008, 61.000, 63.428, 65.838, 68.428, 70.529, 72.951, 75.380, 78.053, 80.727, 83.445, 85.906, 88.688, 91.342, 93.822, 96.894, 99.811, 102.137, 104.945, 107.785, 110.536, 113.697, 116.434, 119.570, 122.372, 125.263, 128.682, 131.374, 134.240, 137.633, 140.936, 143.236, 145.556, 149.469, 152.187, 155.766, 158.960, 162.057, 165.116, 168.329, 172.056, 174.709, 177.588, 181.399, 184.374, 188.203, 190.973, 193.916, 197.199, 200.772, 204.987, 207.879, 210.700, 213.714, 217.935, 221.161, 224.021, 227.201, 231.410, 234.822, 237.939, 241.646, 245.219, 248.149, 251.760, 254.826, 259.381, 262.594, 266.225, 269.444, 274.148, 276.679, 280.021, 284.294, 287.475, 291.247, 294.986, 299.009, 302.967, 305.634, 309.708, 312.786, 317.181, 320.252, 324.326, 328.317, 332.204, 336.548, 339.620, 343.231, 347.510, 350.987, 356.384, 360.188, 362.701, 366.106, 370.784, 374.608, 378.071, 382.948, 385.397, 390.473, 394.842, 398.865, 402.765, 407.032, 410.457, 414.332, 419.273, 422.357, 426.380, 431.341, 435.768, 439.045, 444.031, 448.144, 453.124, 456.497, 460.263, 464.472, 468.224, 473.018, 476.436, 483.415, 485.889, 489.879, 494.428, 499.743, 502.930, 506.303, 511.984, 515.871, 519.926, 522.805, 527.650, 531.216, 535.065, 537.468, 542.069, 544.434, 549.111, 551.438, 555.531, 558.615, 559.932, 564.193, 564.732, 568.530, 569.507, 570.953, 572.090, 574.866, 575.663, 578.304, 578.471, 579.357, 580.000, 580.000};

	// HOMOGENOUS IRRADIATION METHOD CALIBRATION
    // distances from homogenous irradiation method, time steps 0, 3, 6, 8, etc 
    double D1_drift_time[204]  = {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 66, 69, 72, 75, 78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 114, 117, 120, 123, 126, 129, 132, 135, 138, 141, 144, 147, 150, 153, 156, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 189, 192, 195, 198, 201, 204, 207, 210, 213, 216, 219, 222, 225, 228, 231, 234, 237, 240, 243, 246, 249, 252, 255, 258, 261, 264, 267, 270, 273, 276, 279, 282, 285, 288, 291, 294, 297, 300, 303, 306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 345, 348, 351, 354, 357, 360, 363, 366, 369, 372, 375, 378, 381, 384, 387, 390, 393, 396, 399, 402, 405, 408, 411, 414, 417, 420, 423, 426, 429, 432, 435, 438, 441, 444, 447, 450, 453, 456, 459, 462, 465, 468, 471, 474, 477, 480, 483, 486, 489, 492, 495, 498, 501, 504, 507, 510, 513, 516, 519, 522, 525, 528, 531, 534, 537, 540, 543, 546, 549, 552, 555, 558, 561, 564, 567, 570, 573, 576, 579, 582, 585, 588, 591, 594, 597, 600, 603, 606, 609};
    double D1_distance_l1[204] = {0,  0.00210409,  0.0080029,  0.0165479,  0.0280974,  0.0411263,  0.0549177,  0.070262,  0.0851469,  0.101309,  0.117563,  0.135158,  0.152992,  0.172168,  0.19229,  0.212899,  0.233242,  0.253934,  0.274589,  0.295152,  0.316,  0.336581,  0.357337,  0.378075,  0.39839,  0.419679,  0.440518,  0.459409,  0.478088,  0.49618,  0.51372,  0.529937,  0.546559,  0.561839,  0.57609,  0.590037,  0.603774,  0.617207,  0.630125,  0.643338,  0.656596,  0.669129,  0.681625,  0.694112,  0.705569,  0.718038,  0.729808,  0.74155,  0.753238,  0.765008,  0.776622,  0.788529,  0.799895,  0.811068,  0.822415,  0.833588,  0.845165,  0.856568,  0.868035,  0.878794,  0.889701,  0.900249,  0.911311,  0.921694,  0.931727,  0.942009,  0.952722,  0.963114,  0.97301,  0.983512,  0.993545,  1.00289,  1.01322,  1.0235,  1.03308,  1.04239,  1.0521,  1.06183,  1.07164,  1.08071,  1.09077,  1.09991,  1.10963,  1.1186,  1.12837,  1.13811,  1.14732,  1.15658,  1.16627,  1.17544,  1.1849,  1.19395,  1.20294,  1.21206,  1.22056,  1.22971,  1.23919,  1.24843,  1.25785,  1.26699,  1.27584,  1.28433,  1.29348,  1.30175,  1.31034,  1.3193,  1.32763,  1.33637,  1.34421,  1.35258,  1.36068,  1.36906,  1.37738,  1.3859,  1.39444,  1.40264,  1.41073,  1.41871,  1.42678,  1.435,  1.443,  1.45137,  1.45908,  1.46707,  1.47488,  1.4825,  1.49119,  1.49907,  1.5066,  1.514,  1.522,  1.52978,  1.53759,  1.54564,  1.55338,  1.56137,  1.56883,  1.57636,  1.58383,  1.59154,  1.59915,  1.60684,  1.61462,  1.62267,  1.6303,  1.63779,  1.64528,  1.65268,  1.66018,  1.66747,  1.67505,  1.68278,  1.6902,  1.69734,  1.70432,  1.71191,  1.71959,  1.72712,  1.73434,  1.7418,  1.74913,  1.75638,  1.76406,  1.77124,  1.77847,  1.78587,  1.79306,  1.80081,  1.80848,  1.81566,  1.82289,  1.83066,  1.83808,  1.84547,  1.85296,  1.86076,  1.86842,  1.87587,  1.88397,  1.89141,  1.89825,  1.90544,  1.91214,  1.91857,  1.92458,  1.93064,  1.93567,  1.94016,  1.94497,  1.94915,  1.95233,  1.95552,  1.95864,  1.96146,  1.96373,  1.96597,  1.96798,  1.97,  1.97155,  1.97301,  1.97477,  1.97621,  1.97757,  1.979};
    double D1_distance_l2[204] = {0,  0.00269214,  0.00952814,  0.0185509,  0.0299535,  0.0425229,  0.0561949,  0.0700047,  0.0842188,  0.0993058,  0.114641,  0.131088,  0.14725,  0.163596,  0.18029,  0.197059,  0.213386,  0.230449,  0.247043,  0.262194,  0.277152,  0.292212,  0.306481,  0.321384,  0.335754,  0.34905,  0.362887,  0.376486,  0.389854,  0.402268,  0.415048,  0.426984,  0.438864,  0.450873,  0.46211,  0.47377,  0.484327,  0.495776,  0.507334,  0.518866,  0.529671,  0.540733,  0.551346,  0.561627,  0.572093,  0.582411,  0.592757,  0.603066,  0.612879,  0.622692,  0.632817,  0.642851,  0.652618,  0.6629,  0.672722,  0.682342,  0.691695,  0.701894,  0.711183,  0.721079,  0.73035,  0.740393,  0.750114,  0.759559,  0.769051,  0.7789,  0.788906,  0.798655,  0.808422,  0.818299,  0.828323,  0.837879,  0.847178,  0.856393,  0.865627,  0.875146,  0.885382,  0.895039,  0.904255,  0.91427,  0.923513,  0.933703,  0.943121,  0.952704,  0.962122,  0.971448,  0.980902,  0.990651,  1.00068,  1.01031,  1.0199,  1.02937,  1.03916,  1.0484,  1.0584,  1.0678,  1.07775,  1.08712,  1.0964,  1.10627,  1.11596,  1.12532,  1.13498,  1.14477,  1.15394,  1.16349,  1.1727,  1.1819,  1.19119,  1.20027,  1.20938,  1.21916,  1.22889,  1.23777,  1.2471,  1.25619,  1.26589,  1.27502,  1.28423,  1.2929,  1.30186,  1.31101,  1.32057,  1.3303,  1.33938,  1.34886,  1.35833,  1.36834,  1.37772,  1.38762,  1.39735,  1.40756,  1.41778,  1.42809,  1.43906,  1.44989,  1.46081,  1.47211,  1.48347,  1.49525,  1.50647,  1.51806,  1.52982,  1.54122,  1.55392,  1.56636,  1.57839,  1.59028,  1.60218,  1.61414,  1.62492,  1.63601,  1.64736,  1.65781,  1.66776,  1.67783,  1.68747,  1.69702,  1.7065,  1.71573,  1.72496,  1.73437,  1.744,  1.7531,  1.76217,  1.77109,  1.77956,  1.78804,  1.79622,  1.80485,  1.81315,  1.82115,  1.82973,  1.83763,  1.84577,  1.85352,  1.86188,  1.87024,  1.87805,  1.88572,  1.8932,  1.90091,  1.90816,  1.91547,  1.9224,  1.92889,  1.9344,  1.93989,  1.94485,  1.94908,  1.95328,  1.95715,  1.96026,  1.96366,  1.96637,  1.96894,  1.971,  1.97323,  1.97512,  1.97677,  1.97851,  1.97995,  1.9816,  1.9831};
    double D1_distance_l3[204] = {0,  0.0032618,  0.0109064,  0.0217392,  0.0331326,  0.046143,  0.0599896,  0.0737443,  0.0880411,  0.102669,  0.116414,  0.13084,  0.145008,  0.159792,  0.174833,  0.189212,  0.203638,  0.218504,  0.233251,  0.248301,  0.263719,  0.279431,  0.294601,  0.309421,  0.324628,  0.340376,  0.355674,  0.37157,  0.388099,  0.4036,  0.41956,  0.435501,  0.451195,  0.467963,  0.484539,  0.50161,  0.518232,  0.534982,  0.552145,  0.569042,  0.585517,  0.602515,  0.619458,  0.636217,  0.653224,  0.671711,  0.688902,  0.705983,  0.722384,  0.739024,  0.755296,  0.770952,  0.786416,  0.801613,  0.815726,  0.829968,  0.843732,  0.856412,  0.868623,  0.88111,  0.89299,  0.90498,  0.916677,  0.92773,  0.939216,  0.95048,  0.961111,  0.972284,  0.983218,  0.993325,  1.00393,  1.01382,  1.02399,  1.03414,  1.04424,  1.05423,  1.06408,  1.07366,  1.08324,  1.09337,  1.10311,  1.11252,  1.1223,  1.13171,  1.14082,  1.1501,  1.15876,  1.16747,  1.17621,  1.18472,  1.19373,  1.20244,  1.21121,  1.21978,  1.22797,  1.23637,  1.24481,  1.25293,  1.26086,  1.26871,  1.27618,  1.28402,  1.29194,  1.29952,  1.30764,  1.31543,  1.32358,  1.33097,  1.33863,  1.34636,  1.35394,  1.36116,  1.36849,  1.37577,  1.3828,  1.38974,  1.39662,  1.4035,  1.41013,  1.41672,  1.42318,  1.42957,  1.43577,  1.44222,  1.44839,  1.45486,  1.46091,  1.4673,  1.47337,  1.47991,  1.48571,  1.49177,  1.49756,  1.50366,  1.50968,  1.5158,  1.52188,  1.52829,  1.53397,  1.5395,  1.54573,  1.55191,  1.55796,  1.56373,  1.56977,  1.57581,  1.58179,  1.58777,  1.59344,  1.59923,  1.60512,  1.61112,  1.61717,  1.62339,  1.62983,  1.63634,  1.64222,  1.64818,  1.65448,  1.66038,  1.66714,  1.67317,  1.67966,  1.68606,  1.69265,  1.69897,  1.70512,  1.71124,  1.71798,  1.72395,  1.73021,  1.73676,  1.74336,  1.74982,  1.75619,  1.76288,  1.76926,  1.77534,  1.78174,  1.78831,  1.79491,  1.80109,  1.80817,  1.81516,  1.82222,  1.82919,  1.83607,  1.84334,  1.85052,  1.85771,  1.86504,  1.87269,  1.88027,  1.88802,  1.89557,  1.90339,  1.91056,  1.91794,  1.92479,  1.93106,  1.93746,  1.94339,  1.94856,  1.9538};
    double D1_distance_l4[204] = {0,  0.00384066,  0.0116874,  0.0227775,  0.0357053,  0.0498091,  0.0650799,  0.0800015,  0.0967699,  0.113639,  0.130582,  0.147011,  0.16502,  0.181926,  0.197904,  0.214967,  0.230835,  0.246666,  0.261891,  0.277189,  0.292092,  0.306821,  0.321402,  0.335773,  0.349803,  0.362657,  0.376238,  0.389432,  0.401836,  0.414451,  0.427094,  0.438708,  0.450855,  0.463038,  0.47479,  0.485871,  0.497044,  0.508106,  0.519693,  0.531426,  0.542828,  0.553707,  0.564751,  0.575731,  0.586867,  0.598049,  0.609397,  0.619926,  0.631154,  0.642364,  0.653105,  0.663322,  0.674265,  0.684924,  0.695867,  0.706828,  0.716549,  0.726702,  0.737259,  0.748166,  0.759238,  0.769822,  0.779755,  0.789917,  0.800189,  0.810636,  0.821083,  0.831585,  0.841803,  0.852038,  0.862696,  0.873189,  0.884114,  0.894258,  0.904199,  0.914518,  0.924606,  0.934934,  0.945353,  0.955258,  0.965668,  0.976042,  0.986277,  0.996311,  1.0069,  1.0171,  1.02738,  1.03785,  1.04794,  1.05776,  1.06768,  1.07787,  1.08813,  1.0983,  1.10865,  1.11963,  1.13047,  1.14166,  1.15324,  1.1653,  1.17679,  1.18833,  1.20027,  1.21295,  1.22523,  1.23825,  1.25186,  1.26459,  1.27777,  1.29124,  1.30448,  1.31826,  1.33192,  1.34475,  1.35753,  1.36997,  1.38244,  1.39499,  1.40715,  1.41847,  1.42994,  1.44154,  1.45331,  1.46375,  1.47456,  1.48594,  1.49654,  1.50729,  1.51795,  1.52802,  1.53801,  1.54764,  1.55757,  1.56751,  1.57675,  1.58593,  1.59459,  1.60351,  1.61233,  1.62055,  1.62903,  1.63743,  1.64588,  1.65427,  1.66258,  1.67039,  1.67795,  1.68572,  1.69304,  1.70064,  1.7076,  1.71509,  1.72225,  1.72942,  1.73606,  1.74325,  1.75004,  1.75656,  1.76339,  1.76986,  1.77625,  1.78244,  1.78903,  1.79531,  1.80141,  1.80743,  1.81349,  1.81998,  1.82581,  1.83197,  1.83844,  1.84467,  1.8506,  1.85675,  1.86331,  1.86914,  1.87535,  1.88174,  1.88816,  1.8947,  1.9013,  1.9078,  1.91465,  1.92089,  1.92721,  1.93305,  1.93883,  1.94401,  1.94854,  1.95317,  1.95702,  1.96074,  1.96405,  1.96698,  1.96953,  1.97192,  1.97399,  1.97584,  1.97765,  1.97929,  1.98096,  1.98229,  1.98365,  1.98481};
    
    // FOR HOMOGENOUS CALIBRATION METHOD
	for (int i = 0; i < 204; i++)
	{
		D1_L1_calibration_times.push_back(D1_drift_time[i]);
		D1_L1_calibration_distances.push_back(D1_distance_l1[i]);
		D1_L2_calibration_times.push_back(D1_drift_time[i]);
		D1_L2_calibration_distances.push_back(D1_distance_l2[i]);
		D1_L7_calibration_times.push_back(D1_drift_time[i]);
		D1_L7_calibration_distances.push_back(D1_distance_l3[i]);
		D1_L8_calibration_times.push_back(D1_drift_time[i]);
		D1_L8_calibration_distances.push_back(D1_distance_l4[i]);
	}
	
	
	for (int i = 0; i < 8; i++)
	{
		if (i==0||i==1||i==6||i==7)
		//if (i==0||i==1)
		//if (true)
		{
			D1_layer_min_hits[i] = 1;
			D1_layer_max_hits[i] = 1;
			D1_drift_time_min[i] = 0;
			D1_drift_time_max[i] = 609;
		}
		else
		{
			D1_layer_min_hits[i] = 1;
			D1_layer_max_hits[i] = 1;
			D1_drift_time_min[i] = -1500;
			D1_drift_time_max[i] = 1500;
		}
	}
	
	// ---DRIFT CHEMBER D2---
	for (int i = 0; i < 6; i++)
	{
		if (i==4||i==5)
		//if (i==0||i==1)
		//if (true)
		{
			D2_layer_min_hits[i] = 1;
			D2_layer_max_hits[i] = 1;
			D2_drift_time_min[i] = 0;
			D2_drift_time_max[i] = 609;
		}
		else
		{
			D2_layer_min_hits[i] = -1;
			D2_layer_max_hits[i] = -1;
			D2_drift_time_min[i] = -1500;
			D2_drift_time_max[i] = 1500;
		}
	}

	// ---HEX---
	for (int i = 0; i < 7; i++)
	{
		if (i==0||i==3)
		//if (i==0||i==1)
		//if (true)
		{
			HEX_layer_min_hits[i] = 1;
			HEX_layer_max_hits[i] = 1;
			HEX_drift_time_min[i] = -1500;
			HEX_drift_time_max[i] = 1500;
		}
		else
		{
			HEX_layer_min_hits[i] = -1;
			HEX_layer_max_hits[i] = -1;
			HEX_drift_time_min[i] = -1500;
			HEX_drift_time_max[i] = 1500;
		}
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
