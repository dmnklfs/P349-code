#include "Start.h"

Start::Start()
	: Config::Config()
{ 
	correct_event = true;
}

Start::~Start()
{ 
	
}

void Start::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	if (1 ==_stage)  // input data before preselection
	{
		if ( 1 == _good_hit_data.layer)
		{
			RoughEdgeUp.push_back(_good_hit_data.edge);
			RoughTrealUp.push_back(_good_hit_data.treal);
			RoughElementUp.push_back(_good_hit_data.element);
		}
		if ( 2 == _good_hit_data.layer)
		{
			RoughEdgeDown.push_back(_good_hit_data.edge);
			RoughTrealDown.push_back(_good_hit_data.treal);
			RoughElementDown.push_back(_good_hit_data.element);
		}
	}

	if (2 ==_stage)  // input data after preselection
	{
		if ( 1 == _good_hit_data.layer)
		{
			TrealUp.push_back(_good_hit_data.treal);
			ElementUp.push_back(_good_hit_data.element);
		}
		if ( 2 == _good_hit_data.layer)
		{
			TrealDown.push_back(_good_hit_data.treal);
			ElementDown.push_back(_good_hit_data.element);
		}
	}
}

bool Start::was_correct_event()
{
	Start::check_hits();
	return correct_event;
}

void Start::check_hits()
{
	if (Start::check_size() && Start::check_signal(RoughEdgeUp, RoughTrealUp) && Start::check_signal(RoughEdgeDown, RoughTrealDown)) correct_event = true;
	else correct_event = false;
	Start::fill_data_if_correct();
}

bool Start::check_signal(std::vector<int> & Edge, std::vector<double > & Time)
{
	for (unsigned int i = 0; i < Config::start_hits; i++)
	{
		if ( 1 == Edge.at(2*i) && 0 == Edge.at(2*i+1) )
		{
			if (Start::check_time_range( Time.at(2*i)))
			{
				continue;
			}
			else return false;
		}
		else return false;
	}
	return true;
}

bool Start::check_size()
{
	if (Config::start_hits*2 == RoughElementUp.size() && Config::start_hits*2 == RoughElementDown.size()) 
	{
		return true;
	}
	else return false;
}

bool Start::check_time_range(double treal)
{
	if (treal > Config::start_time_min && treal < Config::start_time_max)
	{
		return true;
	}
	else return false;
}

void Start::fill_data_if_correct()
{
	if (correct_event)
	{
		for (unsigned int i = 0; i < Config::start_hits; i++)
		{
			TrealUp.push_back(RoughTrealUp.at(2*i));
			TrealDown.push_back(RoughTrealDown.at(2*i));
			ElementUp.push_back(RoughElementUp.at(2*i));
			ElementDown.push_back(RoughElementDown.at(2*i));
		}
	}
}

start_hist_data Start::get_hist_data()
{
	start_hist_data start_data;
	start_data.rough_multiplicity_up = RoughElementDown.size(); // RoughElementDown has all elements with leading and trailing edges
	start_data.rough_multiplicity_down = RoughElementUp.size();
	start_data.preselected_multiplicity_up = 2*ElementDown.size(); // ElementDown only single correct elements -> multiplicity = size*2
	start_data.preselected_multiplicity_down = 2*ElementUp.size();
	return start_data;
}