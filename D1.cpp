#include "D1.h"

D1::D1()
{ }

D1::D1(const Config &_config)
{
	fit_with_inclined = _config.fit_with_inclined;
	// constructors of the layers: drift time offset, calib times, calib dists, time min, time max, hits min, hits max
	Layer[0] = new DCLayer(1, _config.D1_L1_drift_time_offset, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances, _config.D1_drift_time_min[0],_config.D1_drift_time_max[0],_config.D1_layer_min_hits[0],_config.D1_layer_max_hits[0]);
	Layer[1] = new DCLayer(2, _config.D1_L2_drift_time_offset, _config.D1_L2_calibration_times, _config.D1_L2_calibration_distances, _config.D1_drift_time_min[1],_config.D1_drift_time_max[1],_config.D1_layer_min_hits[1],_config.D1_layer_max_hits[1]);
	Layer[2] = new DCLayer(3, _config.D1_L3_drift_time_offset, _config.D1_L3_calibration_times, _config.D1_L3_calibration_distances, _config.D1_drift_time_min[2],_config.D1_drift_time_max[2],_config.D1_layer_min_hits[2],_config.D1_layer_max_hits[2]);
	Layer[3] = new DCLayer(4, _config.D1_L4_drift_time_offset, _config.D1_L4_calibration_times, _config.D1_L4_calibration_distances, _config.D1_drift_time_min[3],_config.D1_drift_time_max[3],_config.D1_layer_min_hits[3],_config.D1_layer_max_hits[3]);
	Layer[4] = new DCLayer(5, _config.D1_L5_drift_time_offset, _config.D1_L5_calibration_times, _config.D1_L5_calibration_distances, _config.D1_drift_time_min[4],_config.D1_drift_time_max[4],_config.D1_layer_min_hits[4],_config.D1_layer_max_hits[4]);
	Layer[5] = new DCLayer(6, _config.D1_L6_drift_time_offset, _config.D1_L6_calibration_times, _config.D1_L6_calibration_distances, _config.D1_drift_time_min[5],_config.D1_drift_time_max[5],_config.D1_layer_min_hits[5],_config.D1_layer_max_hits[5]);
	Layer[6] = new DCLayer(7, _config.D1_L7_drift_time_offset, _config.D1_L7_calibration_times, _config.D1_L7_calibration_distances, _config.D1_drift_time_min[6],_config.D1_drift_time_max[6],_config.D1_layer_min_hits[6],_config.D1_layer_max_hits[6]);
	Layer[7] = new DCLayer(8, _config.D1_L8_drift_time_offset, _config.D1_L8_calibration_times, _config.D1_L8_calibration_distances, _config.D1_drift_time_min[7],_config.D1_drift_time_max[7],_config.D1_layer_min_hits[7],_config.D1_layer_max_hits[7]);
	for (int i = 0; i < 8; i++)
	{
		// init for inclined wires
		//if(2==i||3==i||4==i||5==i) Layer[i] = new DCLayer(i+1,_config.D2_drift_time_offset, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances, _config.D1_drift_time_min[i],_config.D1_drift_time_max[i],_config.D1_layer_min_hits[i],_config.D1_layer_max_hits[i]);
		// for all layers
		layer_wire_frame_offset[i] = _config.D1_layer_wire_frame_offset[i];
		layer_angle[i] = _config.D1_layer_angle[i];
		no_of_wires[i] = _config.D1_no_of_wires[i];
	}
	D1_no_of_planes_with_hits = 0;
	D1_no_of_cells_with_hits = 0;
	half_x_dim = _config.D1_half_x_dim;
	half_z_dim = _config.D1_half_z_dim;
	z_offset = _config.D1_z_offset;
	x_offset = _config.D1_x_offset;
	y_rotation_angle = _config.D1_y_rotation_angle;
	distance_to_1st_layer = _config.D1_distance_to_1st_layer;
	distance_between_straight_wires = _config.D1_distance_between_straight_wires;
	distance_between_inclined_wires = _config.D1_distance_between_inclined_wires;
	distance_between_layers = _config.D1_distance_between_layers;
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
	D1_no_of_planes_with_hits = 0;
	D1_no_of_cells_with_hits = 0;
	for (int i = 0; i < 8; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
		if (0!= Layer[i]-> Wire.size())
		{
			D1_no_of_planes_with_hits++;
			D1_no_of_cells_with_hits = D1_no_of_cells_with_hits + Layer[i]-> Wire.size();
		}
	}
	if (no_of_layers_with_hits == 8)
	{
		correct_event = true;
	}

	// dell it, choice of coincidences if one wire parametrized
//	double edge_val1, edge_val2, dtime1, dtime2;
//	int wire1, wire2;
//	bool was_in_range;
//	if (correct_in_layer[0]&&correct_in_layer[1]&&correct_in_layer[6]&&correct_in_layer[7])
//	{
//		dtime1 = Layer[0]->DriftTime.at(0);
//		dtime2 = Layer[1]->DriftTime.at(0);
//		wire1  = Layer[0]->Wire.at(0);
//		wire2  = Layer[1]->Wire.at(0);
//		if (wire2==wire1)
//		{
//			edge_val1 = -0.000000796867*(dtime1-45)*(dtime1-45)*(dtime1-45)+0.00190676*(dtime1-45)*(dtime1-45)-1.4683*(dtime1-45)+ 306.876;
//			edge_val2 = -0.000000796867*(dtime1+45)*(dtime1+45)*(dtime1+45)+0.00190676*(dtime1+45)*(dtime1+45)-1.4683*(dtime1+45)+ 266.876;
//			if (dtime2 >= edge_val2 && dtime2 <= edge_val1)
//			{
//				correct_event = true;
//			}
//		}
//		if (wire2==wire1+1)
//		{
//			edge_val1 = 0.00000128478*(dtime1-35)*(dtime1-35)*(dtime1-35)+0.00030667*(dtime1-35)*(dtime1-35)-1.27552*(dtime1-35)+ 375.903;
//			edge_val2 = 0.00000128478*(dtime1+35)*(dtime1+35)*(dtime1+35)+0.00030667*(dtime1+35)*(dtime1+35)-1.27552*(dtime1+35)+ 325.903;
//			if (dtime2 >= edge_val2 && dtime2 <= edge_val1)
//			{
//				correct_event = true;
//			}
//		}
//		//correct_event = true;
//	}

/*	int wire1;
	int wire2;
	int wire3;
	int wire4;
	int wire5;
	int wire6;
	int wire7;
	int wire8;
	bool pair1, pair2, pair3, pair4;
	if (correct_in_layer[0]&&correct_in_layer[1]&&correct_in_layer[2]&&correct_in_layer[3]&&correct_in_layer[4]&&correct_in_layer[5]&&correct_in_layer[6]&&correct_in_layer[7])
	{
		wire1 = Layer[0] -> DCLayer::Wire.at(0);
		wire2 = Layer[1] -> DCLayer::Wire.at(0);
		wire3 = Layer[2] -> DCLayer::Wire.at(0);
		wire4 = Layer[3] -> DCLayer::Wire.at(0);
		wire5 = Layer[4] -> DCLayer::Wire.at(0);
		wire6 = Layer[5] -> DCLayer::Wire.at(0);		
		wire7 = Layer[6] -> DCLayer::Wire.at(0);
		wire8 = Layer[7] -> DCLayer::Wire.at(0);
		//std::cout << wire1 << " " << wire2 << " " << wire7 << " " << wire8 << std::endl;
//		if ((wire2==wire1||wire2==wire1+1)&&(wire8==wire7||wire8==wire7+1))// wire1==19&&wire7==19&&wire2==20&&wire8==20) // ||wire2==wire1+1 ||wire8==wire7+1
//		{
//			correct_event = true;
//		}
		pair1 = false;
		pair2 = false;
		pair3 = false;
		pair4 = false;
		if (wire2==wire1||wire2==wire1+1) pair1 = true;
		if (wire3==wire4||wire3==wire4+1) pair2 = true;
		if (wire5==wire6||wire5==wire6+1) pair3 = true;
		if (wire8==wire7||wire8==wire7+1) pair4 = true;

		if (pair1&&pair2&&pair3&&pair4) correct_event = true;
	}
*/	
	return correct_event;
}

