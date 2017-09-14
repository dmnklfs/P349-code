#include "Calibration3d_HEX.h"

Calibration3d_HEX::Calibration3d_HEX()
{ 
	std::cout << "Warning: You are probably trying to run a Calibration metod. Note that it requires strict conditions on the number of events in the straight layers of the HEX. In case of the problems: check the config/remove this objects/adjust methods of the Calibration class/check event selection criteria in the SingleEvent class. Note that the postion in HEX should be calculated FOR WIRES (now)." << std::endl;
}

Calibration3d_HEX::Calibration3d_HEX(const Config &_config)
{
	fit_with_inclined = _config.fit_with_inclined;
	unbiased_fit = false;//_config.unbiased_fit;
	// for drawing
	half_x_dim = _config.HEX_half_x_dim;
	half_z_dim = _config.HEX_half_z_dim;
	x_lab_position = _config.HEX_x_lab_position;
	z_lab_position = _config.HEX_z_lab_position;
	distance_to_1st_layer = _config.HEX_distance_to_1st_layer;
	
	no_of_iteration = 1; 
	no_of_calib_bins = _config.HEX_L1_calibration_times.size()-1;
	no_of_corr_bins = no_of_calib_bins;
	max_time_range =  _config.HEX_drift_time_max[0];
	calib_bin_width = max_time_range/no_of_calib_bins;
	corr_bin_width = max_time_range/no_of_corr_bins;
	track_angle_min = _config.track_angle_min;
	track_angle_max = _config.track_angle_max;

	std::cout << "* calibration of the HEX DC will be done (with 3d fit)" << std::endl;
	std::cout << "	WARNING: it requires strict conditions on the number of events in all layers of the HEX" << std::endl;

	// init independent from fit_with_inclined
	// initialization of the layers
	Layer[0] = new CalibrationLayer3d_HEX(1, _config.HEX_L1_calibration_times, _config.HEX_L1_calibration_distances);
	Layer[1] = new CalibrationLayer3d_HEX(2, _config.HEX_L2_calibration_times, _config.HEX_L2_calibration_distances);
	Layer[2] = new CalibrationLayer3d_HEX(3, _config.HEX_L3_calibration_times, _config.HEX_L3_calibration_distances);
	Layer[3] = new CalibrationLayer3d_HEX(4, _config.HEX_L4_calibration_times, _config.HEX_L4_calibration_distances);
	Layer[4] = new CalibrationLayer3d_HEX(5, _config.HEX_L5_calibration_times, _config.HEX_L5_calibration_distances);
	Layer[5] = new CalibrationLayer3d_HEX(6, _config.HEX_L6_calibration_times, _config.HEX_L6_calibration_distances);
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> CalibrationLayer3d_HEX::set_no_of_corr_bins(no_of_corr_bins);
		Layer[i] -> CalibrationLayer3d_HEX::set_max_time_range(max_time_range);
		Layer[i] -> CalibrationLayer3d_HEX::set_no_of_bin_in_calib();
	}

	TString name;
	name = Form("#chi^{2}",1);
	chi2 = new TH1F(name, name, 80, -0.25, 8);//80, -0.25, 8);//1000, -0.01, 0.05);  250, -0.25, 25
	chi2->GetXaxis()->SetTitle("#chi^{2}");
	chi2->GetYaxis()->SetTitle("counts");
	chi2->SetLineWidth(2);
	//chi2->SetLineColor(kBlue);

	name = Form("#phi_{xz}",1);
	phi_xz = new TH1F(name, name, 2000, -10, 190);
	phi_xz->GetXaxis()->SetTitle("#phi_{xz} (deg)");
	phi_xz->GetYaxis()->SetTitle("counts");

	name = Form("#theta_{y}",1);
	theta_y = new TH1F(name, name, 2000, -10, 190);
	theta_y->GetXaxis()->SetTitle("#theta_{y} (deg)");
	theta_y->GetYaxis()->SetTitle("counts");

	name = Form("#chi^{2} cut", 1);
	chi2_no_cut = new TH1F(name, name, 80, -0.25, 8);
	chi2_no_cut->GetXaxis()->SetTitle("#chi^{2}");
	chi2_no_cut->GetYaxis()->SetTitle("counts");
	chi2_no_cut->SetLineColor(kRed);

	name = Form("#chi^{2} PDF", 1);
	chi2_pdf = new TH1F(name, name, 100, -0.1, 1.1);
	chi2_pdf->GetXaxis()->SetTitle("probability");
	chi2_pdf->GetYaxis()->SetTitle("counts");

	name = Form("#chi^{2} PDF cut", 1);
	chi2_pdf_no_cut = new TH1F(name, name, 100, -0.1, 1.1);
	chi2_pdf_no_cut->GetXaxis()->SetTitle("probability");
	chi2_pdf_no_cut->GetYaxis()->SetTitle("counts");
	chi2_pdf_no_cut->SetLineColor(kRed);

	name = "track angles";
	angle_distribution = new TH1F(name, name, 2000, -10, 190);
	angle_distribution->GetXaxis()->SetTitle("track angle (deg)");
	angle_distribution->GetYaxis()->SetTitle("counts");
	angle_distribution->SetLineColor(kBlue);
		
	name = "track angles no cut";
	angle_distribution_no_cut = new TH1F(name, name, 2000, -10, 190);
	angle_distribution_no_cut->GetXaxis()->SetTitle("track angle (deg)");
	angle_distribution_no_cut->GetYaxis()->SetTitle("counts");
	angle_distribution_no_cut->SetLineColor(kRed);

	for (int i = 0; i < 6; i++)
	{
		name = Form("layer %d track angles",i+1);
		layer_angle_distribution[i] = new TH1F(name, name, 2000, -10, 190);
		layer_angle_distribution[i]->GetXaxis()->SetTitle("track angle (deg)");
		layer_angle_distribution[i]->GetYaxis()->SetTitle("counts");
		layer_angle_distribution[i]->SetLineColor(kBlue);
		
		name = Form("layer %d track angles no cut",i+1);
		layer_angle_distribution_no_cut[i] = new TH1F(name, name, 2000, -10, 190);
		layer_angle_distribution_no_cut[i]->GetXaxis()->SetTitle("track angle (deg)");
		layer_angle_distribution_no_cut[i]->GetYaxis()->SetTitle("counts");
		layer_angle_distribution_no_cut[i]->SetLineColor(kRed);

		name = Form("layer %d #chi^{2}",i+1);
		layer_chi2[i] = new TH1F(name, name, 80, -0.25, 8);//1000, -0.01, 0.05);
		layer_chi2[i]->GetXaxis()->SetTitle("#chi^{2}");
		layer_chi2[i]->GetYaxis()->SetTitle("counts");
		layer_chi2[i]->SetLineWidth(2);
		//chi2->SetLineColor(kBlue);

		name = Form("layer %d #phi_{xz}",i+1);
		layer_phi_xz[i] = new TH1F(name, name, 2000, -10, 190);
		layer_phi_xz[i]->GetXaxis()->SetTitle("#phi_{xz} (deg)");
		layer_phi_xz[i]->GetYaxis()->SetTitle("counts");

		name = Form("layer %d #theta_{y}",i+1);
		layer_theta_y[i] = new TH1F(name, name, 2000, -10, 190);
		layer_theta_y[i]->GetXaxis()->SetTitle("#theta_{y} (deg)");
		layer_theta_y[i]->GetYaxis()->SetTitle("counts");

		name = Form("layer %d #chi^{2} cut", i+1);
		layer_chi2_no_cut[i] = new TH1F(name, name, 80, -0.25, 8);
		layer_chi2_no_cut[i]->GetXaxis()->SetTitle("#chi^{2}");
		layer_chi2_no_cut[i]->GetYaxis()->SetTitle("counts");
		layer_chi2_no_cut[i]->SetLineColor(kRed);

		name = Form("layer %d #chi^{2} PDF",i+1);
		layer_chi2_pdf[i] = new TH1F(name, name, 100, -0.1, 1.1);
		layer_chi2_pdf[i]->GetXaxis()->SetTitle("probability");
		layer_chi2_pdf[i]->GetYaxis()->SetTitle("counts");

		name = Form("layer %d #chi^{2} PDF cut",i+1);
		layer_chi2_pdf_no_cut[i] = new TH1F(name, name, 100, -0.1, 1.1);
		layer_chi2_pdf_no_cut[i]->GetXaxis()->SetTitle("probability");
		layer_chi2_pdf_no_cut[i]->GetYaxis()->SetTitle("counts");
		layer_chi2_pdf_no_cut[i]->SetLineColor(kRed);
	}
}

