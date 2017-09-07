#include "TrackReconstruction.h"

TrackReconstruction::TrackReconstruction() { }

TrackReconstruction::TrackReconstruction(const Config &_config)
{
	half_x_dim_D1 = _config.D1_half_x_dim;
	half_z_dim_D1 = _config.D1_half_z_dim;
	x_lab_position_D1 = _config.D1_x_lab_position;
	z_lab_position_D1 = _config.D1_z_lab_position;

	half_x_dim_D2 = _config.D2_half_x_dim;
	half_z_dim_D2 = _config.D2_half_z_dim;
	x_lab_position_D2 = _config.D2_x_lab_position;
	z_lab_position_D2 = _config.D2_z_lab_position;

	half_x_dim_HEX = _config.HEX_half_x_dim;
	half_z_dim_HEX = _config.HEX_half_z_dim;
	x_lab_position_HEX = _config.HEX_x_lab_position;
	z_lab_position_HEX = _config.HEX_z_lab_position;

	D1D2_phi_corr = new TH2F("D1D2_phi_corr","D1D2_phi_corr;D1_phi (deg);D2_phi (deg)", 200,75,105,200,75,105);
	D1HEX_phi_corr = new TH2F("D1HEX_phi_corr","D1HEX_phi_corr;D1_phi (deg);HEX_phi (deg)", 200,75,105,200,75,105);
	D1D2_theta_corr = new TH2F("D1D2_theta_corr","D1D2_theta_corr;D1_theta (deg);D2_theta (deg)", 200,75,105,200,75,105);
	D1_chisq = new TH1F("D1 #chi^{2}","D1 #chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	D2_chisq = new TH1F("D2 #chi^{2}","D2 #chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	reco_D2_exp_D1 = new TH2F("recD2_exp_D1","recD2_exp_D1; reconstructed from D1 (cm); expected from D1",400,-20,20,400,-20,20);
}

TrackReconstruction::~TrackReconstruction() { } 

void TrackReconstruction::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "NO OF EVENTS FOR TRACK RECONSTRUCTION: " << no_of_chosen_events << std::endl;
}

void TrackReconstruction::get_data(data_for_track_reconstruction _single_event_data)
{
	track_reco_data single_event_data;
	for (int i = 0; i < 8; i++)
	{
		single_event_data.x_hit_pos_D1[i] = _single_event_data.D1.positionsHitsX[i];
		single_event_data.x_err_hit_pos_D1[i] = _single_event_data.D1.errorsX[i];
		single_event_data.z_hit_pos_D1[i] = _single_event_data.D1.positionsZ[i];
	}
	for (int i = 0; i < 6; i++)
	{
		single_event_data.x_hit_pos_D2[i] = _single_event_data.D2.positionsHitsX[i];
		single_event_data.x_err_hit_pos_D2[i] = _single_event_data.D2.errorsX[i];
		single_event_data.z_hit_pos_D2[i] = _single_event_data.D2.positionsZ[i];
	}
//	for (int i = 0; i < 6; i++)
//	{
//		single_event_data.x_hit_pos_HEX[i] = _single_event_data.HEX.positionsHitsX[i];
//		single_event_data.x_err_hit_pos_HEX[i] = _single_event_data.HEX.errorsX[i];
//		single_event_data.z_hit_pos_HEX[i] = _single_event_data.HEX.positionsZ[i];
//	}
	TrackRecoData.push_back(single_event_data);
}

void TrackReconstruction::set_detectors_positions_on_vectors()
{
	for (int i = 0; i < TrackRecoData.size(); i++)
	{
		TrackRecoData.at(i).track3d_fit_point_D1.SetX(x_lab_position_D1 + TrackRecoData.at(i).track3d_fit_point_D1.X());
		TrackRecoData.at(i).track3d_fit_point_D1.SetZ(z_lab_position_D1 + TrackRecoData.at(i).track3d_fit_point_D1.Z());
		TrackRecoData.at(i).track3d_fit_point_D2.SetX(x_lab_position_D2 + TrackRecoData.at(i).track3d_fit_point_D2.X());
		TrackRecoData.at(i).track3d_fit_point_D2.SetZ(z_lab_position_D2 + TrackRecoData.at(i).track3d_fit_point_D2.Z());
	}
}

