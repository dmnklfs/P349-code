#include "D1D2Reconstruction.h"

D1D2Reconstruction::D1D2Reconstruction() { }

D1D2Reconstruction::D1D2Reconstruction(const Config &_config)
{
	half_x_dim_D1 = _config.D1_half_x_dim;
	half_z_dim_D1 = _config.D1_half_z_dim;
	x_lab_position_D1 = _config.D1_x_lab_position;
	z_lab_position_D1 = _config.D1_z_lab_position;

	half_x_dim_D2 = _config.D2_half_x_dim;
	half_z_dim_D2 = _config.D2_half_z_dim;
	x_lab_position_D2 = _config.D2_x_lab_position;
	z_lab_position_D2 = _config.D2_z_lab_position;

	D2_x_offset = 0;
	D2_z_offset = 0;
	D2_y_offset = 0;

	// D1
	D1_chisq = new TH1F("D1 #chi^{2}","D1 #chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	D1_phi = new TH1F("D1_phi", "D1_phi; phi_xz [deg]; N", 200, 75, 105);
	D1_theta = new TH1F("D1_theta", "D1_theta; theta_xz [deg]; N", 200, 75, 105);

	//D2
	D2_chisq = new TH1F("D2 #chi^{2}","D2 #chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	D2_phi = new TH1F("D2_phi", "D2_phi; phi_xz [deg]; N", 200, 75, 105);
	D2_theta = new TH1F("D2_theta", "D2_theta; theta_yz [deg]; N", 200, 75, 105);

	//common
	phi = new TH1F("phi", "phi; phi_xz [deg]; N", 200, 75, 105);
	theta = new TH1F("theta", "theta; theta_yz [deg]; N", 200, 75, 105);
	chisq = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	chisq_ndf = new TH1F("#chi^{2}/ndf","#chi^{2}/ndf;#chi^{2}/ndf;N", 250, -0.025, 2.5);
	chi2_resc = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 250, -0.25, 25);
	chi2_resc_cut = new TH1F("#chi^{2} cut","#chi^{2} cut;#chi^{2};N", 250, -0.25, 25);
	probability = new TH1F("#chi^{2} prob", "#chi^{2} prob,;#chi^{2} prob;N", 100, -0.1, 1.1);
	probability_cut = new TH1F("#chi^{2} prob cut", "#chi^{2} prob cut,;#chi^{2} prob;N", 100, -0.1, 1.1);

	// correlations	
	// ---D1D2
	//    angles
	D1D2_phi_corr = new TH2F("D1D2_phi_corr","D1D2_phi_corr;D1_phi [deg];D2_phi [deg]", 200,75,105,200,75,105);
	D1D2_theta_corr = new TH2F("D1D2_theta_corr","D1D2_theta_corr;D1_theta [deg];D2_theta [deg]", 200,75,105,200,75,105);
	//    positions
	x_reco_D2_exp_D1 = new TH2F("x_recD2_exp_D1","x_recD2_exp_D1; reconstructed from D2 (cm); expected from D1",400,-20,20,400,-20,20);
	y_reco_D2_exp_D1 = new TH2F("y_recD2_exp_D1","y_recD2_exp_D1; reconstructed from D2 (cm); expected from D1",400,-20,20,400,-20,20);
	x_reco_D2_minus_exp_D1 = new TH1F("x_rec_D2_minus_exp_D1","x_rec_D2_minus_exp_D1;difference [cm];N", 200, -1.5, 1);
	y_reco_D2_minus_exp_D1 = new TH1F("y_rec_D2_minus_exp_D1","y_rec_D2_minus_exp_D1;difference [cm];N", 200, -4, 4);
}

D1D2Reconstruction::~D1D2Reconstruction() { } 


void D1D2Reconstruction::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "NO OF EVENTS FOR TRACK RECONSTRUCTION: " << no_of_chosen_events << std::endl;
}

void D1D2Reconstruction::set_x_offset(double xoffset)
{
	D2_x_offset = D2_x_offset + xoffset;
	for (int i = 0; i < TrackRecoData.size(); i++)
	{	
		for (int j = 0; j < 6; j++)
		{
			TrackRecoData.at(i).x_hit_pos[j] += xoffset;
			TrackRecoData.at(i).x_hit_pos_D2[j] += xoffset;
		}
	}
}

