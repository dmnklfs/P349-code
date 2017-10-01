#include "D1D23d.h"

D1D23d::D1D23d() { }

D1D23d::D1D23d(const Config &_config)
{
	half_x_dim_D1 = _config.D1_half_x_dim;
	half_z_dim_D1 = _config.D1_half_z_dim;
	x_lab_position_D1 = _config.D1_x_lab_position;
	y_lab_position_D1 = _config.D1_y_lab_position;
	z_lab_position_D1 = _config.D1_z_lab_position;

	half_x_dim_D2 = _config.D2_half_x_dim;
	half_z_dim_D2 = _config.D2_half_z_dim;
	x_lab_position_D2 = _config.D2_x_lab_position;
	y_lab_position_D2 = _config.D2_y_lab_position;
	z_lab_position_D2 = _config.D2_z_lab_position;

	D1_x_rot = _config.D1_x_rotation_angle; 
	D1_y_rot = _config.D1_y_rotation_angle; 
	D1_z_rot = _config.D1_z_rotation_angle;
	D2_x_rot = _config.D2_x_rotation_angle; 
	D2_y_rot = _config.D2_y_rotation_angle; 
	D2_z_rot = _config.D2_z_rotation_angle;

	phi = new TH1F("phi", "phi; phi_xz [deg]; N", 200, 75, 105);
	theta = new TH1F("theta", "theta; theta_yz [deg]; N", 200, 75, 105);
	chi2 = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	chi2_resc = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 250, -0.25, 25);
	calc_px = new TH1F("calc_px",";calc_px,N",6250,-20,20);
	calc_py = new TH1F("calc_py",";calc_py,N",5000,-40,40);
	calc_pz = new TH1F("calc_pz",";calc_pz,N",500,-60,0);
	calc_vx = new TH1F("calc_vx",";calc_vx,N",20000,-0.5,0.5);
	calc_vy = new TH1F("calc_vy",";calc_vy,N",20000,-0.5,0.5);
	calc_vz = new TH1F("calc_vz",";calc_vz,N",50000,0.9,1.1);
}

D1D23d::~D1D23d() { } 


void D1D23d::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "NO OF EVENTS FOR TRACK RECONSTRUCTION: " << no_of_chosen_events << std::endl;
}

// get_data: only reads in data from d1 and d2
void D1D23d::get_data(data_for_track_reconstruction _single_event_data)
{
	d1d2_3d_data single_event_data;

	// here data for common reconstruction are shifted by appropriate offsets 
	for (int i = 0; i < 14; i++)
	{
		if (i<6)
		{
			single_event_data.x_hit_pos[i] = _single_event_data.D2.positionsHitsX[i];
			single_event_data.x_err_hit_pos[i] = _single_event_data.D2.errorsX[i];
			single_event_data.z_hit_pos[i] = _single_event_data.D2.positionsZ[i];
		}
		else
		{
			single_event_data.x_hit_pos[i] = _single_event_data.D1.positionsHitsX[i-6];
			single_event_data.x_err_hit_pos[i] = _single_event_data.D1.errorsX[i-6];
			single_event_data.z_hit_pos[i] = _single_event_data.D1.positionsZ[i-6];
		}
	}


	TrackRecoData.push_back(single_event_data);
}

void D1D23d::fit()
{
	// for approximate track reconstruction
	double wires_positionsX_all[14];
	double hits_positionsX_all[14];
	double hits_positionsZ_all[14];
	double errors_all[14];
	//--------------------------------------
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "Fit in 3d..." << std::endl;
	for (unsigned int i = 0; i < no_of_chosen_events; i++)
	{
		for (int j = 0; j < 14; j++) // here just added x and z offsets for correct start parameters
		{
			if (j < 6)
			{
				wires_positionsX_all[j] = 0; // unused, just filling
				hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos[j]+x_lab_position_D2;
				hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos[j]+z_lab_position_D2;
				errors_all[j]=TrackRecoData.at(i).x_err_hit_pos[j];
			}
			else
			{
				wires_positionsX_all[j] = 0; // unused, just filling
				hits_positionsX_all[j] = TrackRecoData.at(i).x_hit_pos[j]+x_lab_position_D1;
				hits_positionsZ_all[j] = TrackRecoData.at(i).z_hit_pos[j]+z_lab_position_D1;
				errors_all[j]=TrackRecoData.at(i).x_err_hit_pos[j];
			}
			
		}
		
		if (0==i%1000) std::cout << "    " << i << " out of " << no_of_chosen_events << " done" << std::endl;

		FitToLines *fitToLines = new FitToLines(i);
		fitToLines -> FitToLines::set_no_of_iteration(0);
		fitToLines -> FitToLines::set_values(hits_positionsX_all,hits_positionsZ_all,errors_all, wires_positionsX_all);
		fitToLines -> FitToLines::set_z_reference((8*z_lab_position_D1 + 6*z_lab_position_D2)*pow(16,-1));
		fitToLines -> FitToLines::fit_straight_layer();
		fitToLines -> FitToLines::fit_inclined_layers();
		fitToLines -> FitToLines::calculate_xy_functions();
		fitToLines -> FitToLines::set_hit_planes_vectors();
		fitToLines -> FitToLines::calculate_normal_to_hit_planes();
		fitToLines -> FitToLines::calculate_hit_planes_eq();
		fitToLines -> FitToLines::calculate_intersection_vectors();
		fitToLines -> FitToLines::calculate_intersection_points();
		fitToLines -> FitToLines::calculate_3d_track_parameters();
		ApproxTrackPoint = fitToLines -> FitToLines::return_approx_track_point();
		ApproxTrackVector = fitToLines -> FitToLines::return_approx_track_vector();
		//std::cout << ApproxTrackVector.X() << " " << ApproxTrackVector.Y() << " " << ApproxTrackVector.Z()  << std::endl;
		//std::cout << ApproxTrackPoint.X() << " " << ApproxTrackPoint.Y() << " " << ApproxTrackPoint.Z()  << std::endl;
		calc_px -> Fill(ApproxTrackPoint.X());
		calc_py -> Fill(ApproxTrackPoint.Y());
		calc_pz -> Fill(ApproxTrackPoint.Z());
		calc_vx -> Fill(ApproxTrackVector.X());
		calc_vy -> Fill(ApproxTrackVector.Y());
		calc_vz -> Fill(ApproxTrackVector.Z());
	}
}

void D1D23d::Save_histos()
{
	gDirectory->pwd();
	calc_px -> Write();
	calc_py -> Write();
	calc_pz -> Write();
	calc_vx -> Write();
	calc_vy -> Write();
	calc_vz -> Write();
}