void TrackReconstruction::set_detectors_positions_on_points()
{
	for (unsigned int i = 0; i < TrackRecoData.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//std::cout << i << " " << j << " " << TrackRecoData.at(i).x_hit_pos_D1[j] << std::endl;
			TrackRecoData.at(i).x_hit_pos_D1[j] = TrackRecoData.at(i).x_hit_pos_D1[j] + x_lab_position_D1;
			//std::cout << i << " " << j << " " << TrackRecoData.at(i).x_hit_pos_D1[j] << std::endl;
			TrackRecoData.at(i).z_hit_pos_D1[j] = TrackRecoData.at(i).z_hit_pos_D1[j] + z_lab_position_D1;
		}
		for (int j = 0; j < 6; j++)
		{
			TrackRecoData.at(i).x_hit_pos_D2[j] = TrackRecoData.at(i).x_hit_pos_D2[j]+ x_lab_position_D2;
			//std::cout << i << " " << j << " " << TrackRecoData.at(i).x_hit_pos_D1[j] << std::endl;
			TrackRecoData.at(i).z_hit_pos_D2[j] = TrackRecoData.at(i).z_hit_pos_D2[j]+ z_lab_position_D2;
			//std::cout << i << " " << j << " " << TrackRecoData.at(i).x_hit_pos_D1[j] << std::endl;
		}
	}
}

void TrackReconstruction::fit_in_3d_D1()
{
	double aSt, bSt, track_angle, temp_chi2, layer_temp_chi2[8], temp_chi2_prob, layer_temp_chi2_prob[8];
	double wires_positionsX_all[8];
	double hits_positionsX_all[8];
	double hits_positionsZ_all[8];
	double errors_all[8];

	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in D1..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		//std::cout << "ok " << std::endl;
		//std::cout << i << std::endl;
		for (int j = 0; j < 8; j++)
		{
			//std::cout << "layer " << j << std::endl;
			wires_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_D1[j];
			//std::cout << wires_positionsX_all[j] << std::endl;
			hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_D1[j];
			hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos_D1[j];
			errors_all[j]=1;
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		Fit3d *fit3d = new Fit3d(i);
		fit3d -> Fit3d::set_no_of_iteration(0);
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
		fit3d -> Fit3d::make_fit_to_lines(false);
		TrackRecoData.at(i).track3d_fit_point_D1 = fit3d -> Fit3d::return_track_point();
		TrackRecoData.at(i).track3d_fit_vector_D1 = fit3d -> Fit3d::return_track_vector();
		//std::cout << "D1 " << TrackRecoData.at(i).track3d_fit_point_D1.X() << std::endl;
		//std::cout << "D1 " << TrackRecoData.at(i).track3d_fit_point_D1.Y() << std::endl;
		//std::cout << "D1 " << TrackRecoData.at(i).track3d_fit_point_D1.Z() << std::endl;

		TrackRecoData.at(i).errflag_D1 = fit3d -> Fit3d::err_flag();
		if ((!(fit3d -> Fit3d::err_flag())))
		{
			TrackRecoData.at(i).chi2_D1 = fit3d -> Fit3d::get_chisq();
			D1_chisq->Fill(TrackRecoData.at(i).chi2_D1);
			TrackRecoData.at(i).phi_xz_D1 = calculate_phi_xz(TrackRecoData.at(i).track3d_fit_vector_D1.X(), TrackRecoData.at(i).track3d_fit_vector_D1.Z());
			TrackRecoData.at(i).theta_yz_D1 = calculate_theta_yz(TrackRecoData.at(i).track3d_fit_vector_D1.Y(), TrackRecoData.at(i).track3d_fit_vector_D1.Z());
			//temp_chi2_prob = TMath::Prob(temp_chi2,4);
			//std::cout << TrackRecoData.at(i).phi_xz_D1 << std::endl;
			//std::cout << TrackRecoData.at(i).theta_yz_D1 << std::endl;
		}
		delete fit3d;
	}
}