void D1D2Reconstruction::set_y_offset(double yoffset)
{
	D2_y_offset = yoffset;
}

void D1D2Reconstruction::set_z_offset(double zoffset)
{
	D2_z_offset = D2_z_offset+zoffset;
	for (int i = 0; i < TrackRecoData.size(); i++)
	{	
		for (int j = 0; j < 6; j++)
		{
			TrackRecoData.at(i).z_hit_pos[j] += zoffset;
			TrackRecoData.at(i).z_hit_pos_D2[j] += zoffset;
		}
	}
}


// all rotations etc can take place here
void D1D2Reconstruction::get_data(data_for_track_reconstruction _single_event_data)
{
	d1d2_reco_data single_event_data;
	// positions of hits with respect to the dc center
	for (int i = 0; i < 6; i++)
	{
		single_event_data.x_hit_pos_D2[i] = _single_event_data.D2.positionsHitsX[i] + x_lab_position_D2 + D2_x_offset;
		single_event_data.x_err_hit_pos_D2[i] = 1;//_single_event_data.D2.errorsX[i];
		single_event_data.z_hit_pos_D2[i] = _single_event_data.D2.positionsZ[i] + z_lab_position_D2 + D2_z_offset;
	}

	// positions of hits - with respect to the dc center
	for (int i = 0; i < 8; i++)
	{
		single_event_data.x_hit_pos_D1[i] = _single_event_data.D1.positionsHitsX[i];
		single_event_data.x_err_hit_pos_D1[i] = 1;//_single_event_data.D1.errorsX[i];
		single_event_data.z_hit_pos_D1[i] = _single_event_data.D1.positionsZ[i];
	}

	// here data for common reconstruction are shifted by appropriate offsets 
	for (int i = 0; i < 14; i++)
	{
		if (i < 6)
		{
			single_event_data.x_hit_pos[i] = _single_event_data.D2.positionsHitsX[i] + x_lab_position_D2;
			single_event_data.x_err_hit_pos[i] = 1;//_single_event_data.D2.errorsX[i];
			single_event_data.z_hit_pos[i] = _single_event_data.D2.positionsZ[i] + z_lab_position_D2;
			//std::cout << i+1 << " " << single_event_data.x_err_hit_pos[i] << std::endl;
		}
		else
		{
			single_event_data.x_hit_pos[i] = _single_event_data.D1.positionsHitsX[i-6];
			single_event_data.x_err_hit_pos[i] = 1;//_single_event_data.D1.errorsX[i-6];
			single_event_data.z_hit_pos[i] = _single_event_data.D1.positionsZ[i-6];
			//std::cout << i+1 << " " << single_event_data.x_err_hit_pos[i] << std::endl;
		}
	}


	TrackRecoData.push_back(single_event_data);
}

double D1D2Reconstruction::get_mean_chisq()
{
	double mean_chisq = 0;
	for (int i = 0; i < TrackRecoData.size(); i++)
	{		
		if (!TrackRecoData.at(i).errflag)
		{
			mean_chisq = mean_chisq + TrackRecoData.at(i).chi2;
			//std::cout << TrackRecoData.at(i).chi2 << std::endl;
		}
	}
	mean_chisq = mean_chisq*pow(TrackRecoData.size(),-1);
	return mean_chisq;
}

double D1D2Reconstruction::calculate_phi_xz(double vx, double vz)
{
	double phi_xz;
	double norm;
	norm = pow(vx*vx+vz*vz,0.5);
	vx = vx*pow(norm,-1);
	vz = vz*pow(norm,-1);
	phi_xz = TMath::ACos(vx)*180*pow(3.14,-1);
	return phi_xz;
}

double D1D2Reconstruction::calculate_theta_yz(double vy, double vz)
{
	double theta_yz;
	double norm;
	norm = pow(vz*vz+vy*vy,0.5);
	vz = vz*pow(norm,-1);
	vy = vy*pow(norm,-1);
	theta_yz = TMath::ACos(vy)*180*pow(3.14,-1);
	return theta_yz;
}

