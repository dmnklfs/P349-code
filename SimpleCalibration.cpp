#include "SimpleCalibration.h"

SimpleCalibration::SimpleCalibration()
{ 
	std::cout << "Warning: You are probably trying to run a Simple Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the SimpleCalibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;
}

SimpleCalibration::SimpleCalibration(const Config &_config)
{
	// calibration
	InitialDriftTimes 	= _config.D1_L1_calibration_times;
	InitialDistances 	= _config.D1_L1_calibration_distances;

	// from config
	no_of_iterations = _config.no_of_iterations_in_simple_calibration; 
	no_of_calib_bins = InitialDriftTimes.size()-1;
	no_of_corr_bins = _config.no_of_bins_in_simple_calibration-1;
	max_time_range =  _config.D1_drift_time_max[0];
	calib_bin_width = max_time_range/no_of_calib_bins;
	corr_bin_width = max_time_range/no_of_corr_bins;

	std::cout << "* simple calibration of the D1 will be done" << std::endl;
	std::cout << "	- number of iterations: " << no_of_iterations << std::endl;
	std::cout << "	WARNING: You are probably trying to run a Simple Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the SimpleCalibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;

	chi2 = new TH1F("#chi^{2}", "#chi^{2}", 400, -1, 5);
	chi2->GetXaxis()->SetTitle("#chi^{2}");
	chi2->GetYaxis()->SetTitle("counts");
	chi2->SetLineWidth(2);
	chi2->SetLineColor(kBlue);

	chi2_cut = new TH1F("#chi^{2} cut", "#chi^{2}", 400, -1, 5);
	chi2_cut->GetXaxis()->SetTitle("#chi^{2}");
	chi2_cut->GetYaxis()->SetTitle("counts");
	chi2_cut->SetLineColor(kRed);

	delta = new TH2F("#Delta", "#Delta", no_of_corr_bins, 0, 610, 300, -2.0, 2.0);
	delta->GetXaxis()->SetTitle("time [ns]");
	delta->GetYaxis()->SetTitle("delta [cm]");

	delta_cut = new TH2F("#Delta cut", "#Delta (#chi^{2} cut)", no_of_corr_bins, 0, 610, 300, -2.0, 2.0);
	delta_cut->GetXaxis()->SetTitle("time [ns]");
	delta_cut->GetYaxis()->SetTitle("delta [cm]");
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

	data.layer[0] = 0;
	data.layer[1] = 1;
	data.layer[2] = 6;
	data.layer[3] = 7;	
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

void SimpleCalibration::fit_events(double _chi2_cut)
{
	std::vector<double> results;
	double x, z, a, b, x_wire;
	double wire_track, wire_hit;
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		MinuitFit * fit = MinuitFit::GetInstance();
		fit -> MinuitFit::set_values(CalibrationData.at(i).hits_positionsX, CalibrationData.at(i).hits_positionsZ, CalibrationData.at(i).errors);
		results = fit -> MinuitFit::fit_with_minuit();

		if (!(fit -> err_flag()))
		{
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
				if (fabs(wire_hit) < fabs(wire_track)) CalibrationData.at(i).delta[j] = fabs(wire_track - wire_hit);
				if (fabs(wire_hit) > fabs(wire_track)) CalibrationData.at(i).delta[j] = -fabs(wire_track - wire_hit);
			}
		}
		//std::cout << wire_track - wire_hit << std::endl;
		results.clear();
		delete fit;
	}
	SimpleCalibration::fill_chi2(_chi2_cut);
	SimpleCalibration::fill_delta(_chi2_cut);
}

void SimpleCalibration::fill_chi2(double _chi2_cut)
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		if (-1!=CalibrationData.at(i).chi2)
		{
			chi2 -> Fill(CalibrationData.at(i).chi2);
			if (CalibrationData.at(i).chi2 < _chi2_cut) chi2_cut -> Fill(CalibrationData.at(i).chi2);
		}
	}
}

void SimpleCalibration::fill_delta(double _chi2_cut)
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (-1!=CalibrationData.at(i).delta[j])
			{
				delta -> Fill(CalibrationData.at(i).drift_times[j], CalibrationData.at(i).delta[j]);
				if (CalibrationData.at(i).chi2 < _chi2_cut) delta_cut -> Fill(CalibrationData.at(i).drift_times[j], CalibrationData.at(i).delta[j]);
			}
		}
	}
}

void SimpleCalibration::set_fit_errors()
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CalibrationData.at(i).errors[j] = ProjectionSigma.at( floor(CalibrationData.at(i).drift_times[j])/corr_bin_width );
		}
	}
}


TCanvas* SimpleCalibration::plot_chi2()
{
	TCanvas *c = new TCanvas("chi2","chi2");
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	chi2 -> Draw();
	chi2_cut -> Draw("same");
	return c;
}

