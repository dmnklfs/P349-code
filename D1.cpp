#include "D1.h"

D1::D1()
{ }

D1::D1(const Config &_config)
{
	// constructors of the layers: drift time offset, calib times, calib dists, time min, time max, hits min, hits max
	Layer[0] = new DCLayer(0, _config.D1_L1_drift_time_offset, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances, _config.D1_drift_time_min[0],_config.D1_drift_time_max[0],_config.D1_layer_min_hits[0],_config.D1_layer_max_hits[0]);
	Layer[1] = new DCLayer(1, _config.D1_L2_drift_time_offset, _config.D1_L2_calibration_times, _config.D1_L2_calibration_distances, _config.D1_drift_time_min[1],_config.D1_drift_time_max[1],_config.D1_layer_min_hits[1],_config.D1_layer_max_hits[1]);
	Layer[6] = new DCLayer(7, _config.D1_L7_drift_time_offset, _config.D1_L7_calibration_times, _config.D1_L7_calibration_distances, _config.D1_drift_time_min[6],_config.D1_drift_time_max[6],_config.D1_layer_min_hits[6],_config.D1_layer_max_hits[6]);
	Layer[7] = new DCLayer(8, _config.D1_L8_drift_time_offset, _config.D1_L8_calibration_times, _config.D1_L8_calibration_distances, _config.D1_drift_time_min[7],_config.D1_drift_time_max[7],_config.D1_layer_min_hits[7],_config.D1_layer_max_hits[7]);
	for (int i = 0; i < 8; i++)
	{
		// init for inclined wires
		if(2==i||3==i||4==i||5==i) Layer[i] = new DCLayer(i+1,_config.D2_drift_time_offset, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances, _config.D1_drift_time_min[i],_config.D1_drift_time_max[i],_config.D1_layer_min_hits[i],_config.D1_layer_max_hits[i]);
		// for all layers
		layer_wire_frame_offset[i] = _config.D1_layer_wire_frame_offset[i];
	}
	half_x_dim = _config.D1_half_x_dim;
	half_z_dim = _config.D1_half_z_dim;
	x_lab_position = _config.D1_x_lab_position;
	z_lab_position = _config.D1_z_lab_position;
	z_offset = _config.D1_z_offset;
	x_offset = _config.D1_x_offset;
	y_rotation_angle = _config.D1_y_rotation_angle;
	distance_to_1st_layer = _config.D1_distance_to_1st_layer;
	distance_between_wires = _config.D1_distance_between_wires;
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
	for (int i = 0; i < 8; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
	}
//	if (no_of_layers_with_hits == 8)
//	{
//		correct_event = true;
//	}

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

	int wire1;
	int wire2;
	int wire7;
	int wire8;
	if (correct_in_layer[0]&&correct_in_layer[1]&&correct_in_layer[6]&&correct_in_layer[7])
	{
		wire1 = Layer[0] -> DCLayer::Wire.at(0);
		wire2 = Layer[1] -> DCLayer::Wire.at(0);
		wire7 = Layer[6] -> DCLayer::Wire.at(0);
		wire8 = Layer[7] -> DCLayer::Wire.at(0);
		//std::cout << wire1 << " " << wire2 << " " << wire7 << " " << wire8 << std::endl;
		if (wire1==19&&wire7==19&&wire2==20&&wire8==20)//(wire2==wire1||wire2==wire1+1)&&(wire8==wire7||wire8==wire7+1)) // ||wire2==wire1+1 ||wire8==wire7+1
		{
			correct_event = true;
		}
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

int D1::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}

void D1::calculate_distances_from_wires()
{
	for (int j = 0; j < 8; j++)
	{
		if (j==0||j==1||j==6||j==7) Layer[j] -> DCLayer::calculate_distances_from_wires();
	}
}

void D1::calculate_relative_and_absolute_positions()
{
	//std::cout << "D1::calculate_relative_and_absolute_positions" << std::endl;
	unsigned int no_of_hits_in_layer;
	double x_prim, z_prim;
	double x, z;
	int straight_layers[4];
	straight_layers[0] =0;
	straight_layers[1] =1;
	straight_layers[2] =6;
	straight_layers[3] =7;
	
	int no_of_layer;

	// CALCULATIONS FOR THE STRAIGHT LAYERS
	for (int i = 0; i < 4; i++)
	{
		no_of_layer = straight_layers[i];
		no_of_hits_in_layer = Layer[no_of_layer] -> Wire.size();
		
		// CALCULATION OF POSITIONS IN THE DETECTOR
		// Z COORDINATE
		// calculate_position_in_detector(double element_no, double element_width, double offset_in_detector)
		z = calc_position_in_detector(no_of_layer, distance_between_layers, - half_z_dim + distance_to_1st_layer);
		Layer[no_of_layer]->RelativeZPosition = z;
		
		// X COORDINATE
		for (unsigned int ii = 0; ii < no_of_hits_in_layer; ii++)
		{
			// change READING so that orientation of the x axis and direction of increasing of wires/elements were the same - 04.10
			x = calc_position_in_detector(41-(Layer[no_of_layer]->Wire.at(ii)), distance_between_wires, -half_x_dim + layer_wire_frame_offset[no_of_layer]);
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
		}
	}
}

void D1::collect_hits_from_all_layers()
{
	// this function can be called somewhere else, not only in the event display class...
	// loop over all entries in the certain layer
	int straight_layers[4];
	straight_layers[0] =0;
	straight_layers[1] =1;
	straight_layers[2] =7;
	straight_layers[3] =6;
	unsigned int no_of_entries; 

	int no_of_layer;
	for (int j = 0; j < 4; j++)
	{
		no_of_layer = straight_layers[j];
		no_of_entries = Layer[ no_of_layer ] -> AbsoluteXPosition.size();
		for (unsigned int i = 0; i < no_of_entries; i++)
		{
			// now positions of wires are plotted
			if (true)// there should be a condition which tells wheter a hit contributes to track or not - 04.10
			{
				AllWiresAbsolutePositionX.push_back(Layer[ no_of_layer ] -> AbsoluteXPosition.at(i));
				AllHitsAbsolutePositionXEventDisplay.push_back( -(Layer[ no_of_layer ] -> AbsoluteXPosition.at(i)) );
				AllWiresAbsolutePositionZ.push_back(Layer[ no_of_layer ] -> AbsoluteZPosition.at(i));
			}
		}
	}	
}

// simple calculation --ONLY-- if there are single hits in all layers
TGraph* D1::plot_track_in_D1()
{
	double wirepos1, wirepos2; 
	int left_right[4];
	double pos_X[4], pos_Z[4], err[4];
	wirepos1 = Layer[0] -> AbsoluteXPosition.at(0);
	wirepos2 = Layer[1] -> AbsoluteXPosition.at(0); 
	if (wirepos1 > wirepos2)
	{
		left_right[0] 	= -1;
		left_right[1] 	= +1;
	}
	else
	{
		left_right[0] 	= +1;
		left_right[1] 	= -1;
	}
	pos_X[0] =wirepos1 + left_right[0]*(Layer[0] -> HitsDistancesFromWires.at(0));
	pos_X[1] =wirepos2 + left_right[1]*(Layer[1] -> HitsDistancesFromWires.at(0));

	wirepos1 = wirepos1 = Layer[6] -> AbsoluteXPosition.at(0);
	wirepos2 = wirepos2 = Layer[7] -> AbsoluteXPosition.at(0);
	if (wirepos1 > wirepos2)
	{
		left_right[2] 	= -1;
		left_right[3] 	= +1;
	}
	else
	{
		left_right[2] 	= +1;
		left_right[3] 	= -1;
	}
	pos_X[2] =wirepos1 + left_right[0]*(Layer[0] -> HitsDistancesFromWires.at(0));
	pos_X[3] =wirepos2 + left_right[1]*(Layer[1] -> HitsDistancesFromWires.at(0));
	// Z positions - for wires. --- what if there are rotations - check?? 28.12.16
	pos_Z[0] = Layer[0] -> AbsoluteZPosition.at(0);
	pos_Z[1] = Layer[1] -> AbsoluteZPosition.at(0);
	pos_Z[2] = Layer[6] -> AbsoluteZPosition.at(0);
	pos_Z[3] = Layer[7] -> AbsoluteZPosition.at(0);
	err[0] = 1;
	err[1] = 1;
	err[2] = 1;
	err[3] = 1;
	MinuitFit * fit = MinuitFit::GetInstance();		
	fit -> MinuitFit::set_values(pos_X, pos_Z, err);
	fit -> MinuitFit::perform_simplified_fit();
	std::vector<double> results;
	results = fit -> MinuitFit::fit_with_minuit();

	double a = -results.at(0);
	double b = results.at(1);
	TF1* fcn = new TF1("straight_track", "[0]*x+[1]", -100, 100);
	fcn -> SetParameter(0, a);
	fcn -> SetParameter(1, b);
	TGraph* track_plot = new TGraph(fcn);
	return track_plot;
}

void D1::set_hits_absolute_positions()
{
	double wirepos1, wirepos2; 
	int left_right[4];
	wirepos1 = Layer[0] -> AbsoluteXPosition.at(0);
	wirepos2 = Layer[1] -> AbsoluteXPosition.at(0); 
	if (wirepos1 > wirepos2)
	{
		left_right[0] 	= -1;
		left_right[1] 	= +1;
	}
	else
	{
		left_right[0] 	= +1;
		left_right[1] 	= -1;
	}
	AllHitsAbsolutePositionX.push_back(wirepos1 + left_right[0]*(Layer[0] -> HitsDistancesFromWires.at(0)));
	AllHitsAbsolutePositionX.push_back(wirepos2 + left_right[1]*(Layer[1] -> HitsDistancesFromWires.at(0)));

	wirepos1 = wirepos1 = Layer[6] -> AbsoluteXPosition.at(0);
	wirepos2 = wirepos2 = Layer[7] -> AbsoluteXPosition.at(0);
	if (wirepos1 > wirepos2)
	{
		left_right[2] 	= -1;
		left_right[3] 	= +1;
	}
	else
	{
		left_right[2] 	= +1;
		left_right[3] 	= -1;
	}
	AllHitsAbsolutePositionX.push_back(wirepos1 + left_right[0]*(Layer[6] -> HitsDistancesFromWires.at(0)));
	AllHitsAbsolutePositionX.push_back(wirepos2 + left_right[1]*(Layer[7] -> HitsDistancesFromWires.at(0)));
	// Z positions - for wires. --- what if there are rotations - check?? 28.12.16
	AllHitsAbsolutePositionZ.push_back(Layer[0] -> AbsoluteZPosition.at(0));
	AllHitsAbsolutePositionZ.push_back(Layer[1] -> AbsoluteZPosition.at(0));
	AllHitsAbsolutePositionZ.push_back(Layer[6] -> AbsoluteZPosition.at(0));
	AllHitsAbsolutePositionZ.push_back(Layer[7] -> AbsoluteZPosition.at(0));
}

bool D1::plot_event()
{
	bool plot_event = false;
	if (0!=AllHitsAbsolutePositionXEventDisplay.size()) plot_event = true;
	return plot_event;
} 

TGraph* D1::get_all_hits_plot()
{
	TGraph* all_hits = new TGraph(AllHitsAbsolutePositionXEventDisplay.size(), &AllHitsAbsolutePositionXEventDisplay.at(0), &AllWiresAbsolutePositionZ.at(0));
	all_hits ->  SetMarkerStyle(20);
	return all_hits;
}

TGraph* D1::get_detector_plot()
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
		data_for_calibration.positionsX[i]	= Layer[ straight_layers[i] ]->AbsoluteXPosition.at(0);
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
	int D1_layers[8];
	D1_layers[0] =0;
	D1_layers[1] =1;
	D1_layers[2] =6;
	D1_layers[3] =7;

	data_for_D1_calibration data_for_calibration;
	for (int i = 0; i < 8; i++)
	{
		//std::cout << i+1 << " wire: " << Layer[i] -> Wire.at(0) << std::endl;
		//std::cout << i+1 << " time: " << Layer[i] -> DriftTime.at(0) << std::endl;
		if (0==i||1==i||6==i||7==i)
		{
			data_for_calibration.positionsX[i]	= Layer[i] -> AbsoluteXPosition.at(0);
			data_for_calibration.positionsZ[i]	= Layer[i] -> AbsoluteZPosition.at(0);
			data_for_calibration.drift_times[i]	= Layer[i] -> DriftTime.at(0);
			//std::cout << i << ": " << Layer[i] -> AbsoluteXPosition.at(0) << std::endl;
			//std::cout << i << ": " << Layer[i] -> DriftTime.at(0)*2*pow(600,-1) << std::endl;
		}
		else
		{
			data_for_calibration.positionsX[i] = -1;
			data_for_calibration.positionsZ[i] = -1;
			data_for_calibration.drift_times[i] = -1;
		}
	}
	return data_for_calibration;
}

double D1::test_get_chosen_position(int _no_of_layer, int _add_in_layer)
{
	double res = (Layer[_no_of_layer]->AbsoluteXPosition.at(0)) + _add_in_layer*2*pow(600,-1)*(Layer[_no_of_layer] -> DriftTime.at(0));
	//std::cout << res << std::endl;
	return res;
}