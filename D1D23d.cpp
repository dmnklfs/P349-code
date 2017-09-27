#include "D1D23d.h"

D1D23d::D1D23d() { }

D1D23d::D1D23d(const Config &_config)
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
	D2_y_offset = 0;
	D2_z_offset = 0;

	phi = new TH1F("phi", "phi; phi_xz [deg]; N", 200, 75, 105);
	theta = new TH1F("theta", "theta; theta_yz [deg]; N", 200, 75, 105);
	chi2 = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 1000, -0.001, 0.05);
	chi2_resc = new TH1F("#chi^{2}","#chi^{2};#chi^{2};N", 250, -0.25, 25);

}

D1D23d::~D1D23d() { } 


void D1D23d::tell_no_of_events()
{
	unsigned int no_of_chosen_events;
	no_of_chosen_events = TrackRecoData.size();
	std::cout << "NO OF EVENTS FOR TRACK RECONSTRUCTION: " << no_of_chosen_events << std::endl;
}

void D1D23d::set_x_offset(double xoffset)
{
	D2_x_offset = D2_x_offset + xoffset;
	for (int i = 0; i < TrackRecoData.size(); i++)
	{	
		for (int j = 0; j < 6; j++)
		{
			TrackRecoData.at(i).x_hit_pos[j] += xoffset;
			//TrackRecoData.at(i).x_hit_pos_D2[j] += xoffset;
		}
	}
}

void D1D23d::set_z_offset(double zoffset)
{
	D2_z_offset = D2_z_offset+zoffset;
	for (int i = 0; i < TrackRecoData.size(); i++)
	{	
		for (int j = 0; j < 6; j++)
		{
			TrackRecoData.at(i).z_hit_pos[j] += zoffset;
			//TrackRecoData.at(i).z_hit_pos_D2[j] += zoffset;
		}
	}
}


// get_data: only reads in data from d1 and d2
void D1D23d::get_data(data_for_track_reconstruction _single_event_data)
{
	d1d2_3d_data single_event_data;
	// positions of hits with respect to the dc center
//	for (int i = 0; i < 6; i++)
//	{
//		single_event_data.x_hit_pos_D2[i] = _single_event_data.D2.positionsHitsX[i] + x_lab_position_D2;
//		single_event_data.x_err_hit_pos_D2[i] = _single_event_data.D2.errorsX[i];
//		single_event_data.z_hit_pos_D2[i] = _single_event_data.D2.positionsZ[i] + z_lab_position_D2;
//	}
//
//	// positions of hits - with respect to the dc center
//	for (int i = 0; i < 8; i++)
//	{
//		single_event_data.x_hit_pos_D1[i] = _single_event_data.D1.positionsHitsX[i];
//		single_event_data.x_err_hit_pos_D1[i] = _single_event_data.D1.errorsX[i];
//		single_event_data.z_hit_pos_D1[i] = _single_event_data.D1.positionsZ[i];
//	}

	// here data for common reconstruction are shifted by appropriate offsets 
	for (int i = 0; i < 14; i++)
	{
		if (i < 6)
		{
			single_event_data.x_hit_pos[i] = _single_event_data.D2.positionsHitsX[i] + x_lab_position_D2;
			single_event_data.x_err_hit_pos[i] = _single_event_data.D2.errorsX[i];
			single_event_data.z_hit_pos[i] = _single_event_data.D2.positionsZ[i] + z_lab_position_D2;
			//std::cout << i+1 << " " << single_event_data.x_err_hit_pos[i] << std::endl;
		}
		else
		{
			single_event_data.x_hit_pos[i] = _single_event_data.D1.positionsHitsX[i-6];
			single_event_data.x_err_hit_pos[i] = _single_event_data.D1.errorsX[i-6];
			single_event_data.z_hit_pos[i] = _single_event_data.D1.positionsZ[i-6];
			//std::cout << i+1 << " " << single_event_data.x_err_hit_pos[i] << std::endl;
		}
	}


	TrackRecoData.push_back(single_event_data);
}

void D1D23d::fit()
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
		fitD1D2 -> FitD1D2::set_z_reference(0.5*(z_lab_position_D1 + z_lab_position_D2));
		fitD1D2 -> FitD1D2::fit_straight_layer();
		fitD1D2 -> FitD1D2::fit_inclined_layers();
		fitD1D2 -> FitD1D2::calculate_xy_functions();
		fitD1D2 -> FitD1D2::set_hit_planes_vectors();
		fitD1D2 -> FitD1D2::calculate_normal_to_hit_planes();
		fitD1D2 -> FitD1D2::calculate_hit_planes_eq();
		fitD1D2 -> FitD1D2::calculate_intersection_vectors();
		fitD1D2 -> FitD1D2::calculate_intersection_points();
		fitD1D2 -> FitD1D2::calculate_3d_track_parameters();

	}
}