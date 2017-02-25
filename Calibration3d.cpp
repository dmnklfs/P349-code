#include "Calibration3d.h"

Calibration3d::Calibration3d()
{ 
	std::cout << "Warning: You are probably trying to run a Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the D1. In case of the problems: check the config/remove this objects/adjust methods of the Calibration class/check event selection criteria in the SingleEvent class. Note that the postion in D1 should be calculated FOR WIRES (now)." << std::endl;
}

Calibration3d::Calibration3d(const Config &_config)
{
	fit_with_inclined = _config.fit_with_inclined;
	// for drawing
	half_x_dim = _config.D1_half_x_dim;
	half_z_dim = _config.D1_half_z_dim;
	x_lab_position = _config.D1_x_lab_position;
	z_lab_position = _config.D1_z_lab_position;
	distance_to_1st_layer = _config.D1_distance_to_1st_layer;
	
	no_of_iteration = 1; 
	no_of_calib_bins = _config.D1_L1_calibration_times.size()-1;
	no_of_corr_bins = no_of_calib_bins;
	max_time_range =  _config.D1_drift_time_max[0];
	calib_bin_width = max_time_range/no_of_calib_bins;
	corr_bin_width = max_time_range/no_of_corr_bins;
	track_angle_min = _config.track_angle_min;
	track_angle_max = _config.track_angle_max;

	std::cout << "* calibration of the D1 DC will be done (with 3d fit)" << std::endl;
	std::cout << "	WARNING: it requires strict conditions on the number of events in all layers of the D1" << std::endl;

	// init independent from fit_with_inclined
	// initialization of the layers
	Layer[0] = new CalibrationLayer3d(1, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances);
	Layer[1] = new CalibrationLayer3d(2, _config.D1_L2_calibration_times, _config.D1_L2_calibration_distances);
	Layer[2] = new CalibrationLayer3d(3, _config.D1_L3_calibration_times, _config.D1_L3_calibration_distances);
	Layer[3] = new CalibrationLayer3d(4, _config.D1_L4_calibration_times, _config.D1_L4_calibration_distances);
	Layer[4] = new CalibrationLayer3d(5, _config.D1_L5_calibration_times, _config.D1_L5_calibration_distances);
	Layer[5] = new CalibrationLayer3d(6, _config.D1_L6_calibration_times, _config.D1_L6_calibration_distances);
	Layer[6] = new CalibrationLayer3d(7, _config.D1_L7_calibration_times, _config.D1_L7_calibration_distances);
	Layer[7] = new CalibrationLayer3d(8, _config.D1_L8_calibration_times, _config.D1_L8_calibration_distances);
	for (int i = 0; i < 8; i++)
	{
		Layer[i] -> CalibrationLayer3d::set_no_of_corr_bins(no_of_corr_bins);
		Layer[i] -> CalibrationLayer3d::set_max_time_range(max_time_range);
		Layer[i] -> CalibrationLayer3d::set_no_of_bin_in_calib();
	}

	TString name;
	name = Form("#chi^{2}",1);
	chi2 = new TH1F(name, name, 2000, -0.25, 25);
	chi2->GetXaxis()->SetTitle("#chi^{2}");
	chi2->GetYaxis()->SetTitle("counts");
	chi2->SetLineWidth(2);
	//chi2->SetLineColor(kBlue);

	name = Form("#chi^{2} cut", 1);
	chi2_cut = new TH1F(name, name, 400, -0.01, 15);
	chi2_cut->GetXaxis()->SetTitle("#chi^{2}");
	chi2_cut->GetYaxis()->SetTitle("counts");
	//chi2_cut->SetLineColor(kRed);

	for (int i = 0; i < 4; i++)
	{
		name = Form("track angles layer %d",i+1);
		angle_distribution[i] = new TH1F(name, name, 2000, -10, 190);
		angle_distribution[i]->GetXaxis()->SetTitle("track angle (deg)");
		angle_distribution[i]->GetYaxis()->SetTitle("counts");
		angle_distribution[i]->SetLineColor(kBlue);
		
		name = Form("track angles no cut layer %d",i+1);
		angle_distribution_no_cut[i] = new TH1F(name, name, 2000, -10, 190);
		angle_distribution_no_cut[i]->GetXaxis()->SetTitle("track angle (deg)");
		angle_distribution_no_cut[i]->GetYaxis()->SetTitle("counts");
		angle_distribution_no_cut[i]->SetLineColor(kRed);
	}
}

Calibration3d::~Calibration3d()
{

}

void Calibration3d::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	std::cout << "NO OF EVENTS FOR CALIBRATION (in each layer): " << no_of_chosen_events << std::endl;
}

void Calibration3d::get_data(data_for_D1_calibration _single_event_data)
{
	double wirepos1, wirepos2;
	int left_right[8];
	for (int i = 0; i < 4; i++)
	{
		wirepos1 = _single_event_data.positionsX[2*i];
		wirepos2 = _single_event_data.positionsX[2*i+1];
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
		Layer[i] -> CalibrationLayer3d::get_data(_single_event_data.positionsX[i], _single_event_data.positionsZ[i], _single_event_data.drift_times[i], left_right[i]);
	}
}

