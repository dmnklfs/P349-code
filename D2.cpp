#include "D2.h"

D2::D2()
{ }

D2::D2(const Config &_config)
{
	Layer[0] = new DCLayer(1, _config.D2_L1_drift_time_offset, _config.D1_L1_calibration_times, _config.D2_L1_calibration_distances, _config.D2_drift_time_min[0],_config.D2_drift_time_max[0],_config.D2_layer_min_hits[0],_config.D2_layer_max_hits[0]);
	Layer[1] = new DCLayer(2, _config.D2_L2_drift_time_offset, _config.D1_L2_calibration_times, _config.D2_L2_calibration_distances, _config.D2_drift_time_min[1],_config.D2_drift_time_max[1],_config.D2_layer_min_hits[1],_config.D2_layer_max_hits[1]);
	Layer[2] = new DCLayer(3, _config.D2_L3_drift_time_offset, _config.D1_L3_calibration_times, _config.D2_L3_calibration_distances, _config.D2_drift_time_min[2],_config.D2_drift_time_max[2],_config.D2_layer_min_hits[2],_config.D2_layer_max_hits[2]);
	Layer[3] = new DCLayer(4, _config.D2_L4_drift_time_offset, _config.D1_L4_calibration_times, _config.D2_L4_calibration_distances, _config.D2_drift_time_min[3],_config.D2_drift_time_max[3],_config.D2_layer_min_hits[3],_config.D2_layer_max_hits[3]);
	Layer[4] = new DCLayer(5, _config.D2_L5_drift_time_offset, _config.D1_L5_calibration_times, _config.D2_L5_calibration_distances, _config.D2_drift_time_min[4],_config.D2_drift_time_max[4],_config.D2_layer_min_hits[4],_config.D2_layer_max_hits[4]);
	Layer[5] = new DCLayer(6, _config.D2_L6_drift_time_offset, _config.D1_L6_calibration_times, _config.D2_L6_calibration_distances, _config.D2_drift_time_min[5],_config.D2_drift_time_max[5],_config.D2_layer_min_hits[5],_config.D2_layer_max_hits[5]);
		
	for (int i = 0; i < 6; i++)
	{
		layer_wire_frame_offset[i] = _config.D2_layer_wire_frame_offset[i];
		layer_angle[i] = _config.D2_layer_angle[i];
		no_of_wires[i] = _config.D2_no_of_wires[i];
	}
	D2_no_of_planes_with_hits = 0;
	D2_no_of_cells_with_hits = 0;
	half_x_dim = _config.D2_half_x_dim;
	half_z_dim = _config.D2_half_z_dim;
	z_offset = _config.D2_z_offset;
	x_offset = _config.D2_x_offset;
	y_rotation_angle = _config.D2_y_rotation_angle;
	distance_to_1st_layer = _config.D2_distance_to_1st_layer;
	distance_between_straight_wires = _config.D2_distance_between_straight_wires;
	distance_between_inclined_wires = _config.D2_distance_between_inclined_wires;
	distance_between_layers = _config.D2_distance_between_layers;
}

D2::~D2()
{  
	for (int i = 0; i < 6; i++)
	{
		delete Layer[i];
	}
}

void D2::fill_good_hits(single_gh_data _good_hit_data)
{
	if (ND2L1 == _good_hit_data.layer) Layer[0]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L2 == _good_hit_data.layer) Layer[1]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L3 == _good_hit_data.layer) Layer[2]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L4 == _good_hit_data.layer) Layer[3]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L5 == _good_hit_data.layer) Layer[4]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L6 == _good_hit_data.layer) Layer[5]->DCLayer::fill_rough_data(_good_hit_data);
}

bool D2::was_correct_event()
{
	correct_event = false;
	no_of_layers_with_hits = 0;
	bool correct_in_layer[6];
	D2_no_of_planes_with_hits = 0;
	D2_no_of_cells_with_hits = 0;
	for (int i = 0; i < 6; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
		if (0!= Layer[i]-> Wire.size())
		{
			D2_no_of_planes_with_hits++;
			D2_no_of_cells_with_hits = D2_no_of_cells_with_hits + Layer[i]-> Wire.size();
		}
	}
	if (no_of_layers_with_hits == 6)
	{
		correct_event = true;
	}

//	int wire1;
//	int wire2;
//	if (correct_in_layer[4]&&correct_in_layer[5])
//	{
//		wire1 = Layer[4] -> DCLayer::Wire.at(0);
//		wire2 = Layer[5] -> DCLayer::Wire.at(0);
//		//std::cout << wire1 << " " << wire2 << " " << wire7 << " " << wire8 << std::endl;
//		if (wire1==15&&wire2==15)//(wire2==wire1||wire2==wire1+1)) // ||wire2==wire1+1 ||wire8==wire7+1
//		{
//			correct_event = true;
//		}
//	}

	return correct_event;
}

