#include "SingleEvent.h"

SingleEvent::SingleEvent()
{
	std::cout << "Object created " << std::endl;
}

SingleEvent::~SingleEvent()
{
	std::cout << "Object destructed " << std::endl;
}

bool SingleEvent::was_correct_event(const int stage)
{
	bool start = Start::was_correct_event();
	// event is ok if
	// 				- it is correct in selected detectots 
	// 				- or we read already preselected data 
	if ( (start ) || stage == 2)
	{
		return true;
	}
	else return false;
}

void SingleEvent::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	Start::fill_good_hits(_stage, _good_hit_data);
}

hist_data SingleEvent::get_hist_data()
{
	hist_data data_for_hists;
	data_for_hists.start_data = Start::get_hist_data();
	return data_for_hists;
}