void D1D2Reconstruction::plot_D1_d2_phi_corr()
{
	double x_pos_layer_1, x_pos_layer_2, wire1, wire2;
	TVector3 D1_track_vector, D2_track_vector, D1_track_point, D2_track_point;
	double z_distance, scale;
	double x_from_D1, y_from_D1, x_from_D2, y_from_D2;
	//set_detectors_shift_on_D2_vectors(x_lab_position_D2+D2_x_offset, z_lab_position_D2+D2_z_offset);

	for (unsigned int i = 0; i < TrackRecoData.size(); i++)
	{

		if (!TrackRecoData.at(i).errflag)
		{
			chisq_ndf->Fill(0.01*TrackRecoData.at(i).chi2);
			chisq->Fill(TrackRecoData.at(i).chi2);
			chi2_resc->Fill(TrackRecoData.at(i).chi2);
			probability -> Fill(TMath::Prob(TrackRecoData.at(i).chi2,10));
			if (TMath::Prob(TrackRecoData.at(i).chi2,10) > 0.0)
			{
				chi2_resc_cut->Fill(TrackRecoData.at(i).chi2);
				probability_cut -> Fill(TMath::Prob(TrackRecoData.at(i).chi2,10));
				if (!TrackRecoData.at(i).errflag_D2&&!TrackRecoData.at(i).errflag_D1)
				{
					D1D2_phi_corr -> Fill(TrackRecoData.at(i).phi_xz_D1, TrackRecoData.at(i).phi_xz_D2);
					D1D2_theta_corr -> Fill(TrackRecoData.at(i).theta_yz_D1, TrackRecoData.at(i).theta_yz_D2);
				}
		
				if (!TrackRecoData.at(i).errflag_D1)
				{
					D1_chisq->Fill(TrackRecoData.at(i).chi2_D1);
					D1_phi -> Fill(TrackRecoData.at(i).phi_xz_D1);
					D1_theta -> Fill(TrackRecoData.at(i).theta_yz_D1);
				}
		
				if (!TrackRecoData.at(i).errflag_D2)
				{
					D2_chisq->Fill(TrackRecoData.at(i).chi2_D2);
					D2_phi -> Fill(TrackRecoData.at(i).phi_xz_D2);
					D2_theta -> Fill(TrackRecoData.at(i).theta_yz_D2);	
				}

				phi -> Fill(TrackRecoData.at(i).phi_xz);
				theta -> Fill(TrackRecoData.at(i).theta_yz);

				// points
				D1_track_vector = TrackRecoData.at(i).track3d_fit_vector_D1;
				D2_track_vector = TrackRecoData.at(i).track3d_fit_vector_D2;
				// vectors
				D1_track_point = TrackRecoData.at(i).track3d_fit_point_D1;
				D2_track_point = TrackRecoData.at(i).track3d_fit_point_D2;
		
				// D1D2
				scale = -fabs(z_lab_position_D1-z_lab_position_D2 )+half_z_dim_D2;
				x_from_D1 = scale*D1_track_vector.X() + D1_track_point.X();
				y_from_D1 = scale*D1_track_vector.Y() + D1_track_point.Y();
				scale = half_z_dim_D2;
				x_from_D2 = scale*D2_track_vector.X() + D2_track_point.X();
				y_from_D2 = scale*D2_track_vector.Y() + D2_track_point.Y();
				x_reco_D2_exp_D1 -> Fill(x_from_D2, x_from_D1);
				y_reco_D2_exp_D1 -> Fill(y_from_D2, y_from_D1);
				x_reco_D2_minus_exp_D1->Fill(x_from_D2-x_from_D1);
				y_reco_D2_minus_exp_D1->Fill(y_from_D2-y_from_D1);
			}
		}
		
	}
}