Calibration3d_HEX::~Calibration3d_HEX()
{

}

void Calibration3d_HEX::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	std::cout << "NO OF EVENTS FOR CALIBRATION (in each layer): " << no_of_chosen_events << std::endl;
}

void Calibration3d_HEX::get_data(data_for_HEX_calibration _single_event_data)
{
	double wirepos1, wirepos2;
	int left_right[6];
	int layer_pairs[6];
	layer_pairs[0] = 0;
	layer_pairs[1] = 3;
	layer_pairs[2] = 1;
	layer_pairs[3] = 2;
	layer_pairs[4] = 4;
	layer_pairs[5] = 5;
	for (int i = 0; i < 3; i++)
	{
		//std::cout << "pair " << i << std::endl;
		wirepos1 = _single_event_data.positionsX[layer_pairs[2*i]];
		//std::cout << layer_pairs[2*i] << " " << wirepos1 << std::endl;
		wirepos2 = _single_event_data.positionsX[layer_pairs[2*i+1]];
		//std::cout << layer_pairs[2*i+1] << " " << wirepos2 << std::endl;
		if (wirepos1 > wirepos2)
		{
			left_right[layer_pairs[2*i]]	= -1;
			left_right[layer_pairs[2*i+1]] 	= +1;
		}
		else
		{
			left_right[layer_pairs[2*i]] 	= +1;
			left_right[layer_pairs[2*i+1]] 	= -1;
		}
		//std::cout << left_right[layer_pairs[2*i]] << " " << left_right[layer_pairs[2*i+1]] << std::endl;
	}
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> CalibrationLayer3d_HEX::get_data(_single_event_data.positionsX[i], _single_event_data.positionsZ[i], _single_event_data.drift_times[i], left_right[i]);
	}
}

