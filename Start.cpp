#include "Start.h"

Start::Start()
	: Config::Config()
{ 
	correct_event = true;
}

Start::~Start()
{ 
	
}

void Start::fill_good_hits(single_gh_data _good_hit_data)
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

bool Start::was_correct_event()
{
	Start::check_hits();
	return correct_event;
}

void Start::check_hits()
{
	// here the correct signals are chosen, do not remove it
	Start::choose_corr_leading_up();
	Start::choose_corr_leading_down();

	bool size_up = check_size_up();
	bool size_down = check_size_down(); // checks if size is in agreement with config
	bool coincidence = check_coincidence(); // checks if vectors are of the same size
	if (size_up&&size_down&&coincidence)
	{
		mean_time = 0.5*(TrealUp.at(0)+TrealDown.at(0));
		correct_event = true;
	}
	else correct_event = false;
}

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
// (applies constraints on time range according to Config)
void Start::choose_corr_leading_up()
{
	int iterations = RoughEdgeUp.size()-1;
	if (RoughEdgeUp.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdgeUp.at(i)&&0==RoughEdgeUp.at(i+1))
		{
			if (check_time_range(RoughTrealUp.at(i)))
			{
				TrealUp.push_back(RoughTrealUp.at(i));
				ElementUp.push_back(RoughElementUp.at(i));
			}
		}
		//if (RoughEdgeUp.at(i)==RoughEdgeUp.at(i+1)) break;
	}
}

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
// (applies constraints on time range according to Config)
void Start::choose_corr_leading_down()
{
	int iterations = RoughEdgeDown.size()-1;
	if (RoughEdgeDown.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdgeDown.at(i)&&0==RoughEdgeDown.at(i+1))
		{
			if (check_time_range(RoughTrealDown.at(i)))
			{
				TrealDown.push_back(RoughTrealDown.at(i));
				ElementDown.push_back(RoughElementDown.at(i));
			}
		}
		//if (RoughEdgeDown.at(i)==RoughEdgeDown.at(i+1)) break;
	}
}

bool Start::check_size_up()
{
	if (Config::start_hits == -1) return true;
	if ((unsigned int)Config::start_hits == ElementUp.size()) 
	{
		return true;
	}
	else return false;
}

bool Start::check_size_down()
{
	if (Config::start_hits == -1) return true;
	if ((unsigned int)Config::start_hits == ElementDown.size()) 
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

bool Start::check_coincidence()
{
	bool was_coincidence = true;
	if (ElementUp.size()==ElementDown.size())
	{
		for (unsigned int i = 0; i < ElementUp.size(); i++)
		{
			if (ElementUp.at(i) == ElementDown.at(i))
			{
				continue;
			}
			else
			{
				was_coincidence = false;
				break;
			}
		}
	}
	else was_coincidence = false;
	return was_coincidence;
}

start_hist_data* Start::get_hist_data()
{
	start_hist_data *start_data = new start_hist_data();
	start_data -> rough_multiplicity_up = RoughElementDown.size(); // RoughElementDown has all elements with leading and trailing edges
	start_data -> rough_multiplicity_down = RoughElementUp.size();
	start_data -> preselected_multiplicity_up = 2*ElementUp.size(); // ElementDown only single correct elements -> multiplicity = size*2
	start_data -> preselected_multiplicity_down = 2*ElementDown.size();
	return start_data;
}

double Start::getTime()
{
	return mean_time;
}