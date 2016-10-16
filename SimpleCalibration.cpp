#include "SimpleCalibration.h"

SimpleCalibration::SimpleCalibration()
{ 
	std::cout << "Warning: You are probably trying to run a Simple Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the SimpleCalibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;
}

SimpleCalibration::SimpleCalibration(const Config &_config)
{
	// calibration
	InitialDriftTimes 	= _config.D1_calibration_times;
	InitialDistances 	= _config.D1_calibration_distances;

	// from config
	no_of_iterations = _config.no_of_iterations_in_simple_calibration; 
	no_of_calib_bins = InitialDriftTimes.size()-1;
	no_of_corr_bins = _config.no_of_bins_in_simple_calibration;
	max_time_range =  _config.D1_drift_time_max[0];
	calib_bin_width = max_time_range/no_of_calib_bins;
	corr_bin_width = max_time_range/no_of_corr_bins;

	std::cout << "* simple calibration of the D1 will be done" << std::endl;
	std::cout << "	- number of iterations: " << no_of_iterations << std::endl;
	//std::cout << "	- number of time bins: " << no_of_bins << ", width of the bin: " << bin_width << " ns" << std::endl;
	std::cout << "	WARNING: You are probably trying to run a Simple Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the SimpleCalibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;
}


SimpleCalibration::~SimpleCalibration()
{  }

void SimpleCalibration::get_data(data_for_D1_simple_calibration _single_event_data)
{
	single_event_data data;
	for (int i = 0; i < 4; i++)
	{
		data.wires_positionsX[i] 	= _single_event_data.positionsX[i];
		data.wires_positionsZ[i] 	= _single_event_data.positionsZ[i];
		data.drift_times[i] = _single_event_data.drift_times[i];
		data.errors[i] = 1;
	}

	if (data.wires_positionsX[0] > data.wires_positionsX[1])
	{
		data.left_right[0] 	= -1;
		data.left_right[1] 	= +1;
	}
	else
	{
		data.left_right[0] 	= +1;
		data.left_right[1] 	= -1;
	}

	if (data.wires_positionsX[2] > data.wires_positionsX[3])
	{
		data.left_right[2] 	= -1;
		data.left_right[3] 	= +1;
	}
	else
	{
		data.left_right[2] 	= +1;
		data.left_right[3] 	= -1;
	}

	for (int i = 0; i < 4; i++)
	{
		data.hits_positionsX[i] = data.wires_positionsX[i]+(data.left_right[i])*drift_time_to_distance(data.drift_times[i]);
		data.hits_positionsZ[i] = data.wires_positionsZ[i];
		data.delta[i] = -1;
	}

	data.track_a = -1;
	data.track_b = -1;
	data.chi2 = -1;
	CalibrationData.push_back(data);
}

void SimpleCalibration::tell_no_of_events()
{
	std::cout << "* calibration will be done based on: " << CalibrationData.size() << " events" << std::endl;
}

// checked, works fine. move as a common function? - 16.10
double SimpleCalibration::drift_time_to_distance(double drift_time)
{
	double distance;
	int calib_bin = floor(drift_time/calib_bin_width);
	double t1 = InitialDriftTimes.at(calib_bin);
	double t2 = InitialDriftTimes.at(calib_bin+1);
	double x1 = InitialDistances.at(calib_bin);
	double x2 = InitialDistances.at(calib_bin+1);
	distance = InitialDistances.at(calib_bin) + (x2 - x1)*(drift_time - t1)/(t2 - t1);
	return distance;
}

void SimpleCalibration::SingleIteration(double _chi2_cut)
{
	std::vector<double> results;
	double x, z, a, b, x_wire;
	double wire_track, wire_hit;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		MinuitFit * fit = MinuitFit::GetInstance();
		fit -> MinuitFit::set_values(CalibrationData.at(i).hits_positionsX, CalibrationData.at(i).hits_positionsZ, CalibrationData.at(i).errors);
		results = fit -> MinuitFit::fit_with_minuit();
		CalibrationData.at(i).track_a = results.at(0);
		CalibrationData.at(i).track_b = results.at(1);
		CalibrationData.at(i).chi2 = results.at(2);

		a = CalibrationData.at(i).track_a;
		b = CalibrationData.at(i).track_b;
		for (int j = 0; j < 4; j++)
		{
			x = CalibrationData.at(i).hits_positionsX[j];
			z = CalibrationData.at(i).hits_positionsZ[j];
			x_wire = CalibrationData.at(i).wires_positionsX[j];
			wire_track = fabs((z - b)/a - x_wire);
			wire_hit = fabs( x - x_wire);
			if (wire_hit < wire_track) CalibrationData.at(i).delta[j] = fabs(wire_track - wire_hit);
			if (wire_hit > wire_track) CalibrationData.at(i).delta[j] = -fabs(wire_track - wire_hit);
		}
		std::cout << results.at(0) << " " << results.at(1) << " " << results.at(2) << std::endl;
		results.clear();
		delete fit;
	}
	SimpleCalibration::plot_chi2();
	SimpleCalibration::plot2d();
}

void SimpleCalibration::plot_chi2()
{
	TH1F *chi2hist = new TH1F("#chi^{2}", "#chi^{2}", 100, -1, 10);
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		chi2hist -> Fill(CalibrationData.at(i).chi2);
	}
	TCanvas *c = new TCanvas("c","c");
	gStyle -> SetOptStat(1111111);
	chi2hist -> Draw();
	c -> SaveAs("chi2.png");
}

void SimpleCalibration::plot2d()
{
	TH2F *Delta = new TH2F("#Delta", "#Delta", 200, 0, 300, 60, -3, 3);
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Delta -> Fill(CalibrationData.at(i).drift_times[j], CalibrationData.at(i).delta[j]);
		}
		
	}
	TCanvas *c = new TCanvas("c2","c2");
	gStyle -> SetOptStat(1111111);
	Delta -> Draw("colz");
	c -> SaveAs("delta.png");
}