void Calibration3d_HEX::set_no_of_iteration(double _no_of_iteration)
{
	no_of_iteration = _no_of_iteration;
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> CalibrationLayer3d_HEX::set_no_of_iteration(_no_of_iteration);
	}
}

void Calibration3d_HEX::calculate_hit_position()
{
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> CalibrationLayer3d_HEX::calculate_hit_position();
	}
}

void Calibration3d_HEX::set_no_of_bin_in_event()
{
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> CalibrationLayer3d_HEX::set_no_of_bin_in_event();
	}
}

void Calibration3d_HEX::save_histograms()
{
	TString name;
	name = Form("results/chi2_iteration_%d.png",no_of_iteration);
	plot_chi2() -> SaveAs(name);
	name = Form("results/chi2_range_iteration_%d.png",no_of_iteration);
	plot_chi2_cut() -> SaveAs(name);
	name = Form("results/tracks_anglular_distribution_iteration_%d.png",no_of_iteration);
	plot_angle_distribution() -> SaveAs(name);
	name = Form("results/chi2_PDF_iteration_%d.png",no_of_iteration);
	plot_chi2_pdf() -> SaveAs(name);
	//name = Form("test_%d", event_no);
	//TFile test_file("results/file_calib.root","UPDATE");
	for (int i = 0; i < 6; i++)
	{
		name = Form("results/layer%d_delta_iteration_%d.png",i+1, no_of_iteration);
		Layer[i] -> CalibrationLayer3d_HEX::plot_delta() -> SaveAs(name);
		gDirectory->pwd();
		Layer[i] -> CalibrationLayer3d_HEX::plot_delta() -> Write();	
		name = Form("results/layer%d_chi2_iteration_%d.png",i+1, no_of_iteration);
		//plot_chi2(i) -> SaveAs(name);
		name = Form("results/layer%d_chi2_range_iteration_%d.png",i+1, no_of_iteration);
		plot_chi2_cut(i) -> SaveAs(name);
		name = Form("results/layer%d_tracks_anglular_distribution_iteration_%d.png",i+1, no_of_iteration);
		plot_angle_distribution(i) -> SaveAs(name);
		name = Form("results/layer%d_chi2_PDF_iteration_%d.png",i+1, no_of_iteration);
		plot_chi2_pdf(i) -> SaveAs(name);
	}
	//test_file.Close();
}

void Calibration3d_HEX::fit_events()
{
	fit_in_3d();
}

double Calibration3d_HEX::calculate_phi_xz()
{
	double phi_xz;
	// calculate vector projected onto xz plane
	double vx, vz, norm;
	vx = track3d_fit_vector.X();
	vz = track3d_fit_vector.Z();
	norm = pow(vx*vx+vz*vz,0.5);
	vx = vx*pow(norm,-1);
	vz = vz*pow(norm,-1);
	phi_xz = TMath::ACos(vx)*180*pow(3.14,-1);
	return phi_xz;
}