void Calibration3d::set_no_of_iteration(double _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
	for (int i = 0; i < 8; i++)
	{
		Layer[i] -> CalibrationLayer3d::set_no_of_iteration(_no_of_iteration);
	}
}

void Calibration3d::calculate_hit_position()
{
	for (int i = 0; i < 8; i++)
	{
		Layer[i] -> CalibrationLayer3d::calculate_hit_position();
	}
}

void Calibration3d::set_no_of_bin_in_event()
{
	for (int i = 0; i < 8; i++)
	{
		Layer[i] -> CalibrationLayer3d::set_no_of_bin_in_event();
	}
}

void Calibration3d::save_histograms()
{
	TString name;
	name = Form("results/chi2_iteration_%d.png",no_of_iteration);
	plot_chi2() -> SaveAs(name);
	name = Form("results/chi2_range_iteration_%d.png",no_of_iteration);
	plot_chi2_cut() -> SaveAs(name);
	name = Form("results/tracks_anglular_distribution_iteration_%d.png",no_of_iteration);
	plot_angle_distribution() -> SaveAs(name);
	//name = Form("test_%d", event_no);
	TFile test_file("file_calib.root","UPDATE");
	for (int i = 0; i < 8; i++)
	{
		if (0==i||1==i||6==i||7==i)
		{
			name = Form("results/layer%d_delta_iteration_%d.png",i+1, no_of_iteration);
			Layer[i] -> CalibrationLayer3d::plot_delta() -> SaveAs(name);
			Layer[i] -> CalibrationLayer3d::plot_delta() -> Write();	
		}
	}
	test_file.Write();
}

void Calibration3d::fit_events()
{
	fit_in_3d();
}

void Calibration3d::fit_in_3d()
{
	int layers_numbers[4];
	layers_numbers[0] = 0;
	layers_numbers[1] = 1;
	layers_numbers[2] = 6;
	layers_numbers[3] = 7;

	double aSt, bSt, track_angle;
	double wires_positionsX_all[8];
	double hits_positionsX_all[8];
	double hits_positionsZ_all[8];
	double errors_all[8];
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	std::cout << "Fit in 3d..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		//std::cout << "ok " << std::endl;
		//std::cout << i << std::endl;
		for (int j = 0; j < 8; j++)
		{
			//std::cout << "layer " << j << std::endl;
			wires_positionsX_all[j] = Layer[j]->CalibrationData.at(i).wire_pos_X;
			hits_positionsX_all[j] = Layer[j]->CalibrationData.at(i).hit_pos_X;
			hits_positionsZ_all[j] = Layer[j]->CalibrationData.at(i).hit_pos_Z;
			errors_all[j] = Layer[j]->CalibrationData.at(i).hit_pos_Xerr;
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		Fit3d *fit3d = new Fit3d(i);
		fit3d -> Fit3d::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fit3d -> Fit3d::fit_straight_layer();
		fit3d -> Fit3d::fit_inclined_layers();
		fit3d -> Fit3d::calculate_xy_functions();
		fit3d -> Fit3d::set_hit_planes_vectors();
		fit3d -> Fit3d::calculate_normal_to_hit_planes();
		fit3d -> Fit3d::calculate_hit_planes_eq();
		fit3d -> Fit3d::calculate_intersection_vectors();
		fit3d -> Fit3d::calculate_intersection_points();
		fit3d -> Fit3d::calculate_3d_track_parameters();
		fit3d -> Fit3d::set_detector_position(x_lab_position, z_lab_position, half_x_dim, half_z_dim, distance_to_1st_layer);
		fit3d -> Fit3d::calculate_projections_on_hit_planes_calculations();

		fit3d -> Fit3d::make_fit_to_lines();
		fit3d -> Fit3d::calculate_projections_on_hit_planes_fit();
		track3d_fit_point = fit3d -> Fit3d::return_track_point();
		track3d_fit_vector = fit3d -> Fit3d::return_track_vector();
		fit3d -> Fit3d::calculate_wires_xy_functions();
		fit3d -> Fit3d::calculate_wire_track_distances();
		fit3d -> Fit3d::draw_event();


		if (!(fit3d -> Fit3d::err_flag()))
		{
			// straight
			aSt = fit3d -> Fit3d::get_track_8lines_projection_params(0,0);
			bSt = fit3d -> Fit3d::get_track_8lines_projection_params(0,1);
			//std::cout << " ok " << aSt << std::endl;
			track_angle = TMath::ATan(aSt)*180*pow(3.14,-1);
			if (track_angle < 0) track_angle = 180+track_angle;
			//chi2St = results.at(2);
			angle_distribution_no_cut[0] -> Fill(track_angle);
			if ( was_correct_angle(track_angle) )
			{
				angle_distribution[0] -> Fill(track_angle);
				//chi2_cut -> Fill(chi2St);
				//chi2 -> Fill(chi2St);
				// set values is straight layers
				for (int j = 0; j < 4; j++)
				{
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_A = aSt;
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_B = bSt;
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_C = bSt;
					Layer[layers_numbers[j]] -> CalibrationData.at(i).track_angle = track_angle;
					Layer[layers_numbers[j]] -> calculate_deltas(i);
				}
			}

			// inclined1
			aSt = fit3d -> Fit3d::get_track_8lines_projection_params(1,0);
			bSt = fit3d -> Fit3d::get_track_8lines_projection_params(1,1);
			track_angle = TMath::ATan(aSt)*180*pow(3.14,-1);
			if (track_angle < 0) track_angle = 180+track_angle;
			//chi2St = results.at(2);
			//angle_distribution_no_cut[0] -> Fill(track_angle);
			if ( was_correct_angle(track_angle) )
			{
				//angle_distribution[0] -> Fill(track_angle);
				//chi2_cut -> Fill(chi2St);
				//chi2 -> Fill(chi2St);
				// set values is straight layers
				for (int j = 0; j < 2; j++)
				{
					Layer[2+i] -> CalibrationData.at(i).track_angle = track_angle;
					Layer[2+i] -> calculate_deltas(i);
				}
			}

			// inclined2
			aSt = fit3d -> Fit3d::get_track_8lines_projection_params(2,0);
			bSt = fit3d -> Fit3d::get_track_8lines_projection_params(2,1);
			track_angle = TMath::ATan(aSt)*180*pow(3.14,-1);
			if (track_angle < 0) track_angle = 180+track_angle;
			//chi2St = results.at(2);
			//angle_distribution_no_cut[0] -> Fill(track_angle);
			if ( was_correct_angle(track_angle) )
			{
				//angle_distribution[0] -> Fill(track_angle);
				//chi2_cut -> Fill(chi2St);
				//chi2 -> Fill(chi2St);
				// set values is straight layers
				for (int j = 0; j < 2; j++)
				{
					Layer[4+i] -> CalibrationData.at(i).track_angle = track_angle;
					// set deltas, calculate deltas??
					Layer[4+i] -> calculate_deltas(i);
				}
			}
		}
		delete fit3d;
	}

}

