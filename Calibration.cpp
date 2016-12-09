#include "Calibration.h"

Calibration::Calibration()
{ 
	std::cout << "Warning: You are probably trying to run a Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the Calibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;
}

Calibration::Calibration(const Config &_config)
{
	
	no_of_iteration = 1; 
	no_of_calib_bins = 201-1;
	no_of_corr_bins = _config.no_of_bins_in_simple_calibration-1;
	max_time_range =  _config.D1_drift_time_max[0];
	calib_bin_width = max_time_range/no_of_calib_bins;
	corr_bin_width = max_time_range/no_of_corr_bins;
	track_angle_min = _config.track_angle_min;
	track_angle_max = _config.track_angle_max;

	std::cout << "* simple calibration of the D1 will be done" << std::endl;
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
			Layer[i] -> CalibrationLayer::set_no_of_bin_in_calib();
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
	chi2 = new TH1F(name, name, 400, -0.25, 3);
	chi2->GetXaxis()->SetTitle("#chi^{2}");
	chi2->GetYaxis()->SetTitle("counts");
	chi2->SetLineWidth(2);
	//chi2->SetLineColor(kBlue);

	name = Form("#chi^{2} cut", 1);
	chi2_cut = new TH1F(name, name, 400, -0.01, 0.1);
	chi2_cut->GetXaxis()->SetTitle("#chi^{2}");
	chi2_cut->GetYaxis()->SetTitle("counts");
	//chi2_cut->SetLineColor(kRed);

	//angle_distribution = new TH1F("track angles", "track angles", 2000, 72, 92);
	angle_distribution = new TH1F("track angles", "track angles", 2000, -10, 190);
	angle_distribution->GetXaxis()->SetTitle("track angle (deg)");
	angle_distribution->GetYaxis()->SetTitle("counts");
	//angle_distribution_no_cut = new TH1F("track angles no cut", "track angles no cut", 2000, 72, 92);
	angle_distribution_no_cut = new TH1F("track angles no cut", "track angles no cut", 2000, -10, 190);
	angle_distribution_no_cut->GetXaxis()->SetTitle("track angle (deg)");
	angle_distribution_no_cut->GetYaxis()->SetTitle("counts");
	angle_distribution_no_cut->SetLineColor(kRed);
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

void Calibration::set_no_of_iteration(double _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::set_no_of_iteration(_no_of_iteration);
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

void Calibration::set_no_of_bin_in_event()
{
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			Layer[i] -> CalibrationLayer::set_no_of_bin_in_event();
		}
	}
}

void Calibration::save_histograms()
{
	TString name;
	name = Form("results/chi2_iteration_%d.png",no_of_iteration);
	plot_chi2() -> SaveAs(name);
	name = Form("results/chi2_range_iteration_%d.png",no_of_iteration);
	plot_chi2_cut() -> SaveAs(name);
	name = Form("results/tracks_anglular_distribution_iteration_%d.png",no_of_iteration);
	plot_angle_distribution() -> SaveAs(name);
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			name = Form("results/layer%d_delta_iteration_%d.png",i+1, no_of_iteration);
			Layer[i] -> CalibrationLayer::plot_delta() -> SaveAs(name);	
		}
	}
}