void TrackReconstruction::fit_in_3d_D2()
{
	double aSt, bSt, track_angle, temp_chi2, layer_temp_chi2[6], temp_chi2_prob, layer_temp_chi2_prob[6];
	double wires_positionsX_all[6];
	double hits_positionsX_all[6];
	double hits_positionsZ_all[6];
	double errors_all[6];

	int no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in D2..." << std::endl;

	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			wires_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_D2[j];
			hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_D2[j];
			hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos_D2[j];
			errors_all[j]=1;
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		Fit3d_D2 *fit3d = new Fit3d_D2(i);
		fit3d -> Fit3d_D2::set_no_of_iteration(0);
		fit3d -> Fit3d_D2::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fit3d -> Fit3d_D2::fit_straight_layer();
		fit3d -> Fit3d_D2::fit_inclined_layers();
		fit3d -> Fit3d_D2::calculate_xy_functions();
		fit3d -> Fit3d_D2::set_hit_planes_vectors();
		fit3d -> Fit3d_D2::calculate_normal_to_hit_planes();
		fit3d -> Fit3d_D2::calculate_hit_planes_eq();
		fit3d -> Fit3d_D2::calculate_intersection_vectors();
		fit3d -> Fit3d_D2::calculate_intersection_points();
		fit3d -> Fit3d_D2::calculate_3d_track_parameters();
		fit3d -> Fit3d_D2::make_fit_to_lines(false);
		TrackRecoData.at(i).track3d_fit_point_D2 = fit3d -> Fit3d_D2::return_track_point();
		TrackRecoData.at(i).track3d_fit_vector_D2 = fit3d -> Fit3d_D2::return_track_vector();
		//std::cout << "D2 " << TrackRecoData.at(i).track3d_fit_point_D2.X() << std::endl;
		//std::cout << "D2 " << TrackRecoData.at(i).track3d_fit_point_D2.Y() << std::endl;
		//std::cout << "D2 " << TrackRecoData.at(i).track3d_fit_point_D2.Z() << std::endl;

		TrackRecoData.at(i).errflag_D2 = fit3d -> Fit3d_D2::err_flag();
		if ((!(fit3d -> Fit3d_D2::err_flag())))
		{
			TrackRecoData.at(i).chi2_D2 = fit3d -> Fit3d_D2::get_chisq();
			D2_chisq->Fill(TrackRecoData.at(i).chi2_D2);
			TrackRecoData.at(i).phi_xz_D2 = calculate_phi_xz(TrackRecoData.at(i).track3d_fit_vector_D2.X(), TrackRecoData.at(i).track3d_fit_vector_D2.Z());
			TrackRecoData.at(i).theta_yz_D2 = calculate_theta_yz(TrackRecoData.at(i).track3d_fit_vector_D2.Y(), TrackRecoData.at(i).track3d_fit_vector_D2.Z());
			//temp_chi2_prob = TMath::Prob(temp_chi2,4);
			//std::cout << TrackRecoData.at(i).phi_xz_D2 << std::endl;
			//std::cout << TrackRecoData.at(i).theta_yz_D2 << std::endl;
		}
		delete fit3d;
	}
}

void TrackReconstruction::fit_in_3d_HEX()
{
	double aSt, bSt, track_angle, temp_chi2, layer_temp_chi2[6], temp_chi2_prob, layer_temp_chi2_prob[6];
	double wires_positionsX_all[6];
	double hits_positionsX_all[6];
	double hits_positionsZ_all[6];
	double errors_all[6];

	int no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in HEX..." << std::endl;

	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			wires_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_HEX[j];
			hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_HEX[j];
			hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos_HEX[j];
			errors_all[j]=1;
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		Fit3d_HEX *fit3d = new Fit3d_HEX(i);
		fit3d -> Fit3d_HEX::set_no_of_iteration(0);
		fit3d -> Fit3d_HEX::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fit3d -> Fit3d_HEX::fit_straight_layer();
		fit3d -> Fit3d_HEX::fit_inclined_layers();
		fit3d -> Fit3d_HEX::calculate_xy_functions();
		fit3d -> Fit3d_HEX::set_hit_planes_vectors();
		fit3d -> Fit3d_HEX::calculate_normal_to_hit_planes();
		fit3d -> Fit3d_HEX::calculate_hit_planes_eq();
		fit3d -> Fit3d_HEX::calculate_intersection_vectors();
		fit3d -> Fit3d_HEX::calculate_intersection_points();
		fit3d -> Fit3d_HEX::calculate_3d_track_parameters();
		fit3d -> Fit3d_HEX::make_fit_to_lines(false);
		TrackRecoData.at(i).track3d_fit_point_HEX = fit3d -> Fit3d_HEX::return_track_point();
		TrackRecoData.at(i).track3d_fit_vector_HEX = fit3d -> Fit3d_HEX::return_track_vector();

		TrackRecoData.at(i).errflag_HEX = fit3d -> Fit3d_HEX::err_flag();
		if ((!(fit3d -> Fit3d_HEX::err_flag())))
		{
			TrackRecoData.at(i).chi2_HEX = fit3d -> Fit3d_HEX::get_chisq();
			TrackRecoData.at(i).phi_xz_HEX = calculate_phi_xz(TrackRecoData.at(i).track3d_fit_vector_HEX.X(), TrackRecoData.at(i).track3d_fit_vector_HEX.Z());
			TrackRecoData.at(i).theta_yz_HEX = calculate_theta_yz(TrackRecoData.at(i).track3d_fit_vector_HEX.Y(), TrackRecoData.at(i).track3d_fit_vector_HEX.Z());
			//temp_chi2_prob = TMath::Prob(temp_chi2,4);
			//std::cout << TrackRecoData.at(i).phi_xz_HEX << std::endl;
			//std::cout << TrackRecoData.at(i).theta_yz_HEX << std::endl;
		}
		delete fit3d;
	}
}