void Calibration3d::deletations()
{
	for (int i = 0; i < 8; i++)
	{
		Layer[i] -> CalibrationLayer3d::deletations();
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
	for (int i = 0; i < 4; i++)
	{
		angle_distribution[i] -> Reset();
		angle_distribution_no_cut[i] -> Reset();
	}
	
}

TCanvas* Calibration3d::plot_chi2()
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

TCanvas* Calibration3d::plot_chi2_cut()
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

void Calibration3d::fit_delta_projections()
{
	TString name;
	name = Form("results/DeltaProjections1_iteration_%d/",no_of_iteration);
	Layer[0] -> fit_delta_projections(name);
	name = Form("results/DeltaProjections2_iteration_%d/",no_of_iteration);
	Layer[1] -> fit_delta_projections(name);
	name = Form("results/DeltaProjections7_iteration_%d/",no_of_iteration);
	Layer[6] -> fit_delta_projections(name);
	name = Form("results/DeltaProjections8_iteration_%d/",no_of_iteration);
	Layer[7] -> fit_delta_projections(name);
}

void Calibration3d::apply_corrections()
{
	Layer[0] -> apply_corrections();
	Layer[1] -> apply_corrections();
	Layer[6] -> apply_corrections();
	Layer[7] -> apply_corrections();
}

void Calibration3d::set_pos_Xerr()
{
	Layer[0] -> set_pos_Xerr();
	Layer[1] -> set_pos_Xerr();
	Layer[6] -> set_pos_Xerr();
	Layer[7] -> set_pos_Xerr();
}
void Calibration3d::plot_current_calibration()
{
	TString name;
	for (int i = 0; i < 8; i++)
	{
		if (i==0||i==1||i==6||i==7)
		{
			name = Form("results/layer%d_calibration_iteration_%d.png",i+1, no_of_iteration);
			Layer[i] -> plot_current_calibration() -> SaveAs(name);
		}
	}
}

TCanvas* Calibration3d::plot_angle_distribution()
{
	TString name;
	name = Form("Track angles distribution iteration %d", no_of_iteration);
	TCanvas *c = new TCanvas(name,name,2000,500);
	c->Divide(4,1);
	for (int i = 0; i < 4; i++)
	{
		c->cd(i+1);
		name = Form("Track angles distribution iteration %d", no_of_iteration);
		gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
		gStyle->SetStatX(0.4);                
		gStyle->SetStatW(0.2);
		gStyle->SetStatH(0.1);
		gStyle->SetStatY(0.9);
		gStyle -> SetOptStat(1111111);
		gPad -> SetLogy();
		angle_distribution_no_cut[i] -> Draw();
		angle_distribution[i] -> Draw("same");
	}
	return c;
}

bool Calibration3d::was_correct_angle(double track_angle)
{
	if (track_angle > track_angle_min && track_angle < track_angle_max) return true;
	else return false;
}