double Calibration3d_HEX::calculate_theta_y()
{
	double theta_y = 0;
	double vz, vy, norm;
	vz = track3d_fit_vector.Z();
	vy = track3d_fit_vector.Y();
	norm = pow(vz*vz+vy*vy,0.5);
	vz = vz*pow(norm,-1);
	vy = vy*pow(norm,-1);
	// calculate angle between Ox and vector
	theta_y = TMath::ACos(vy)*180*pow(3.14,-1);
	return theta_y;
}

void Calibration3d_HEX::fit_in_3d()
{
	double aSt, bSt, track_angle, temp_chi2, layer_temp_chi2[6], temp_chi2_prob, layer_temp_chi2_prob[6];
	double wires_positionsX_all[6];
	double hits_positionsX_all[6];
	double hits_positionsZ_all[6];
	double errors_all[6];
	unsigned int no_of_chosen_events;
	no_of_chosen_events = Layer[0] -> CalibrationData.size();
	std::cout << "Fit in 3d..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		//std::cout << Layer[0]->CalibrationData.at(i).wire_pos_X << std::endl;
		//std::cout << Layer[1]->CalibrationData.at(i).wire_pos_X << std::endl;
		//std::cout << "r " << Layer[0]->CalibrationData.at(i).wire_pos_X - Layer[1]->CalibrationData.at(i).wire_pos_X << std::endl;
		//std::cout << "ok " << std::endl;
		//std::cout << i << std::endl;
		for (int j = 0; j < 6; j++)
		{
			//std::cout << "   for fitting... " << std::endl;
			//std::cout << "   layer " << j << std::endl;
			wires_positionsX_all[j] = Layer[j]->CalibrationData.at(i).wire_pos_X;
			hits_positionsX_all[j] = Layer[j]->CalibrationData.at(i).hit_pos_X;
			hits_positionsZ_all[j] = Layer[j]->CalibrationData.at(i).hit_pos_Z;
			if (no_of_iteration==0) errors_all[j]=1;
			else errors_all[j] = Layer[j]->CalibrationData.at(i).hit_pos_Xerr;
			//std::cout << "   wires_positionsX_all[j] " << wires_positionsX_all[j] << std::endl;
			//std::cout << "   hits_positionsX_all[j] " << hits_positionsX_all[j] << std::endl;
			//std::cout << "   hits_positionsZ_all[j] " << hits_positionsZ_all[j] << std::endl;
			//std::cout << "   errors_all[j] " << errors_all[j] << std::endl;
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		Fit3d_HEX *fit3d_HEX = new Fit3d_HEX(i);
		fit3d_HEX -> Fit3d_HEX::set_no_of_iteration(no_of_iteration);
		fit3d_HEX -> Fit3d_HEX::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fit3d_HEX -> Fit3d_HEX::fit_straight_layer();
		fit3d_HEX -> Fit3d_HEX::fit_inclined_layers();
		fit3d_HEX -> Fit3d_HEX::calculate_xy_functions();
		fit3d_HEX -> Fit3d_HEX::set_hit_planes_vectors();
		fit3d_HEX -> Fit3d_HEX::calculate_normal_to_hit_planes();
		fit3d_HEX -> Fit3d_HEX::calculate_hit_planes_eq();
		fit3d_HEX -> Fit3d_HEX::calculate_intersection_vectors();
		fit3d_HEX -> Fit3d_HEX::calculate_intersection_points();
		fit3d_HEX -> Fit3d_HEX::calculate_3d_track_parameters();
		fit3d_HEX -> Fit3d_HEX::set_detector_position(x_lab_position, z_lab_position, half_x_dim, half_z_dim, distance_to_1st_layer);
		fit3d_HEX -> Fit3d_HEX::calculate_projections_on_hit_planes_calculations();

		fit3d_HEX -> Fit3d_HEX::make_fit_to_lines(unbiased_fit);
		fit3d_HEX -> Fit3d_HEX::calculate_projections_on_hit_planes_fit();
		track3d_fit_point = fit3d_HEX -> Fit3d_HEX::return_track_point();
		track3d_fit_vector = fit3d_HEX -> Fit3d_HEX::return_track_vector();
		fit3d_HEX -> Fit3d_HEX::calculate_wires_xy_functions();
		fit3d_HEX -> Fit3d_HEX::calculate_wire_track_distances();
		//fit3d_HEX -> Fit3d_HEX::draw_event();

		// cut on convergence of -- ALL ?? -- fits
		// cut on fit probability -- only for all layers
		if ((!(fit3d_HEX -> Fit3d_HEX::err_flag())))//&&((temp_chi2_prob>0.05)||no_of_iteration==0))
		{

			temp_chi2 = fit3d_HEX -> Fit3d_HEX::get_chisq();
			temp_chi2_prob = TMath::Prob(temp_chi2,2);
			//std::cout << "ok" << std::endl;
			// straight
			aSt = fit3d_HEX -> Fit3d_HEX::get_track_8lines_projection_params(0,0); // remove
			bSt = fit3d_HEX -> Fit3d_HEX::get_track_8lines_projection_params(0,1);

			// not from track projection - from calculate phi/theta
			track_angle = TMath::ATan(aSt)*180*pow(3.14,-1);
			if (track_angle < 0) track_angle = 180+track_angle;

			angle_distribution_no_cut -> Fill(track_angle);
			chi2_pdf_no_cut->Fill(temp_chi2_prob);
			chi2_no_cut->Fill(temp_chi2);

			// -------------------------------
			// | results from layers, no cut |
			// -------------------------------
			for (int j = 0; j < 6; j++)
			{
				layer_temp_chi2[j] = fit3d_HEX -> Fit3d_HEX::get_chisq(j);
				layer_temp_chi2_prob[j] = TMath::Prob(layer_temp_chi2[j],1);
				layer_angle_distribution_no_cut[j] -> Fill( fit3d_HEX -> Fit3d_HEX::calculate_phi_xz(j) );
				layer_chi2_pdf_no_cut[j] -> Fill(layer_temp_chi2_prob[j]);
				layer_chi2_no_cut[j] -> Fill(layer_temp_chi2[j]);
			}

			if ( was_correct_angle(track_angle) ) //was_correct_angle(track_angle) )
			{
				//std::cout << " ok 1" << std::endl;
				angle_distribution -> Fill(track_angle);
				chi2 -> Fill(temp_chi2);
				chi2_pdf -> Fill(temp_chi2_prob);
				phi_xz -> Fill(Calibration3d_HEX::calculate_phi_xz());
				theta_y -> Fill(Calibration3d_HEX::calculate_theta_y());

				for (int j = 0; j < 6; j++)
				{
					Layer[j] -> CalibrationData.at(i).track_A = aSt;
					Layer[j] -> CalibrationData.at(i).track_B = bSt;
					Layer[j] -> CalibrationData.at(i).track_C = bSt;
					Layer[j] -> CalibrationData.at(i).distance_wire_track = fit3d_HEX -> Fit3d_HEX::get_wire_track_dist(j);
					//std::cout << " c " << j << " " << Layer[j] -> CalibrationData.at(i).distance_wire_track << std::endl;
					Layer[j] -> CalibrationData.at(i).track_angle = track_angle;
					Layer[j] -> CalibrationLayer3d_HEX::calculate_deltas(i);
					layer_angle_distribution[j] -> Fill( fit3d_HEX -> Fit3d_HEX::calculate_phi_xz(j) );
					layer_chi2_pdf[j] -> Fill(layer_temp_chi2_prob[j]);
					layer_chi2[j] -> Fill(layer_temp_chi2[j]);
				}
			}
		}
		delete fit3d_HEX;
	}

}

