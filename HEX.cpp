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
	x_lab_position = _config.HEX_x_lab_position;
	z_lab_position = _config.HEX_z_lab_position;
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
		if (j==0||j==3||j==6||((j==1||j==2||j==4||j==5)&&fit_with_inclined))
		Layer[j] -> DCLayer::calculate_distances_from_wires();
	}
}

void HEX::calculate_relative_and_absolute_positions_straight()
{
	//std::cout << "D1::calculate_relative_and_absolute_positions" << std::endl;
	unsigned int no_of_hits_in_layer;
	double x_prim, z_prim;
	double x, z;
	int straight_layers[3];
	straight_layers[0] =0;
	straight_layers[1] =3;
	straight_layers[2] =6;
	
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
			//x = calc_position_in_detector(no_of_wires[no_of_layer]-(Layer[no_of_layer]->Wire.at(ii)), distance_between_straight_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			x = calc_position_in_detector((Layer[no_of_layer]->Wire.at(ii)), distance_between_straight_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
			
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

void HEX::calculate_relative_and_absolute_positions_inclined()
{
	if(fit_with_inclined)
	{
		unsigned int no_of_hits_in_layer;
		double x_prim, z_prim;
		double x, z;
		int straight_layers[4];
		straight_layers[0] =1;
		straight_layers[1] =2;
		straight_layers[2] =4;
		straight_layers[3] =5;
		
		int no_of_layer;
	
		// CALCULATIONS FOR THE --inclined-- LAYERS
		for (int i = 0; i < 4; i++)
		{
			no_of_layer = straight_layers[i];
			no_of_hits_in_layer = Layer[no_of_layer] -> Wire.size();
			//std::cout << layer_wire_frame_offset[no_of_layer] << std::endl;
			
			// CALCULATION OF POSITIONS IN THE DETECTOR
			// Z COORDINATE
			// calculate_position_in_detector(double element_no, double element_width, double offset_in_detector)
			z = calc_position_in_detector(no_of_layer, distance_between_layers, - half_z_dim + distance_to_1st_layer);
			Layer[no_of_layer]->RelativeZPosition = z;
			
			// X COORDINATE
			for (unsigned int ii = 0; ii < no_of_hits_in_layer; ii++)
			{
				// change READING so that orientation of the x axis and direction of increasing of wires/elements were the same - 04.10.16
				//x = calc_position_in_detector(no_of_wires[no_of_layer]-(Layer[no_of_layer]->Wire.at(ii)), distance_between_inclined_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
				x = calc_position_in_detector((Layer[no_of_layer]->Wire.at(ii)), distance_between_inclined_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
				
				//if(i == 2 || i == 3) x = 2+calc_position_in_detector(41-(Layer[no_of_layer]->Wire.at(ii)), distance_between_straight_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
				Layer[no_of_layer]->RelativeXPosition.push_back(x);
		
				x = Layer[no_of_layer]->RelativeXPosition.back();
				z = Layer[no_of_layer]->RelativeZPosition;
				//std::cout << "1. " << z << std::endl;
				
				// CALCULATE POSITION IN THE LAB
				// MAKE ROTATION AROUND Y AXIS
				x_prim = get_x_after_rot_Y(x, z, y_rotation_angle);
				z_prim = get_z_after_rot_Y(x, z, y_rotation_angle);
				//std::cout << "2. " << z_prim << std::endl;
	
				// !!! MAKE ROTATION AROUND X AXIS
	
				// calc_position_in_lab(double position_in_detector, double detector_position, double detector_offset)
				x = calc_position_in_lab(x_prim, x_lab_position, x_offset);
				z = calc_position_in_lab(z_prim, z_lab_position, z_offset);
				//std::cout << "3. " << z << std::endl;
	
				Layer[no_of_layer]->AbsoluteXPosition.push_back(x);
				Layer[no_of_layer]->AbsoluteZPosition.push_back(z);
			}
		}
		//std::cout << ".layer " << 1 << " z " << Layer[0]->AbsoluteZPosition.back()  << " x " << Layer[0]->AbsoluteXPosition.back() << std::endl;
		//std::cout << ".layer " << 2 << " z " << Layer[1]->AbsoluteZPosition.back()  << " x " << Layer[1]->AbsoluteXPosition.back() << std::endl;
		//std::cout << ".layer " << 3 << " z " << Layer[2]->AbsoluteZPosition.back()  << " x " << Layer[2]->AbsoluteXPosition.back() << std::endl;
		//std::cout << ".layer " << 4 << " z " << Layer[3]->AbsoluteZPosition.back()  << " x " << Layer[3]->AbsoluteXPosition.back() << std::endl;
		//std::cout << ".layer " << 5 << " z " << Layer[4]->AbsoluteZPosition.back()  << " x " << Layer[4]->AbsoluteXPosition.back() << std::endl;
		//std::cout << ".layer " << 6 << " z " << Layer[5]->AbsoluteZPosition.back()  << " x " << Layer[5]->AbsoluteXPosition.back() << std::endl;
	
	}
	
}

void HEX::collect_hits_from_all_layers()
{
	unsigned int no_of_entries; 

	int no_of_layer;
	for (int j = 0; j < 6; j++)
	{
		no_of_entries = Layer[ j ] -> AbsoluteXPosition.size();
		for (unsigned int i = 0; i < no_of_entries; i++)
		{
			// now positions of wires are plotted
			if (true)// there should be a condition which tells wheter a hit contributes to track or not - 04.10.16
			{
				AllWiresAbsolutePositionX.push_back(Layer[ j ] -> AbsoluteXPosition.at(i));
				AllHitsAbsolutePositionXEventDisplay.push_back( -(Layer[ j ] -> AbsoluteXPosition.at(i)) );
				AllWiresAbsolutePositionZ.push_back(Layer[ j ] -> AbsoluteZPosition.at(i));
				//std::cout << "layer " << j+1 << " z " << AllWiresAbsolutePositionZ.back()  << " x " << AllWiresAbsolutePositionX.back()<< std::endl;
			}
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

data_for_HEX_calibration HEX::get_data_for_calibration() // i need here only informations about wires and distances
{
	data_for_HEX_calibration data_for_calibration;
	for (int i = 0; i < 6; i++)
	{
		//std::cout << "layer " << i << " absolute x position " << Layer[i] -> AbsoluteXPosition.at(0) << std::endl;
		//std::cout << "layer " << i << " absolute z position " << Layer[i] -> AbsoluteZPosition.at(0) << std::endl;
		data_for_calibration.positionsX[i]	= Layer[i] -> AbsoluteXPosition.at(0);
		data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
		data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
		//std::cout << i+1 << " " << Layer[i] -> AbsoluteXPosition.at(0) << " " << Layer[i] -> AbsoluteZPosition.at(0) << " " << Layer[i] -> DriftTime.at(0) << std::endl;
	}
	return data_for_calibration;
}