D1_hist_data* D1::get_hist_data()
{
	D1_hist_data* d1_data = new D1_hist_data();
	for (int i = 0; i < 8; i++)
	{
		d1_data -> layer_data[i] = Layer[i]-> DCLayer::get_hist_data();
	}
	d1_data -> D1_no_of_cells_with_hits = D1_no_of_cells_with_hits;
	d1_data -> D1_no_of_planes_with_hits = D1_no_of_planes_with_hits;
	return d1_data;
	//delete d1_data;
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

void D1::calculate_wire_positions_in_detector()
{
	//std::cout << "D1::calculate_relative_and_absolute_positions_straight" << std::endl;
	unsigned int no_of_hits_in_layer;
	double x, z;
	
	int no_of_layer;

	for (int i = 0; i < 8; i++)
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
			if (i==0||i==1||i==6||i==7) x = calc_position_in_detector(no_of_wires[no_of_layer]-(Layer[no_of_layer]->Wire.at(ii)), distance_between_straight_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			else x = calc_position_in_detector(no_of_wires[no_of_layer]-(Layer[no_of_layer]->Wire.at(ii)), distance_between_inclined_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			Layer[no_of_layer]->RelativeXPosition.push_back(x);
	
			Layer[no_of_layer]->AbsoluteXWirePosition.push_back(x);
			Layer[no_of_layer]->AbsoluteZPosition.push_back(z);
			//std::cout << i << " " << Layer[no_of_layer]->AbsoluteXWirePosition.at(0) << std::endl;
		}
	}
}

void D1::set_hits_absolute_positions() // works only if there is exactly one hit in all layers. in future - it should chose between correct hits
{
	double wirepos1, wirepos2;
	double hitx, wirex, dist_from_wire;
	int left_right[8];

	for (int i = 0; i < 4; i++)
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
	for (int i = 0; i < 8; i++)
	{
		wirex = Layer[i]-> AbsoluteXWirePosition.at(0);
		//std::cout << " ok " << std::endl;
		//std::cout << left_right[i] << std::endl;
		//std::cout << wirex << std::endl;
		//std::cout << " ok2 " << std::endl;
		dist_from_wire = Layer[i]-> HitsDistancesFromWires.at(0);
		if (i==0||i==1||i==6||i==7) hitx = wirex+left_right[i]*dist_from_wire;//*pow(TMath::Cos(31*TMath::DegToRad()),-1);
		if (i==2||i==3||i==4||i==5) hitx = wirex+left_right[i]*dist_from_wire*pow(TMath::Cos(31*TMath::DegToRad()),-1);
		Layer[i]->AbsoluteXHitPosition.push_back(hitx);
		//std::cout << "layer " << i << " " << Layer[i]->AbsoluteXHitPosition.at(0) << std::endl;

	}
}

// SIMPLIFIED CALIBRATION
// !!! this function can only work with suitable preselection conditions
data_for_D1_simple_calibration D1::get_data_for_simple_calibration()
{
	int straight_layers[4];
	straight_layers[0] =0;
	straight_layers[1] =1;
	straight_layers[2] =6;
	straight_layers[3] =7;

	data_for_D1_simple_calibration data_for_calibration;
	for (int i = 0; i < 4; i++)
	{
		data_for_calibration.positionsX[i]	= Layer[ straight_layers[i] ]->AbsoluteXWirePosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[ straight_layers[i] ]->AbsoluteZPosition.at(0);
		//std::cout << Layer[ straight_layers[i] ]->DriftTime.at(0) << std::endl;
		data_for_calibration.drift_times[i]	= Layer[ straight_layers[i] ]->DriftTime.at(0);
		data_for_calibration.distane_from_wire[i] = Layer[ straight_layers[i] ]->HitsDistancesFromWires.at(0);
		//data_for_calibration.left_right[i]	= Layer[ straight_layers[i] ]->LeftRight.at(0);
	}
	return data_for_calibration;
}

data_for_D1_calibration D1::get_data_for_calibration() // i need here only informations about wires and distances
{
	data_for_D1_calibration data_for_calibration;
	for (int i = 0; i < 8; i++)
	{
		data_for_calibration.positionsX[i]	= Layer[i] -> AbsoluteXWirePosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
		//std::cout << i << " " << Layer[i] -> AbsoluteXPosition.at(0) << " " << Layer[i] -> AbsoluteZPosition.at(0) << " " << Layer[i] -> DriftTime.at(0) << std::endl;
	}
	return data_for_calibration;
}

data_for_D1_track_reco D1::get_data_for_track_reco() // i need here only informations about wires and distances
{
	data_for_D1_track_reco data_for_calibration;
	for (int i = 0; i < 8; i++)
	{
		data_for_calibration.positionsHitsX[i]	= Layer[i] -> AbsoluteXHitPosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
	}
	return data_for_calibration;
}
