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
		single_event_data.x_hit_pos_D1[8] = _single_event_data.D1.positionsX[i];
		single_event_data.x_err_hit_pos_D1[8] = _single_event_data.D1.errorsX[i];
		single_event_data.z_hit_pos_D1[8] = _single_event_data.D1.positionsZ[i];
	}
	for (int i = 0; i < 6; i++)
	{
		single_event_data.x_hit_pos_D1[6] = _single_event_data.D2.positionsX[i];
		single_event_data.x_err_hit_pos_D1[6] = _single_event_data.D2.errorsX[i];
		single_event_data.z_hit_pos_D1[6] = _single_event_data.D2.positionsZ[i];
	}
	for (int i = 0; i < 7; i++)
	{
		single_event_data.x_hit_pos_D1[7] = _single_event_data.HEX.positionsX[i];
		single_event_data.x_err_hit_pos_D1[7] = _single_event_data.HEX.errorsX[i];
		single_event_data.z_hit_pos_D1[7] = _single_event_data.HEX.positionsZ[i];
	}
	TrackRecoData.push_back(single_event_data);
}
