#include "SingleEvent.h"

SingleEvent::SingleEvent()
{
	//std::cout << "Object created " << std::endl;

}

SingleEvent::~SingleEvent()
{
	//std::cout << "Object destructed " << std::endl;
}

bool SingleEvent::was_correct_event(const int stage)
{
	bool start = Start::was_correct_event();
	bool tof = TOF::was_correct_event();
	bool D1 = D1::was_correct_event();
	bool D2 = D2::was_correct_event();
	bool HEX = HEX::was_correct_event();
	bool intermediate = Intermediate::was_correct_event();
	bool fiber = Fiber::was_correct_event();
	// event is ok if
	// 				- it is correct in selected detectots 
	// 				- or we read already preselected data 
	if ( (start && tof && D1 && D2 && HEX && intermediate && fiber) || stage == 2)  // add TOF
	{
		return true;
	}
	else return false;
}

void SingleEvent::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	Start::fill_good_hits(_stage, _good_hit_data);
	TOF::fill_good_hits(_stage, _good_hit_data);
	D1::fill_good_hits(_stage, _good_hit_data);
	D2::fill_good_hits(_stage, _good_hit_data);
	HEX::fill_good_hits(_stage, _good_hit_data);
	Intermediate::fill_good_hits(_stage, _good_hit_data);
	Fiber::fill_good_hits(_stage, _good_hit_data);
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
