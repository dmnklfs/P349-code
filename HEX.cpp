#include "HEX.h"

HEX::HEX()
{ }

HEX::HEX(const Config &_config)
{
	fit_with_inclined = _config.fit_with_inclined;
	// constructors of the layers: drift time offset, calib times, calib dists, time min, time max, hits min, hits max
	Layer[0] = new DCLayer(1, _config.HEX_L1_drift_time_offset, _config.HEX_L1_calibration_times, _config.HEX_L1_calibration_distances, _config.HEX_drift_time_min[0],_config.HEX_drift_time_max[0],_config.HEX_layer_min_hits[0],_config.HEX_layer_max_hits[0]);
	Layer[1] = new DCLayer(2, _config.HEX_L2_drift_time_offset, _config.HEX_L2_calibration_times, _config.HEX_L2_calibration_distances, _config.HEX_drift_time_min[1],_config.HEX_drift_time_max[1],_config.HEX_layer_min_hits[1],_config.HEX_layer_max_hits[1]);
	Layer[2] = new DCLayer(3, _config.HEX_L3_drift_time_offset, _config.HEX_L3_calibration_times, _config.HEX_L3_calibration_distances, _config.HEX_drift_time_min[2],_config.HEX_drift_time_max[2],_config.HEX_layer_min_hits[2],_config.HEX_layer_max_hits[2]);
	Layer[3] = new DCLayer(4, _config.HEX_L4_drift_time_offset, _config.HEX_L4_calibration_times, _config.HEX_L4_calibration_distances, _config.HEX_drift_time_min[3],_config.HEX_drift_time_max[3],_config.HEX_layer_min_hits[3],_config.HEX_layer_max_hits[3]);
	Layer[4] = new DCLayer(5, _config.HEX_L5_drift_time_offset, _config.HEX_L5_calibration_times, _config.HEX_L5_calibration_distances, _config.HEX_drift_time_min[4],_config.HEX_drift_time_max[4],_config.HEX_layer_min_hits[4],_config.HEX_layer_max_hits[4]);
	Layer[5] = new DCLayer(6, _config.HEX_L6_drift_time_offset, _config.HEX_L6_calibration_times, _config.HEX_L6_calibration_distances, _config.HEX_drift_time_min[5],_config.HEX_drift_time_max[5],_config.HEX_layer_min_hits[5],_config.HEX_layer_max_hits[5]);
	Layer[6] = new DCLayer(7, _config.HEX_L7_drift_time_offset, _config.HEX_L7_calibration_times, _config.HEX_L7_calibration_distances, _config.HEX_drift_time_min[6],_config.HEX_drift_time_max[6],_config.HEX_layer_min_hits[6],_config.HEX_layer_max_hits[6]);
	for (int i = 0; i < 6; i++)
	{
		layer_wire_frame_offset[i] = _config.HEX_layer_wire_frame_offset[i];
		layer_angle[i] = _config.HEX_layer_angle[i];
		no_of_wires[i] = _config.HEX_no_of_wires[i];
	}
	HEX_no_of_planes_with_hits = 0;
	HEX_no_of_cells_with_hits = 0;
	half_x_dim = _config.HEX_half_x_dim;
	half_z_dim = _config.HEX_half_z_dim;
	z_offset = _config.HEX_z_offset;
	x_offset = _config.HEX_x_offset;
	y_rotation_angle = _config.HEX_y_rotation_angle;
	distance_to_1st_layer = _config.HEX_distance_to_1st_layer;
	distance_between_straight_wires = _config.HEX_distance_between_straight_wires;
	distance_between_inclined_wires = _config.HEX_distance_between_inclined_wires;
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
	for (int i = 0; i < 6; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
		if (0!= Layer[i]-> Wire.size())
		{
			HEX_no_of_planes_with_hits++;
			HEX_no_of_cells_with_hits = HEX_no_of_cells_with_hits + Layer[i]-> Wire.size();
		}
	}
	/*if (no_of_layers_with_hits == 6)
	{
		correct_event = true;
	}*/

	int wire1;
	int wire2;
	int wire3;
	int wire4;
	int wire5;
	int wire6;
	int wire7;
	bool pair1, pair2, pair3, pair4;
	if (correct_in_layer[0]&&correct_in_layer[1]&&correct_in_layer[2]&&correct_in_layer[3]&&correct_in_layer[4]&&correct_in_layer[5])
	{
		wire1 = Layer[0] -> DCLayer::Wire.at(0);
		wire2 = Layer[1] -> DCLayer::Wire.at(0);
		wire3 = Layer[2] -> DCLayer::Wire.at(0);
		wire4 = Layer[3] -> DCLayer::Wire.at(0);
		wire5 = Layer[4] -> DCLayer::Wire.at(0);
		wire6 = Layer[5] -> DCLayer::Wire.at(0);

		pair1 = false;
		pair2 = false;
		pair3 = false;
		if (wire4==wire1||wire4+1==wire1) pair1 = true;
		//if ((wire2==wire1-1||wire2==wire1-2)&&(wire3==wire1||wire3==wire1-1)&&(wire2==wire3||wire3==wire2+1)) pair2 = true;
		//if ((wire5==wire1+1||wire5==wire1+2)&&(wire6==wire1||wire6==wire1+1)&&(wire5==wire6||wire6==wire5-1)) pair3 = true;
		if (wire2==wire3||wire3==wire2+1) pair2 = true;
		if (wire5==wire6||wire6==wire5-1) pair3 = true;
		if (pair1&&pair2&&(pair3)) correct_event = true;
	}

	return correct_event;
}

