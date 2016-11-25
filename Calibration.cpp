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
			Layer[i] -> CalibrationLayer::set_no_of_corr_bins(no_of_corr_bins);
			Layer[i] -> CalibrationLayer::set_max_time_range(max_time_range);
		}
		else 
		{
			// layers with inclined wires *somehow* initialized - for now, 24.11.2016
			Layer[i] = new CalibrationLayer(i+1, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances);
			Layer[i] -> CalibrationLayer::set_no_of_corr_bins(no_of_corr_bins);
			Layer[i] -> CalibrationLayer::set_max_time_range(max_time_range);
		}
	}
	TString name;
	name = Form("#chi^{2}",1);
	chi2 = new TH1F(name, name, 400, -1, 5);
	chi2->GetXaxis()->SetTitle("#chi^{2}");
	chi2->GetYaxis()->SetTitle("counts");
	chi2->SetLineWidth(2);
	chi2->SetLineColor(kBlue);

	name = Form("#chi^{2} cut", 1);
	chi2_cut = new TH1F(name, name, 400, -1, 5);
	chi2_cut->GetXaxis()->SetTitle("#chi^{2}");
	chi2_cut->GetYaxis()->SetTitle("counts");
	chi2_cut->SetLineColor(kRed);
}

Calibration::~Calibration()
{

}

void Calibration::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	std::cout << "NO OF EVENTS FOR CALIBRATION (in each layer): " << no_of_chosen_events << std::endl;
}

void Calibration::get_data(data_for_D1_calibration _single_event_data)
{
	double wirepos1, wirepos2;
	int left_right[8];
	wirepos1 = _single_event_data.positionsX[0];
	wirepos2 = _single_event_data.positionsX[1];
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
	wirepos1 = _single_event_data.positionsX[6];
	wirepos2 = _single_event_data.positionsX[7];
	if (wirepos1 > wirepos2)
	{
		left_right[6] 	= -1;
		left_right[7] 	= +1;
	}
	else
	{
		left_right[6] 	= +1;
		left_right[7] 	= -1;
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
	fill_chi2(_chi2_cut);
	name = Form("results/_chi2.png",1);
	plot_chi2() -> SaveAs(name);
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::fill_delta(_chi2_cut);
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
			Chi2.push_back(results.at(2));
		}
		else // needed. StraightLayersTracks* have to have the same length as the CalibrationData in certain layers
		{
			StraightLayersTracks_apar.push_back(-1);
			StraightLayersTracks_bpar.push_back(-1);
			Chi2.push_back(-1);
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

void Calibration::calculate_deltas()
{
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
			Layer[straight_layers_numbers[j]] -> calculate_deltas();
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
	Chi2.clear();
	chi2 -> Reset();
	chi2_cut -> Reset();
}

void Calibration::fill_chi2(double _chi2_cut)
{
	for (unsigned int i = 0; i < Chi2.size(); i++)
	{
		if (-1!=Chi2.at(i))
		{
			chi2 -> Fill(Chi2.at(i));
			if (Chi2.at(i) < _chi2_cut) chi2_cut -> Fill(Chi2.at(i));
		}
	}
}

TCanvas* Calibration::plot_chi2()
{
	TString name;
	name = "c_#chi^{2}";
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	chi2 -> Draw();
	chi2_cut -> Draw("same");
	return c;
}

void Calibration::fit_delta_projections()
{
	Layer[0] -> fit_delta_projections("results/DeltaProjections1/");
	Layer[1] -> fit_delta_projections("results/DeltaProjections2/");
	Layer[6] -> fit_delta_projections("results/DeltaProjections6/");
	Layer[7] -> fit_delta_projections("results/DeltaProjections7/");
}

void Calibration::apply_corrections()
{
	Layer[0] -> apply_corrections();
	Layer[1] -> apply_corrections();
	Layer[6] -> apply_corrections();
	Layer[7] -> apply_corrections();
}

TCanvas* Calibration::plot_current_calibration()
{
	Layer[0] -> plot_current_calibration() -> SaveAs("results/layer1_calibration.png");
	Layer[1] -> plot_current_calibration() -> SaveAs("results/layer2_calibration.png");
	Layer[6] -> plot_current_calibration() -> SaveAs("results/layer7_calibration.png");
	Layer[7] -> plot_current_calibration() -> SaveAs("results/layer8_calibration.png");
}