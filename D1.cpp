#include "D1.h"

D1::D1()
{ }

D1::D1(const Config &_config)
{
	for (int i = 0; i < 8; i++)
	{
		Layer[i] = new DCLayer(_config.D1_drift_time_offset, _config.D1_calibration_times, _config.D1_calibration_distances, _config.D1_drift_time_min[i],_config.D1_drift_time_max[i],_config.D1_layer_min_hits[i],_config.D1_layer_max_hits[i]);
	}
	x_det_center = _config.D1_x_det_center;
	z_det_center = _config.D1_z_det_center;
	z_offset = _config.D1_z_offset;
	x_offset = _config.D1_x_offset;
	y_rotation_angle = _config.D1_y_rotation_angle;
}

D1::~D1()
{  
	for (int i = 0; i < 8; i++)
	{
		delete Layer[i];
	}
}

void D1::fill_good_hits(single_gh_data _good_hit_data)
{
	if (ND1L1 == _good_hit_data.layer) Layer[0] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L2 == _good_hit_data.layer) Layer[1] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L3 == _good_hit_data.layer) Layer[2] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L4 == _good_hit_data.layer) Layer[3] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L5 == _good_hit_data.layer) Layer[4] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L6 == _good_hit_data.layer) Layer[5] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L7 == _good_hit_data.layer) Layer[6] -> DCLayer::fill_rough_data(_good_hit_data);
	if (ND1L8 == _good_hit_data.layer) Layer[7] -> DCLayer::fill_rough_data(_good_hit_data);
}

bool D1::was_correct_event()
{
	correct_event = false;
	no_of_layers_with_hits = 0;
	bool correct_in_layer[8];
	for (int i = 0; i < 8; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
	}
	if (no_of_layers_with_hits >= 4)
	{
		correct_event = true;
	}
	return correct_event;
}

D1_hist_data* D1::get_hist_data()
{
	D1_hist_data* d1_data = new D1_hist_data();
	for (int i = 0; i < 8; i++)
	{
		d1_data -> layer_data[i] = Layer[i]-> DCLayer::get_hist_data();
	}
	return d1_data;
	//delete d1_data;
}

XZ_positions* D1::get_event_to_display()
{
	// for now - only one layer
	for (unsigned int i = 0; i < Layer[0] -> AbsoluteXPosition.size(); i++)
	{
		if (true)// there should be a condition which tells wheter a hit contributes to track or not - 04.10
		{
			AllHitsAbsolutePositionX.push_back(Layer[0] -> AbsoluteXPosition.at(i));
			AllHitsAbsolutePositionZ.push_back(Layer[0] -> AbsoluteZPosition.at(i));
		}
	}
	XZ_positions* d1_all_hits = new XZ_positions(AllHitsAbsolutePositionX, AllHitsAbsolutePositionZ);
	return d1_all_hits;
}

int D1::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}

void D1::calculate_distances_from_wires()
{
	for (int j = 0; j < 8; j++)
	{
		Layer[j] -> DCLayer::calculate_distances_from_wires();
	}
}

void D1::calculate_absolute_positions()
{
	// for now: layers with straight layers
	// LAYER 1
	Layer[0] -> RelativeZPosition = 3.3 - z_det_center; // move z positions of layers to config - 04.10
	// after rotation around the center of the detector
	double x_prim;
	double z_prim;
	for (unsigned int i = 0; i < Layer[0] -> Wire.size(); i++)
	{
		// change reading so that orientation of the x axis 
		// and direction of increasing of wires/elements were the same - 04.10

		// positions 
		Layer[0] -> RelativeXPosition.push_back( -x_det_center + 3 + 4*(41 - Layer[0] -> Wire.at(i)) );x_prim = cos(y_rotation_angle)*(Layer[0] -> RelativeXPosition.back()) + sin(y_rotation_angle)*(Layer[0] -> RelativeZPosition);
		z_prim = -sin(y_rotation_angle)*(Layer[0] -> RelativeXPosition.back()) + cos(y_rotation_angle)*(Layer[0] -> RelativeZPosition);;
		Layer[0] -> AbsoluteXPosition.push_back( x_prim + x_offset );
		Layer[0] -> AbsoluteZPosition.push_back( z_prim + z_offset );
	}
}