void Calibration3d_HEX::deletations()
{
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> CalibrationLayer3d_HEX::deletations();
	}
	StraightLayersTracks_apar.clear();
	StraightLayersTracks_bpar.clear();
	InclinedLayersPlTracks_apar.clear();
	InclinedLayersPlTracks_bpar.clear();
	InclinedLayersMTracks_apar.clear();
	InclinedLayersMTracks_bpar.clear();
	Chi2.clear();
	chi2 -> Reset();
	chi2_no_cut -> Reset();
	chi2_pdf -> Reset();
	chi2_pdf_no_cut -> Reset();
	angle_distribution -> Reset();
	angle_distribution_no_cut -> Reset();
	for (int i = 0; i < 6; i++)
	{
		layer_angle_distribution[i] -> Reset();
		layer_angle_distribution_no_cut[i] -> Reset();
		layer_chi2[i] -> Reset();
		layer_chi2_no_cut[i] -> Reset();
		layer_chi2_pdf[i] -> Reset();
		layer_chi2_pdf_no_cut[i] -> Reset();
	}
	
}

TCanvas* Calibration3d_HEX::plot_chi2()
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

TCanvas* Calibration3d_HEX::plot_chi2_cut()
{
	TString name;
	name = "c_#chi^{2}_2";
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	chi2_no_cut -> Draw();
	chi2 -> Draw("same");
	return c;
}