D2_hist_data* D2::get_hist_data()
{
	D2_hist_data* D2_data = new D2_hist_data();
	for (int i = 0; i < 6; i++)
	{
		D2_data -> layer_data[i] = Layer[i]-> DCLayer::get_hist_data();
	}
	D2_data -> D2_no_of_cells_with_hits = D2_no_of_cells_with_hits;
	D2_data -> D2_no_of_planes_with_hits = D2_no_of_planes_with_hits;
	return D2_data;
}

int D2::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}

void D2::calculate_wire_positions_in_detector()
{
	//std::cout << "D1::calculate_relative_and_absolute_positions_straight" << std::endl;
	unsigned int no_of_hits_in_layer;
	double x_prim, z_prim;
	double x, z;
	int no_of_layer;

	// CALCULATIONS FOR THE STRAIGHT LAYERS
	for (int i = 0; i < 6; i++)
	{
		no_of_layer = i;
		no_of_hits_in_layer = Layer[no_of_layer] -> Wire.size();

		// CALCULATION OF POSITIONS IN THE DETECTOR
		// Z COORDINATE
		// calculate_position_in_detector(double element_no, double element_width, double offset_in_detector)
		z = calc_position_in_detector(no_of_layer, distance_between_layers, - half_z_dim + distance_to_1st_layer);
		
		// X COORDINATE
		for (unsigned int ii = 0; ii < no_of_hits_in_layer; ii++)
		{
			//std::cout << "no_of_wires[no_of_layer] " << no_of_wires[no_of_layer] << std::endl;
			//std::cout << "Wire.at(ii) " << Layer[no_of_layer]->Wire.at(ii) << std::endl;
			// change READING so that orientation of the x axis and direction of increasing of wires/elements were the same - 04.10
			if (i==4||i==5)
			{
				x = calc_position_in_detector(no_of_wires[no_of_layer]-(Layer[no_of_layer]->Wire.at(ii)), distance_between_straight_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			}
			else x = calc_position_in_detector(no_of_wires[no_of_layer]-(Layer[no_of_layer]->Wire.at(ii)), distance_between_inclined_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);

			Layer[no_of_layer]->AbsoluteXWirePosition.push_back(x);
			Layer[no_of_layer]->AbsoluteZPosition.push_back(z);
		}
		//std::cout << Layer[no_of_layer]->AbsoluteXWirePosition.at(0) << std::endl;
	}
}

void D2::calculate_distances_from_wires()
{
	for (int j = 0; j < 6; j++)
	{
		Layer[j] -> DCLayer::calculate_distances_from_wires();
	}
}


void D2::set_hits_absolute_positions()
{
	double wirepos1, wirepos2;
	double hitx, wirex, dist_from_wire;
	int left_right[6];

	for (int i = 0; i < 3; i++)
	{
		wirepos1 = Layer[2*i  ]->AbsoluteXWirePosition.at(0);
		wirepos2 = Layer[2*i+1]->AbsoluteXWirePosition.at(0);
		if (wirepos1 > wirepos2)
		{
			left_right[2*i] 	= -1;
			left_right[2*i+1] 	= +1;
		}
		else
		{
			left_right[2*i] 	= +1;
			left_right[2*i+1] 	= -1;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		wirex = Layer[i]-> AbsoluteXWirePosition.at(0);
		dist_from_wire = Layer[i]-> HitsDistancesFromWires.at(0);
		if (i==4||i==5) hitx = wirex+left_right[i]*dist_from_wire;//*pow(TMath::Cos(31*TMath::DegToRad()),-1);
		if (i==0||i==1||i==2||i==3) hitx = wirex+left_right[i]*dist_from_wire*pow(TMath::Cos(31*TMath::DegToRad()),-1);
		Layer[i]->AbsoluteXHitPosition.push_back(hitx);
		//std::cout << "layer " << i << " " << Layer[i]->AbsoluteXHitPosition.at(0) << std::endl;
	}

}

data_for_D2_calibration D2::get_data_for_calibration() // i need here only informations about wires and distances
{
	data_for_D2_calibration data_for_calibration;
	for (int i = 0; i < 6; i++)
	{
		//std::cout << "layer " << i << " absolute x position " << Layer[i] -> AbsoluteXPosition.at(0) << std::endl;
		//std::cout << "layer " << i << " absolute z position " << Layer[i] -> AbsoluteZPosition.at(0) << std::endl;
		data_for_calibration.positionsX[i]	= Layer[i] -> AbsoluteXWirePosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
		//std::cout << i << " " << Layer[i] -> AbsoluteXPosition.at(0) << " " << Layer[i] -> AbsoluteZPosition.at(0) << " " << Layer[i] -> DriftTime.at(0) << std::endl;
	}
	return data_for_calibration;
}

data_for_D2_track_reco D2::get_data_for_track_reco() // i need here only informations about wires and distances
{
	data_for_D2_track_reco data_for_calibration;
	for (int i = 0; i < 6; i++)
	{
		data_for_calibration.positionsHitsX[i]	= Layer[i] -> AbsoluteXHitPosition.at(0);
		//std::cout << "a" << std::endl;
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
	}
	return data_for_calibration;
}