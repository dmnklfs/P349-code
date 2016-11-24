#include "Calibration.h"

Calibration::Calibration()
{ 
	std::cout << "Warning: You are probably trying to run a Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the Calibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;
}

Calibration::Calibration(const Config &_config)
{
	
	no_of_iterations = _config.no_of_iterations_in_simple_calibration; 
	no_of_calib_bins = 201-1;
	no_of_corr_bins = _config.no_of_bins_in_simple_calibration-1;
	max_time_range =  _config.D1_drift_time_max[0];
	calib_bin_width = max_time_range/no_of_calib_bins;
	corr_bin_width = max_time_range/no_of_corr_bins;

	std::cout << "* simple calibration of the D1 will be done" << std::endl;
	std::cout << "	- number of iterations: " << no_of_iterations << std::endl;
	std::cout << "	WARNING: You are probably trying to run a Simple Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the Calibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;

	// initialization of the layers
	Layer[0] = new CalibrationLayer(1, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances);
	Layer[1] = new CalibrationLayer(2, _config.D1_L2_calibration_times, _config.D1_L2_calibration_distances);
	Layer[6] = new CalibrationLayer(7, _config.D1_L7_calibration_times, _config.D1_L7_calibration_distances);
	Layer[7] = new CalibrationLayer(8, _config.D1_L8_calibration_times, _config.D1_L8_calibration_distances);
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::set_no_of_corr_bins(corr_bin_width);
			Layer[i] -> CalibrationLayer::set_max_time_range(max_time_range);
		}
		else 
		{
			// layers with inclined wires *somehow* initialized - for now, 24.11.2016
			Layer[i] = new CalibrationLayer(i+1, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances);
			Layer[i] -> CalibrationLayer::set_no_of_corr_bins(corr_bin_width);
			Layer[i] -> CalibrationLayer::set_max_time_range(max_time_range);
		}
	}
}

Calibration::~Calibration()
{

}

void Calibration::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	std::cout << no_of_chosen_events << std::endl;
}

void Calibration::get_data(data_for_D1_calibration _single_event_data)
{
	double wirepos1[4], wirepos2[4];
	int left_right[8];
	for (int i = 0; i < 4; i++)
	{
		wirepos1[i] = _single_event_data.positionsX[i];
		wirepos2[i] = _single_event_data.positionsX[i+1];
		if (wirepos1 > wirepos2)
		{
			left_right[i] 		= -1;
			left_right[i+1] 	= +1;
		}
		else
		{
			left_right[i] 		= +1;
			left_right[i+1] 	= -1;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::get_data(_single_event_data.positionsX[i], _single_event_data.positionsZ[i], _single_event_data.drift_times[i], left_right[i]);
		}
		else 
		{
			// layers with inclined wires *somehow* initialized - for now, 24.11.2016
			Layer[i] -> CalibrationLayer::get_data(_single_event_data.positionsX[0], _single_event_data.positionsZ[0], _single_event_data.drift_times[0], left_right[0]);;
		}
	}
}

void Calibration::calculate_hit_position()
{
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::calculate_hit_position();
		}
	}
}

void Calibration::fill_histograms(double _chi2_cut)
{
	TString name;
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::fill_chi2(_chi2_cut);
			Layer[i] -> CalibrationLayer::fill_delta(_chi2_cut);
			name = Form("results/layer%d_chi2.png",i+1);
			Layer[i] -> CalibrationLayer::plot_chi2() -> SaveAs(name);
			name = Form("results/layer%d_delta.png",i+1);
			Layer[i] -> CalibrationLayer::plot_delta() -> SaveAs(name);
			name = Form("results/layer%d_delta_cut.png",i+1);
			Layer[i] -> CalibrationLayer::plot_delta_cut() -> SaveAs(name);			
		}
	}
}

void Calibration::fit_events_in_straight_layers()
{
	std::vector<double> results;
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	double hits_positionsX[4];
	double hits_positionsZ[4];
	double errors[4];
	int layers_numbers[4];
	layers_numbers[0] = 0;
	layers_numbers[1] = 1;
	layers_numbers[2] = 6;
	layers_numbers[3] = 7;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		// take the single event data
		for (int j = 0; j < 4; j++)
		{
			hits_positionsX[j] = Layer[layers_numbers[j]]->CalibrationData.at(i).hit_pos_X;
			hits_positionsZ[j] = Layer[layers_numbers[j]]->CalibrationData.at(i).hit_pos_Z;
			errors[j] = 1;
		}
		MinuitFit * fit = MinuitFit::GetInstance();		
		fit -> MinuitFit::set_values(hits_positionsX, hits_positionsZ, errors);
		results = fit -> MinuitFit::fit_with_minuit();

		if (!(fit -> err_flag()))
		{
			StraightLayersTracks_apar.push_back(results.at(0));
			StraightLayersTracks_bpar.push_back(results.at(1));
		}
		else // needed. StraightLayersTracks* have to have the same length as the CalibrationData in certain layers
		{
			StraightLayersTracks_apar.push_back(-1);
			StraightLayersTracks_bpar.push_back(-1);
		}
		results.clear();
		delete fit;
	}
}

void Calibration::set_values_of_track_projections_params()
{
	// there should be an additional step before: combination of informations from different angle-planes
	// into one 3d track and then projecting these parameters into the planes
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	int straight_layers_numbers[4];
	straight_layers_numbers[0] = 0;
	straight_layers_numbers[1] = 1;
	straight_layers_numbers[2] = 6;
	straight_layers_numbers[3] = 7;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Layer[straight_layers_numbers[j]] -> CalibrationData.at(i).track_a = StraightLayersTracks_apar.at(i);
			Layer[straight_layers_numbers[j]] -> CalibrationData.at(i).track_b = StraightLayersTracks_bpar.at(i);
		}
	}
}

void Calibration::deletations()
{
	for (int i = 0; i < 8; i++)
	{
		Layer[i] -> CalibrationLayer::deletations();
	}
	StraightLayersTracks_apar.clear();
	StraightLayersTracks_bpar.clear();
	InclinedLayersPlTracks_apar.clear();
	InclinedLayersPlTracks_bpar.clear();
	InclinedLayersMTracks_apar.clear();
	InclinedLayersMTracks_bpar.clear();
}