void D1D2Reconstruction::save_histos()
{
	gDirectory->pwd();
	std::string name(D1_chisq -> GetName());
	TString aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	//D1_chisq->Write(aname);

	//name = (D2_chisq->GetName());
	//aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	//D2_chisq->Write(aname);


	name = (chisq->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	chisq->Write(aname);
	name = (chisq_ndf->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	chisq_ndf->Write();
	name = (chi2_resc->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	chi2_resc->Write();
	name = (chi2_resc_cut->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	chi2_resc_cut->Write();

	probability->Write();
	probability_cut->Write();
	D1_phi -> Write();
	D1_theta -> Write();
	D2_phi -> Write();
	D2_theta -> Write();

	name = (phi->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	phi -> Write(aname);

	name = (theta->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	theta -> Write(aname);

	name = (D1D2_phi_corr->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	D1D2_phi_corr->Write(aname);

	name = (D1D2_theta_corr->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	D1D2_theta_corr->Write(aname);

	name = (x_reco_D2_exp_D1->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	x_reco_D2_exp_D1->Write(aname);

	name = (x_reco_D2_exp_D1->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	x_reco_D2_exp_D1->ProjectionX()->Write(aname);

	name = (y_reco_D2_exp_D1->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	y_reco_D2_exp_D1->Write(aname);

	name = (x_reco_D2_exp_D1->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	x_reco_D2_exp_D1->ProjectionY()->Write(aname);

	name = (x_reco_D2_minus_exp_D1->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	x_reco_D2_minus_exp_D1->Write(aname);

	name = (y_reco_D2_minus_exp_D1->GetName());
	aname = Form("%0.3lf_%0.3lf_%0.3lf_", D2_x_offset, D2_y_offset, D2_z_offset) + name;
	y_reco_D2_minus_exp_D1->Write(aname);
}

void D1D2Reconstruction::reconstructed_D2_vs_expected_D1()
{
	TVector3 D1_track_vector, D2_track_vector, D1_track_point, D2_track_point;
	double z_distance, scale;
	double x_from_D1, y_from_D1, x_from_D2, y_from_D2;
	//set_detectors_shift_on_D2_vectors(x_lab_position_D2, z_lab_position_D2);
	for (unsigned int i = 0; i < TrackRecoData.size(); i++)
	{
		// points
		D1_track_vector = TrackRecoData.at(i).track3d_fit_vector_D1;
		D2_track_vector = TrackRecoData.at(i).track3d_fit_vector_D2;
		// vectors
		D1_track_point = TrackRecoData.at(i).track3d_fit_point_D1;
		D2_track_point = TrackRecoData.at(i).track3d_fit_point_D2;

		// D1D2
		scale = -fabs(z_lab_position_D1-z_lab_position_D2 )+half_z_dim_D2;
		x_from_D1 = scale*D1_track_vector.X() + D1_track_point.X();
		y_from_D1 = scale*D1_track_vector.Y() + D1_track_point.Y();
		scale = half_z_dim_D2;
		x_from_D2 = scale*D2_track_vector.X() + D2_track_point.X();
		y_from_D2 = scale*D2_track_vector.Y() + D2_track_point.Y();
		x_reco_D2_exp_D1 -> Fill(x_from_D2, x_from_D1);
		y_reco_D2_exp_D1 -> Fill(y_from_D2, y_from_D1);
		x_reco_D2_minus_exp_D1->Fill(x_from_D2-x_from_D1);
		y_reco_D2_minus_exp_D1->Fill(y_from_D2-y_from_D1);
	}
}

void D1D2Reconstruction::fit_in_3d_D1()
{
	double wires_positionsX_all[8];
	double hits_positionsX_all[8];
	double hits_positionsZ_all[8];
	double errors_all[8];

	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in D1..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			wires_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_D1[j];
			hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos_D1[j];
			hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos_D1[j];
			errors_all[j]=TrackRecoData.at(i).x_err_hit_pos_D1[j];
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
		TrackRecoData.at(i).errflag_D1 = fit3d -> Fit3d::err_flag();
		if ((!(fit3d -> Fit3d::err_flag())))
		{
			TrackRecoData.at(i).chi2_D1 = fit3d -> Fit3d::get_chisq();
			TrackRecoData.at(i).phi_xz_D1 = calculate_phi_xz(TrackRecoData.at(i).track3d_fit_vector_D1.X(), TrackRecoData.at(i).track3d_fit_vector_D1.Z());
			TrackRecoData.at(i).theta_yz_D1 = calculate_theta_yz(TrackRecoData.at(i).track3d_fit_vector_D1.Y(), TrackRecoData.at(i).track3d_fit_vector_D1.Z());
		}
		delete fit3d;
	}
}

void D1D2Reconstruction::fit_in_3d_D2()
{
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
			errors_all[j]=TrackRecoData.at(i).x_err_hit_pos_D2[j];
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		Fit3d_D2 *fit3d = new Fit3d_D2(i);
		fit3d -> Fit3d_D2::set_no_of_iteration(0);
		fit3d -> Fit3d_D2::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fit3d -> Fit3d_D2::set_z_reference((hits_positionsZ_all[0]+hits_positionsZ_all[5])/2);
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
		TrackRecoData.at(i).errflag_D2 = fit3d -> Fit3d_D2::err_flag();
		if ((!(fit3d -> Fit3d_D2::err_flag())))
		{
			TrackRecoData.at(i).chi2_D2 = fit3d -> Fit3d_D2::get_chisq();
			TrackRecoData.at(i).phi_xz_D2 = calculate_phi_xz(TrackRecoData.at(i).track3d_fit_vector_D2.X(), TrackRecoData.at(i).track3d_fit_vector_D2.Z());
			TrackRecoData.at(i).theta_yz_D2 = calculate_theta_yz(TrackRecoData.at(i).track3d_fit_vector_D2.Y(), TrackRecoData.at(i).track3d_fit_vector_D2.Z());
		}
		delete fit3d;
	}
}

void D1D2Reconstruction::fit()
{
	double wires_positionsX_all[14];
	double hits_positionsX_all[14];
	double hits_positionsZ_all[14];
	double errors_all[14];
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in 3d..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			wires_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos[j]; // unused, just filling
			hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos[j];
			hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos[j];
			errors_all[j]=TrackRecoData.at(i).x_err_hit_pos[j];;
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		FitD1D2 *fitD1D2 = new FitD1D2(i);
		fitD1D2 -> FitD1D2::set_no_of_iteration(0);
		fitD1D2 -> FitD1D2::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fitD1D2 -> FitD1D2::set_z_reference((8*z_lab_position_D1 + 6*z_lab_position_D2)*pow(14,-1));
		fitD1D2 -> FitD1D2::fit_straight_layer();
		fitD1D2 -> FitD1D2::fit_inclined_layers();
		fitD1D2 -> FitD1D2::calculate_xy_functions();
		fitD1D2 -> FitD1D2::set_yoffsets(D2_y_offset);
		fitD1D2 -> FitD1D2::set_hit_planes_vectors();
		fitD1D2 -> FitD1D2::calculate_normal_to_hit_planes();
		fitD1D2 -> FitD1D2::calculate_hit_planes_eq();
		fitD1D2 -> FitD1D2::calculate_intersection_vectors();
		fitD1D2 -> FitD1D2::calculate_intersection_points();
		fitD1D2 -> FitD1D2::calculate_3d_track_parameters();
		fitD1D2 -> FitD1D2::calculate_projections_on_hit_planes_calculations();
		fitD1D2 -> FitD1D2::make_fit_to_lines(false);
		TrackRecoData.at(i).track3d_fit_point = fitD1D2 -> FitD1D2::return_track_point();
		TrackRecoData.at(i).track3d_fit_vector = fitD1D2 -> FitD1D2::return_track_vector();
		TrackRecoData.at(i).errflag = fitD1D2 -> FitD1D2::err_flag();
		if ((!(fitD1D2 -> FitD1D2::err_flag())))
		{
			TrackRecoData.at(i).chi2 = fitD1D2 -> FitD1D2::get_chisq();
			TrackRecoData.at(i).phi_xz = calculate_phi_xz(TrackRecoData.at(i).track3d_fit_vector.X(), TrackRecoData.at(i).track3d_fit_vector.Z());
			TrackRecoData.at(i).theta_yz = calculate_theta_yz(TrackRecoData.at(i).track3d_fit_vector.Y(), TrackRecoData.at(i).track3d_fit_vector.Z());
			
		}
		delete fitD1D2;
	}
}

void D1D2Reconstruction::deletations()
{
	D1_chisq -> Reset();
	D1_phi -> Reset();
	D1_theta -> Reset();
	D2_chisq -> Reset();
	D2_phi -> Reset();
	D2_theta -> Reset();
	phi -> Reset();
	theta -> Reset();
	chisq -> Reset();
	chisq_ndf -> Reset();
	chi2_resc -> Reset();
	chi2_resc_cut -> Reset();
	probability -> Reset();
	probability_cut -> Reset();
	D1D2_phi_corr -> Reset();
	D1D2_theta_corr -> Reset();
	x_reco_D2_exp_D1 -> Reset();
	y_reco_D2_exp_D1 -> Reset();
	x_reco_D2_minus_exp_D1 -> Reset();
	y_reco_D2_minus_exp_D1 -> Reset();
}