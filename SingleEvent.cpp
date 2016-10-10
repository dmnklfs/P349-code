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
	bool tof = TOF::was_correct_event();
	bool D1 = D1::was_correct_event();
	bool D2 = D2::was_correct_event();
	bool HEX = HEX::was_correct_event();
	bool intermediate = Intermediate::was_correct_event();
	bool fiber = Fiber::was_correct_event();


	bool D1andD2 = false;
	if ( D1::get_no_of_layers_with_hits() + D2::get_no_of_layers_with_hits() >= 4 ) D1andD2 = true;
	// event is ok if
	// 				- it is correct in selected detectots 
	// 				- or we read already preselected data 
	if ( (start && tof && fiber && HEX && D1) || stage == 2)
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

event_to_display SingleEvent::get_event_to_display()
{
	event_to_display event;

	event.HitsPlots.push_back(D1::get_all_hits_plot());
	event.DetectorPlots.push_back(D1::get_detector_plot());
	//event.D1_event_to_display = D1::get_event_to_display();
	return event;
}

double SingleEvent::getTOF()
{
	double tof;
	tof = TOF::getTime() - Start::getTime();
	return tof;
}

void SingleEvent::test_calculate_distances()
{
	D1::calculate_distances_from_wires();
	D1::calculate_relative_and_absolute_positions();
	D1::collect_hits_from_all_layers();
}
