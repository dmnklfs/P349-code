#include "HEX.h"

HEX::HEX()
{ }

HEX::HEX(const Config &_config)
{
	for (int i = 0; i < 7; i++)
	{
		Layer[i] = new DCLayer(i, _config.HEX_drift_time_offset, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances, _config.HEX_drift_time_min[i],_config.HEX_drift_time_max[i],_config.HEX_layer_min_hits[i],_config.HEX_layer_max_hits[i]);
		layer_wire_frame_offset[i] = _config.HEX_layer_wire_frame_offset[i];
	}
	half_x_dim = _config.HEX_half_x_dim;
	half_z_dim = _config.HEX_half_z_dim;
	x_lab_position = _config.HEX_x_lab_position;
	z_lab_position = _config.HEX_z_lab_position;
	z_offset = _config.HEX_z_offset;
	x_offset = _config.HEX_x_offset;
	y_rotation_angle = _config.HEX_y_rotation_angle;
	distance_to_1st_layer = _config.HEX_distance_to_1st_layer;
	distance_between_wires = _config.HEX_distance_between_wires;
	distance_between_layers = _config.HEX_distance_between_layers;
}

HEX::~HEX()
{  
	for (int i = 0; i < 7; i++)
	{
		delete Layer[i];
	}
}

void HEX::fill_good_hits(single_gh_data _good_hit_data)
{
	if (NHEXL1 == _good_hit_data.layer) Layer[0] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL2 == _good_hit_data.layer) Layer[1] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL3 == _good_hit_data.layer) Layer[2] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL4 == _good_hit_data.layer) Layer[3] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL5 == _good_hit_data.layer) Layer[4] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL6 == _good_hit_data.layer) Layer[5] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL7 == _good_hit_data.layer) Layer[6] -> DCLayer::fill_rough_data(_good_hit_data);
}

bool HEX::was_correct_event()
{
	correct_event = false;
	no_of_layers_with_hits = 0;
	bool correct_in_layer[7];
	for (int i = 0; i < 7; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
	}
	if (no_of_layers_with_hits == 7)
	{
		correct_event = true;
	}
	return correct_event;
}

HEX_hist_data* HEX::get_hist_data()
{
	HEX_hist_data* HEX_data = new HEX_hist_data();
	for (int i = 0; i < 7; i++)
	{
		HEX_data -> layer_data[i] = Layer[i] -> DCLayer::get_hist_data();
	}
	return HEX_data;
}

int HEX::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}

