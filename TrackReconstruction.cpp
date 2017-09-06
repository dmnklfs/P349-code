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
		//std::cout << single_event_data.x_hit_pos_D1[i] << std::endl;
	}
	for (int i = 0; i < 6; i++)
	{
		single_event_data.x_hit_pos_D2[i] = _single_event_data.D2.positionsHitsX[i];
		single_event_data.x_err_hit_pos_D2[i] = _single_event_data.D2.errorsX[i];
		single_event_data.z_hit_pos_D2[i] = _single_event_data.D2.positionsZ[i];
	}
	for (int i = 0; i < 6; i++)
	{
		single_event_data.x_hit_pos_HEX[i] = _single_event_data.HEX.positionsHitsX[i];
		single_event_data.x_err_hit_pos_HEX[i] = _single_event_data.HEX.errorsX[i];
		single_event_data.z_hit_pos_HEX[i] = _single_event_data.HEX.positionsZ[i];
	}
	TrackRecoData.push_back(single_event_data);
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
		track3d_fit_point_D1 = fit3d -> Fit3d::return_track_point();
		track3d_fit_vector_D1 = fit3d -> Fit3d::return_track_vector();

		TrackRecoData.at(i).errflag_D1 = fit3d -> Fit3d::err_flag();
		if ((!(fit3d -> Fit3d::err_flag())))
		{
			TrackRecoData.at(i).chi2_D1 = fit3d -> Fit3d::get_chisq();
			TrackRecoData.at(i).phi_xz_D1 = calculate_phi_xz(track3d_fit_vector_D1.X(), track3d_fit_vector_D1.Z());
			TrackRecoData.at(i).theta_yz_D1 = calculate_theta_yz(track3d_fit_vector_D1.Y(), track3d_fit_vector_D1.Z());
			//temp_chi2_prob = TMath::Prob(temp_chi2,4);
			std::cout << TrackRecoData.at(i).phi_xz_D1 << std::endl;
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
		track3d_fit_point_D2 = fit3d -> Fit3d_D2::return_track_point();
		track3d_fit_vector_D2 = fit3d -> Fit3d_D2::return_track_vector();

		TrackRecoData.at(i).errflag_D2 = fit3d -> Fit3d_D2::err_flag();
		if ((!(fit3d -> Fit3d_D2::err_flag())))
		{
			TrackRecoData.at(i).chi2_D2 = fit3d -> Fit3d_D2::get_chisq();
			TrackRecoData.at(i).phi_xz_D2 = calculate_phi_xz(track3d_fit_vector_D2.X(), track3d_fit_vector_D2.Z());
			TrackRecoData.at(i).theta_yz_D2 = calculate_theta_yz(track3d_fit_vector_D2.Y(), track3d_fit_vector_D2.Z());
			//temp_chi2_prob = TMath::Prob(temp_chi2,4);
			std::cout << TrackRecoData.at(i).phi_xz_D2 << std::endl;
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
		track3d_fit_point_HEX = fit3d -> Fit3d_HEX::return_track_point();
		track3d_fit_vector_HEX = fit3d -> Fit3d_HEX::return_track_vector();

		TrackRecoData.at(i).errflag_HEX = fit3d -> Fit3d_HEX::err_flag();
		if ((!(fit3d -> Fit3d_HEX::err_flag())))
		{
			TrackRecoData.at(i).chi2_HEX = fit3d -> Fit3d_HEX::get_chisq();
			TrackRecoData.at(i).phi_xz_HEX = calculate_phi_xz(track3d_fit_vector_HEX.X(), track3d_fit_vector_HEX.Z());
			TrackRecoData.at(i).theta_yz_HEX = calculate_theta_yz(track3d_fit_vector_HEX.Y(), track3d_fit_vector_HEX.Z());
			//temp_chi2_prob = TMath::Prob(temp_chi2,4);
			std::cout << TrackRecoData.at(i).phi_xz_HEX << std::endl;
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