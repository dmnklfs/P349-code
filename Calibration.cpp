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

