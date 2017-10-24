#include "SingleEvent.h"

SingleEvent::SingleEvent()
{ }

SingleEvent::SingleEvent(const Config &_config)
	: Start::Start(_config), TOF::TOF(_config), D1::D1(_config), D2::D2(_config), HEX::HEX(_config), Intermediate::Intermediate(_config), Fiber::Fiber(_config)
{

}

SingleEvent::~SingleEvent()
{

}

bool SingleEvent::was_correct_event(const int stage)
{
	// do not remove functions below - they chose correct signals in each detector 
	bool start = Start::was_correct_event();
	//std::cout << " ok1 " << std::endl;
	bool tof = TOF::was_correct_event();
	//std::cout << " ok2 " << std::endl;
	bool D1 = D1::was_correct_event();
	//std::cout << " ok3 " << std::endl;
	bool D2 = D2::was_correct_event();
	//std::cout << " ok4 " << std::endl;
	bool HEX = HEX::was_correct_event();
	//std::cout << " ok5 " << std::endl;
	bool intermediate = Intermediate::was_correct_event();
	bool fiber = Fiber::was_correct_event();


	bool D1andD2 = false;
	if ( D1::get_no_of_layers_with_hits() + D2::get_no_of_layers_with_hits() >= 4 ) D1andD2 = true;
	// event is ok if
	// 				- it is correct in selected detectots 
	// 				- or we read already preselected data 
	// if ( (start && tof && D1 && D2 && HEX && Start::getTimeUp()<10 && Start::getTimeDown()<10) || stage == 2)
	if ( (start&&tof) || stage == 2)
	{
		return true;
	}
	else return false;
}

void SingleEvent::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	Start::fill_good_hits(_good_hit_data);
	TOF::fill_good_hits(_good_hit_data);
	D1::fill_good_hits(_good_hit_data);
	D2::fill_good_hits(_good_hit_data);
	HEX::fill_good_hits(_good_hit_data);
	Intermediate::fill_good_hits(_good_hit_data);
	Fiber::fill_good_hits(_good_hit_data);
}

hist_data SingleEvent::get_hist_data()
{
	hist_data data_for_hists;
	data_for_hists.start_data = Start::get_hist_data();
	data_for_hists.tof_data = TOF::get_hist_data();
	data_for_hists.d1_data = D1::get_hist_data();
	data_for_hists.d2_data = D2::get_hist_data();
	data_for_hists.hex_data = HEX::get_hist_data();
	data_for_hists.intermediate_data = Intermediate::get_hist_data();
	data_for_hists.fiber_data = Fiber::get_hist_data();
	return data_for_hists;
}

data_for_track_reconstruction SingleEvent::get_data_for_track_reconstruction()
{
	//std::cout << "i" << std::endl;
	data_for_track_reconstruction track_reco_data;
	track_reco_data.D1 = D1::get_data_for_track_reco();
	//std::cout << "ok6 " << std::endl;
	track_reco_data.D2 = D2::get_data_for_track_reco();
	//std::cout << "ok7 " << std::endl;
	//std::cout << " a " << std::endl;
	//track_reco_data.HEX = HEX::get_data_for_track_reco();
	//std::cout << "ok8 " << std::endl;
	//std::cout << "ok3 " << std::endl;
	//for (int i = 0; i < 8; i++)
	//{
	//	std::cout << "   " << i << " " << track_reco_data.D1.positionsX[i] << std::endl;
	//}
	
	return track_reco_data;
}

data_for_D1D2_calibration SingleEvent::get_data_for_D1D2_calibration()
{
	data_for_D1D2_calibration d1d2_calib_data;
	data_for_D1_calibration D1 = D1::get_data_for_calibration();
	data_for_D2_calibration D2 = D2::get_data_for_calibration();
	for (int i = 0; i < 6; i++)
	{
		d1d2_calib_data.positionsX[i] = D2.positionsX[i];
		d1d2_calib_data.positionsZ[i] = D2.positionsZ[i];
		d1d2_calib_data.drift_times[i] = D2.drift_times[i];
	}
	for (int i = 6; i < 14; i++)
	{
		d1d2_calib_data.positionsX[i] = D1.positionsX[i-6];
		d1d2_calib_data.positionsZ[i] = D1.positionsZ[i-6];
		d1d2_calib_data.drift_times[i] = D1.drift_times[i-6];
	}
	return d1d2_calib_data;	
}

double SingleEvent::getTOF()
{
	double tof;
	//tof = TOF::getTime() - Start::getTime();
	return tof;
}

void SingleEvent::test_calculate_distances()
{
	D1::calculate_distances_from_wires();
	D1::calculate_wire_positions_in_detector();
	D1::set_hits_absolute_positions();
	
	D2::calculate_distances_from_wires();
	D2::calculate_wire_positions_in_detector();
	D2::set_hits_absolute_positions();

	//std::cout << " a " << std::endl;
	//HEX::calculate_distances_from_wires();
	//HEX::calculate_wire_positions_in_detector();
//	//std::cout << " b " << std::endl;
	//HEX::set_hits_absolute_positions();

}