void HEX::calculate_relative_and_absolute_positions()
{
	//std::cout << "D1::calculate_relative_and_absolute_positions" << std::endl;
	unsigned int no_of_hits_in_layer;
	double x_prim, z_prim;
	double x, z;
	int straight_layers[4];
	straight_layers[0] =0;
	straight_layers[1] =3; // there should be one more layer added 24.12.16
	
	int no_of_layer;

	// CALCULATIONS FOR THE STRAIGHT LAYERS
	for (int i = 0; i < 2; i++)
	{
		no_of_layer = straight_layers[i];
		no_of_hits_in_layer = Layer[no_of_layer] -> Wire.size();
		// std::cout << "no of hits: " << no_of_hits_in_layer << std::endl;
		// CALCULATION OF POSITIONS IN THE DETECTOR
		// Z COORDINATE
		// calculate_position_in_detector(double element_no, double element_width, double offset_in_detector)
		z = calc_position_in_detector(no_of_layer, distance_between_layers, - half_z_dim + distance_to_1st_layer);
		Layer[no_of_layer]->RelativeZPosition = z;
		
		// X COORDINATE
		for (unsigned int ii = 0; ii < no_of_hits_in_layer; ii++)
		{
			// change READING so that orientation of the x axis and direction of increasing of wires/elements were the same - 04.10
			x = calc_position_in_detector((-1+Layer[no_of_layer]->Wire.at(ii)), distance_between_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			//if(i == 2 || i == 3) x = 2+calc_position_in_detector(41-(Layer[no_of_layer]->Wire.at(ii)), distance_between_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			Layer[no_of_layer]->RelativeXPosition.push_back(x);
	
			x = Layer[no_of_layer]->RelativeXPosition.back();
			z = Layer[no_of_layer]->RelativeZPosition;
			
			// CALCULATE POSITION IN THE LAB
			// MAKE ROTATION AROUND Y AXIS
			x_prim = get_x_after_rot_Y(x, z, y_rotation_angle);
			z_prim = get_z_after_rot_Y(x, z, y_rotation_angle);

			// !!! MAKE ROTATION AROUND X AXIS

			// calc_position_in_lab(double position_in_detector, double detector_position, double detector_offset)
			x = calc_position_in_lab(x_prim, x_lab_position, x_offset);
			z = calc_position_in_lab(z_prim, z_lab_position, z_offset);

			Layer[no_of_layer]->AbsoluteXPosition.push_back(x);
			Layer[no_of_layer]->AbsoluteZPosition.push_back(z);
			//std::cout << "x: " << x << std::endl;
		}
	}
}

double HEX::test_get_chosen_position(int _no_of_layer)
{
	return Layer[_no_of_layer]->AbsoluteXPosition.at(0);
}

bool HEX::plot_event()
{
	bool plot_event = false;
	if (0!=AllHitsAbsolutePositionXEventDisplay.size()) plot_event = true;
	//std::cout << AllHitsAbsolutePositionXEventDisplay.size() << std::endl;
	return plot_event;
}

TGraph* HEX::get_all_hits_plot()
{
	TGraph* all_hits = new TGraph(AllHitsAbsolutePositionXEventDisplay.size(), &AllHitsAbsolutePositionXEventDisplay.at(0), &AllHitsAbsolutePositionZ.at(0));
	all_hits ->  SetMarkerStyle(20);
	return all_hits;
}

TGraph* HEX::get_detector_plot()
{
	TGraph* detector_plot;
	// coordinates of the corners of the detector
	double x_detector[5], z_detector[5];
	double x_lab[5], z_lab[5];
	double x_prim, z_prim; // after rotation
	x_detector[0] =(-half_x_dim);
	x_detector[1] =( half_x_dim);
	x_detector[2] =( half_x_dim);
	x_detector[3] =(-half_x_dim);
	x_detector[4] = x_detector[0];
	z_detector[0] =(-half_z_dim);
	z_detector[1] =(-half_z_dim);
	z_detector[2] =( half_z_dim);
	z_detector[3] =( half_z_dim);
	z_detector[4] = z_detector[0];
	for (int i = 0; i < 5; i++)
	{
		x_prim = get_x_after_rot_Y(x_detector[i], z_detector[i], y_rotation_angle);
		z_prim = get_z_after_rot_Y(x_detector[i], z_detector[i], y_rotation_angle);
		x_lab[i] = -calc_position_in_lab(x_prim, x_lab_position, x_offset);
		z_lab[i] = calc_position_in_lab(z_prim, z_lab_position, z_offset);
	}
	detector_plot = new TGraph(5, x_lab, z_lab);
	detector_plot ->SetLineColor(4);
	detector_plot ->SetLineWidth(4);
	detector_plot ->SetFillStyle(0);

	return detector_plot;
}

void HEX::collect_hits_from_all_layers()
{
	// this function can be called somewhere else, not only in the event display class...
	// loop over all entries in the certain layer
	int straight_layers[3];
	straight_layers[0] =0;
	straight_layers[1] =3;
	//straight_layers[2] =7;
	unsigned int no_of_entries; 

	int no_of_layer;
	for (int j = 0; j < 2; j++)
	{
		no_of_layer = straight_layers[j];
		no_of_entries = Layer[ no_of_layer ] -> AbsoluteXPosition.size();
		//std::cout << no_of_entries << std::endl;
		for (unsigned int i = 0; i < no_of_entries; i++)
		{
			if (true)// there should be a condition which tells wheter a hit contributes to track or not - 04.10
			{
				AllHitsAbsolutePositionX.push_back(Layer[ no_of_layer ] -> AbsoluteXPosition.at(i));
				AllHitsAbsolutePositionXEventDisplay.push_back( -(Layer[ no_of_layer ] -> AbsoluteXPosition.at(i)) );
				AllHitsAbsolutePositionZ.push_back(Layer[ no_of_layer ] -> AbsoluteZPosition.at(i));
			}
		}
	}	
}