double TrackReconstruction::calculate_phi_xz(double vx, double vz)
{
	double phi_xz;
	double norm;
	norm = pow(vx*vx+vz*vz,0.5);
	vx = vx*pow(norm,-1);
	vz = vz*pow(norm,-1);
	phi_xz = TMath::ACos(vx)*180*pow(3.14,-1);
	return phi_xz;
}

double TrackReconstruction::calculate_theta_yz(double vy, double vz)
{
	double theta_yz;
	double norm;
	norm = pow(vz*vz+vy*vy,0.5);
	vz = vz*pow(norm,-1);
	vy = vy*pow(norm,-1);
	theta_yz = TMath::ACos(vy)*180*pow(3.14,-1);
	return theta_yz;
}

void TrackReconstruction::plot_D1_d2_phi_corr()
{
	for (unsigned int i = 0; i < TrackRecoData.size(); i++)
	{
		D1D2_phi_corr -> Fill(TrackRecoData.at(i).phi_xz_D1, TrackRecoData.at(i).phi_xz_D2);
		D1D2_theta_corr -> Fill(TrackRecoData.at(i).theta_yz_D1, TrackRecoData.at(i).theta_yz_D2);
		//D1HEX_phi_corr -> Fill(TrackRecoData.at(i).phi_xz_D1, TrackRecoData.at(i).phi_xz_HEX);
	}
	//TCanvas *c1 = new TCanvas("a","",500,500);
	//D1D2_phi_corr -> Draw("colz");
	//TCanvas *c2 = new TCanvas("b","",500,500);
	//D1D2_theta_corr -> Draw("colz");
	//c1 -> SaveAs("results/D1D2_phi_corr.root");
	//c2 -> SaveAs("results/D1D2_theta_corr.png");
}

void TrackReconstruction::save_histos()
{
	gDirectory->pwd();
	D1_chisq->Write();
	D2_chisq->Write();
	D1D2_phi_corr->Write();
	D1D2_theta_corr->Write();
	reco_D2_exp_D1->Write();
}

void TrackReconstruction::reconstructed_D2_vs_expected_D1()
{
	TVector3 D1_track_vector, D2_track_vector, D1_track_point, D2_track_point;
	double z_distance, scale;
	double x_from_D1, y_from_D1, x_from_D2, y_from_D2;
	for (unsigned int i = 0; i < TrackRecoData.size(); i++)
	{
		D1_track_vector = TrackRecoData.at(i).track3d_fit_vector_D1;
		D2_track_vector = TrackRecoData.at(i).track3d_fit_vector_D2;
		D1_track_point = TrackRecoData.at(i).track3d_fit_point_D1;
		D2_track_point = TrackRecoData.at(i).track3d_fit_point_D2;
		//std::cout << "D1_track_point " << D1_track_point.Z() << std::endl;
		//std::cout << "D2_track_point " << D2_track_point.Z() << std::endl;
		//std::cout << "D1_track_vector " << D1_track_vector.Z() << std::endl;
		//std::cout << "D2_track_vector " << D2_track_vector.Z() << std::endl;
		scale = D1_track_point.Z() - 59.6;
		x_from_D1 = scale*D1_track_vector.X() + D1_track_point.X();
		y_from_D1 = scale*D1_track_vector.Y() + D1_track_point.Y();
		scale = 7.8;
		x_from_D2 = scale*D2_track_vector.X() + D2_track_point.X();
		y_from_D2 = scale*D2_track_vector.Y() + D2_track_point.Y();
		//std::cout << x_from_D1 << " " << x_from_D2 << std::endl;
		reco_D2_exp_D1 -> Fill(y_from_D2, y_from_D1);
	}
}