TCanvas* Calibration3d_HEX::plot_chi2_cut(int _layer_no)
{
	TString name;
	name = Form("c_#chi^{2}_cut_layer%d", _layer_no);
	TCanvas *c = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	layer_chi2_no_cut[_layer_no] -> Draw();
	layer_chi2[_layer_no] -> Draw("same");
	return c;
}

TCanvas* Calibration3d_HEX::plot_chi2_pdf()
{
	TString name;
	name = "c_#chi^{2}_pdf";
	TCanvas *c2 = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	gPad->SetLogy();
	chi2_pdf_no_cut -> Draw();
	chi2_pdf -> Draw("same");
	return c2;
}

TCanvas* Calibration3d_HEX::plot_chi2_pdf(int _layer_no)
{
	TString name;
	name = Form("c_#chi^{2}_pdf_layer%d", _layer_no);
	TCanvas *c2 = new TCanvas(name,name);
	gStyle -> SetOptStat(1111111);
	gStyle->SetStatX(0.9);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	gPad->SetLogy();
	layer_chi2_pdf_no_cut[ _layer_no ] -> Draw();
	layer_chi2_pdf[ _layer_no ] -> Draw("same");
	return c2;
}

void Calibration3d_HEX::fit_delta_projections()
{
	TString name;
	for (int i = 0; i < 6; i++)
	{
		name = Form("results/DeltaProjections%d_iteration_%d/",i+1,no_of_iteration);
		Layer[i] -> fit_delta_projections(name);
	}
}

void Calibration3d_HEX::apply_corrections()
{
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> apply_corrections();
	}
}

void Calibration3d_HEX::set_pos_Xerr()
{
	for (int i = 0; i < 6; i++)
	{
		Layer[i] -> set_pos_Xerr();
	}
}
void Calibration3d_HEX::plot_current_calibration()
{
	TString name;
	for (int i = 0; i < 6; i++)
	{
		name = Form("results/layer%d_calibration_iteration_%d.png",i+1, no_of_iteration);
		Layer[i] -> plot_current_calibration() -> SaveAs(name);
		name = Form("results/layer%d_corrections_%d.png",i+1, no_of_iteration);
		Layer[i] -> plot_corrections() -> SaveAs(name);
	}
}

TCanvas* Calibration3d_HEX::plot_angle_distribution()
{
	TString name;
	name = Form("Track angles distribution iteration %d", no_of_iteration);
	TCanvas *c = new TCanvas(name,name,2000,500);
	c->Divide(3,1);
	c->cd(1);
	name = Form("Track angles distribution iteration %d", no_of_iteration);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.4);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	gStyle -> SetOptStat(1111111);
	//gPad -> SetLogy();
	angle_distribution_no_cut -> Draw();
	angle_distribution -> Draw("same");
	c->cd(2);
	//gPad -> SetLogy();
	phi_xz -> Draw();
	c->cd(3);
	//gPad -> SetLogy();
	theta_y -> Draw();

	gDirectory->pwd();
	if (no_of_iteration==9) phi_xz -> Write();
	if (no_of_iteration==9) theta_y -> Write();

	return c;
}

TCanvas* Calibration3d_HEX::plot_angle_distribution(int _layer_no)
{
	TString name;
	name = Form("Track angles distribution iteration %d layer %d", no_of_iteration, _layer_no);
	TCanvas *c = new TCanvas(name,name,2000,500);
	c->Divide(3,1);
	c->cd(1);
	name = Form("Track angles distribution iteration %d", no_of_iteration);
	gStyle->SetOptStat(0000000);		// tym mozna manipulowac przy rzutach (tylko tym?)
	gStyle->SetStatX(0.4);                
	gStyle->SetStatW(0.2);
	gStyle->SetStatH(0.1);
	gStyle->SetStatY(0.9);
	gStyle -> SetOptStat(1111111);
	//gPad -> SetLogy();
	layer_angle_distribution_no_cut[ _layer_no ] -> Draw();
	layer_angle_distribution[ _layer_no ] -> Draw("same");
	c->cd(2);
	//gPad -> SetLogy();
	phi_xz -> Draw();
	c->cd(3);
	//gPad -> SetLogy();
	theta_y -> Draw();
	return c;
}

bool Calibration3d_HEX::was_correct_angle(double track_angle)
{
	if (track_angle > track_angle_min && track_angle < track_angle_max) return true;
	else return false;
}