void Calibration::fit_events_in_straight_layers(double _chi2_cut)
{
	std::vector<double> results;
	double hits_positionsX[4];
	double hits_positionsZ[4];
	double errors[4];
	int layers_numbers[4];
	layers_numbers[0] = 0;
	layers_numbers[1] = 1;
	layers_numbers[2] = 6;
	layers_numbers[3] = 7;

	double aSt, track_angle, bSt, chi2St;

	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		// take the single event data
		for (int j = 0; j < 4; j++)
		{
			hits_positionsX[j] = Layer[layers_numbers[j]]->CalibrationData.at(i).hit_pos_X;
			std::cout << hits_positionsX[j] << std::endl;
			hits_positionsZ[j] = Layer[layers_numbers[j]]->CalibrationData.at(i).hit_pos_Z;
			errors[j] = 1;
		}
		// fit for the straight layers
		MinuitFit * fit = MinuitFit::GetInstance();		
		fit -> MinuitFit::set_values(hits_positionsX, hits_positionsZ, errors);
		fit -> MinuitFit::perform_simplified_fit();
		results = fit -> MinuitFit::fit_with_minuit();
		if (!(fit -> err_flag()))
		{
			aSt = results.at(0);
			bSt = results.at(1);
			track_angle = TMath::ATan(aSt)*180*pow(3.14,-1);
			if (track_angle < 0) track_angle = 180+track_angle;
			chi2St = results.at(2);
			angle_distribution_no_cut -> Fill(track_angle);
			if ( was_correct_angle(track_angle) )
			{
				angle_distribution -> Fill(track_angle);
				chi2_cut -> Fill(chi2St);
				chi2 -> Fill(chi2St);
				// set values is straight layers
				for (int j = 0; j < 4; j++)
				{
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_a = aSt;
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_b = bSt;
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_angle = track_angle;
					Layer[layers_numbers[j]] -> calculate_deltas(i);
				}
			}
		}
		else // needed. StraightLayersTracks* have to have the same length as the CalibrationData in certain layers
		{
			aSt = -1;
			bSt = -1;
		}

		results.clear();
		delete fit;

		// there should be fit in inclined layers
		// there should be some 3d fitting
	}// end of loop over all calib events
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
	angle_distribution -> Reset();
	angle_distribution_no_cut -> Reset();
}

TCanvas* Calibration::plot_chi2()
{
	TString name;
	name = "c_#chi^{2}_1";
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	chi2 -> Draw();
	return c;
}

TCanvas* Calibration::plot_chi2_cut()
{
	TString name;
	name = "c_#chi^{2}_2";
	TCanvas *c2 = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	chi2_cut -> Draw();
	return c2;
}

void Calibration::fit_delta_projections()
{
	TString name;
	name = Form("results/DeltaProjections1_iteration_%d/",no_of_iteration);
	Layer[0] -> fit_delta_projections(name);
	name = Form("results/DeltaProjections2_iteration_%d/",no_of_iteration);
	Layer[1] -> fit_delta_projections(name);
	name = Form("results/DeltaProjections6_iteration_%d/",no_of_iteration);
	Layer[6] -> fit_delta_projections(name);
	name = Form("results/DeltaProjections7_iteration_%d/",no_of_iteration);
	Layer[7] -> fit_delta_projections(name);
}

void Calibration::apply_corrections()
{
	Layer[0] -> apply_corrections();
	Layer[1] -> apply_corrections();
	Layer[6] -> apply_corrections();
	Layer[7] -> apply_corrections();
}

void Calibration::plot_current_calibration()
{
	TString name;
	name = Form("results/layer1_calibration_iteration_%d.png",no_of_iteration);
	Layer[0] -> plot_current_calibration() -> SaveAs(name);
	name = Form("results/layer2_calibration_iteration_%d.png",no_of_iteration);
	Layer[1] -> plot_current_calibration() -> SaveAs(name);
	name = Form("results/layer7_calibration_iteration_%d.png",no_of_iteration);
	Layer[6] -> plot_current_calibration() -> SaveAs(name);
	name = Form("results/layer8_calibration_iteration_%d.png",no_of_iteration);
	Layer[7] -> plot_current_calibration() -> SaveAs(name);
}

TCanvas* Calibration::Calibration::plot_angle_distribution()
{
	TString name;
	name = Form("Track angles distribution iteration %d", no_of_iteration);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.4);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gPad -> SetLogy();
	angle_distribution_no_cut -> Draw();
	angle_distribution -> Draw("same");
	return c;
}

bool Calibration::was_correct_angle(double track_angle)
{
	if (track_angle > track_angle_min && track_angle < track_angle_max) return true;
	else return false;
}