TCanvas* SimpleCalibration::plot_delta()
{
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	TCanvas *c = new TCanvas("c_delta","c_delta");
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogz();
	delta -> Draw("colz");
	return c;
	// delete c;
}

TCanvas* SimpleCalibration::plot_delta_cut()
{
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	TCanvas *c = new TCanvas("c_delta_cut","c_delta_cut");
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogz();
	delta_cut -> Draw("colz");
	return c;
	// delete c;
}

TCanvas* SimpleCalibration::plot_current_calibration()
{
	TGraph* current_calibration;
	current_calibration = new TGraph(InitialDriftTimes.size(), &InitialDriftTimes.at(0), &InitialDistances.at(0));
	TCanvas *c_current_calibration = new TCanvas("c_current_calibration","c_current_calibration");
	current_calibration -> Draw("AL");
   	current_calibration->SetMinimum(0);
   	current_calibration->SetMaximum(2.5);
	return c_current_calibration;
	

}

void SimpleCalibration::fit_delta_projections(const char* folder_name)
{
	ProjectionConstant.clear();
	ProjectionMean.clear();
	ProjectionSigma.clear();
	// create directory for results
	boost::filesystem::create_directories(folder_name);
	TString ProjectionName;
	TH1D *delta_projection;
	int no_of_entries_in_projection;
	TCanvas *c_delta_projection;
	TF1 *gaussian = new TF1("gaussian","gaus", -1.5, 1.5);
	double hist_center, hist_sigma;
	for (int i = 0; i < no_of_corr_bins; i++) // there was no_of_corr_bins + 1
	{
		delta_projection = delta_cut -> ProjectionY("",i,i+1);
		no_of_entries_in_projection = delta_projection -> GetEntries();
		hist_center = delta_projection -> GetMean();
		hist_sigma = delta_projection -> GetRMS();

		ProjectionName = Form("projection_%d",i);
		c_delta_projection = new TCanvas(ProjectionName);
		gStyle->SetStatW(0.15);
		gStyle->SetStatH(0.1);
		gStyle->SetStatX(0.4);   
		gStyle->SetStatY(0.9);             
		ProjectionName = Form(folder_name + TString("projection_%d.png"),i);
		delta_projection -> Draw();
		if (no_of_entries_in_projection > 10)
		{
			gaussian -> SetParameters(delta_projection -> GetMaximum(), 0, 0.1);
			delta_projection->Fit("gaussian","","",hist_center-hist_sigma,hist_center+hist_sigma);
			ProjectionConstant.push_back(gaussian->GetParameter(0));
    		ProjectionMean.push_back(gaussian->GetParameter(1));
    		ProjectionSigma.push_back(0.5*gaussian->GetParameter(2));

    		gStyle->SetOptFit(1111);
			gPad->Modified();
		}
		else
		{
			ProjectionConstant.push_back(-1);
			ProjectionMean.push_back(-1);
			ProjectionSigma.push_back(-1);
		}
		c_delta_projection -> SaveAs(ProjectionName);
		delete c_delta_projection;
	}
	delete gaussian;
}

void SimpleCalibration::apply_corrections()
{
	//if (InitialDistances.size()!=ProjectionMean.size()) std::cout << "ERROR in SimpleCalibration::apply_corrections(): incorrect sizes!!!" << std::endl;
	int calib_bin;
	for (unsigned int i = 0; i < InitialDistances.size(); i++)
	{
		calib_bin = floor(InitialDriftTimes.at(i)/corr_bin_width);
		std::cout << "calib bin: " << calib_bin << std::endl;
		std::cout << "before: " << InitialDistances.at(i) << std::endl;
		std::cout << "proj value " << ProjectionMean.at(calib_bin) << std::endl;
		if(-1!=ProjectionMean.at(calib_bin)) InitialDistances.at(i) = InitialDistances.at(i) + ProjectionMean.at(calib_bin);
		std::cout << "after: " << InitialDistances.at(i) << std::endl;
		//if (InitialDistances.at(i) > 2) InitialDistances.at(i) = 2;
		if (InitialDistances.at(i) < 0) InitialDistances.at(i) = 0;
	}	
}

void SimpleCalibration::deletations()
{
	ProjectionConstant.clear();
	ProjectionSigma.clear();
	ProjectionMean.clear();
	chi2 -> Reset();
	chi2_cut -> Reset();
	delta -> Reset();
	delta_cut -> Reset();
}

void SimpleCalibration::recalculate_positions()
{
	for (unsigned int i = 0; i < CalibrationData.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CalibrationData.at(i).hits_positionsX[j] = CalibrationData.at(i).wires_positionsX[j]+(CalibrationData.at(i).left_right[j])*drift_time_to_distance(CalibrationData.at(i).drift_times[j]);
		}
	}
}