HEX_hist_data* HEX::get_hist_data()
{
	HEX_hist_data* hex_data = new HEX_hist_data();
	for (int i = 0; i < 7; i++)
	{
		hex_data -> layer_data[i] = Layer[i] -> DCLayer::get_hist_data();
	}
	hex_data -> HEX_no_of_cells_with_hits = HEX_no_of_cells_with_hits;
	hex_data -> HEX_no_of_planes_with_hits = HEX_no_of_planes_with_hits;
	return hex_data;
}

int HEX::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}

void HEX::calculate_distances_from_wires()
{
	for (int j = 0; j < 7; j++)
	{
		Layer[j] -> DCLayer::calculate_distances_from_wires();
	}
}

void HEX::calculate_wire_positions_in_detector()
{
	//std::cout << "D1::calculate_relative_and_absolute_positions" << std::endl;
	unsigned int no_of_hits_in_layer;
	double x, z;
	
	int no_of_layer;

	// CALCULATIONS FOR THE STRAIGHT LAYERS
	for (int i = 0; i < 6; i++)
	{
		no_of_layer = i;
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
			//std::cout << "ok" << std::endl;
			x = calc_position_in_detector((Layer[no_of_layer]->Wire.at(ii)), distance_between_straight_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			//std::cout << "wires " << i << " " << Layer[no_of_layer]->Wire.at(ii) << " " << x << std::endl;
			//std::cout << "wires r " << i << " " << no_of_wires[no_of_layer]-(49-Layer[no_of_layer]->Wire.at(ii)) << " " << x << std::endl;
			Layer[no_of_layer]->AbsoluteXWirePosition.push_back(x);
			Layer[no_of_layer]->AbsoluteZPosition.push_back(z);
		}
	}
}

void HEX::set_hits_absolute_positions() // works only if there is exactly one hit in all layers. in future - it should chose between correct hits
{
	double wirepos1, wirepos2;
	double hitx, wirex, dist_from_wire;
	int left_right[7];
	int layer_pairs[6];
	layer_pairs[0] = 0;
	layer_pairs[1] = 3;
	layer_pairs[2] = 1;
	layer_pairs[3] = 2;
	layer_pairs[4] = 4;
	layer_pairs[5] = 5;
	for (int i = 0; i < 3; i++)
	{
		wirepos1 = Layer[layer_pairs[2*i]]  ->AbsoluteXWirePosition.at(0);
		wirepos2 = Layer[layer_pairs[2*i+1]]->AbsoluteXWirePosition.at(0);
		//if (i==2) std::cout << wirepos1 << " " << wirepos2 << std::endl;
		if (wirepos1 > wirepos2)
		{
			left_right[layer_pairs[2*i]]	= -1;
			left_right[layer_pairs[2*i+1]] 	= +1;
		}
		else
		{
			left_right[layer_pairs[2*i]] 	= +1;
			left_right[layer_pairs[2*i+1]] 	= -1;
		}
	}
	//std::cout << left_right[0] << left_right[3] << std::endl;
	for (int i = 0; i < 6; i++)
	{
		wirex = Layer[i]-> AbsoluteXWirePosition.at(0);
		dist_from_wire = Layer[i]-> HitsDistancesFromWires.at(0);
		if (i==0||i==3||i==6)       hitx = wirex+left_right[i]*dist_from_wire;//*pow(TMath::Cos(31*TMath::DegToRad()),-1);
		else hitx = wirex+left_right[i]*dist_from_wire*1.773*pow(1.8,-1)*pow(TMath::Cos(10*TMath::DegToRad()),-1);
		Layer[i]->AbsoluteXHitPosition.push_back(hitx);
		//std::cout << i << " " << hitx << std::endl;
		//std::cout << "layer " << i << " " << Layer[i]->AbsoluteXHitPosition.at(0) << std::endl;
	}
}

data_for_HEX_calibration HEX::get_data_for_calibration() // i need here only informations about wires and distances
{
	data_for_HEX_calibration data_for_calibration;
	for (int i = 0; i < 6; i++)
	{
		//std::cout << "layer " << i << " absolute x position " << Layer[i] -> AbsoluteXWirePosition.at(0) << std::endl;
		//std::cout << "layer " << i << " absolute z position " << Layer[i] -> AbsoluteZPosition.at(0) << std::endl;
		data_for_calibration.positionsX[i]	= Layer[i] -> AbsoluteXWirePosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
		//std::cout << i+1 << " " << Layer[i] -> AbsoluteXWirePosition.at(0) << " " << Layer[i] -> AbsoluteZPosition.at(0) << " " << Layer[i] -> DriftTime.at(0) << std::endl;
	}
	return data_for_calibration;
}

data_for_HEX_track_reco HEX::get_data_for_track_reco() // i need here only informations about wires and distances
{
	data_for_HEX_track_reco data_for_calibration;
	for (int i = 0; i < 6; i++)
	{
		data_for_calibration.positionsWiresX[i]	= Layer[i] -> Wire.at(0);
		data_for_calibration.positionsHitsX[i]	= Layer[i] -> AbsoluteXHitPosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
	}
	return data_for_calibration;
}