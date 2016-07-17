#include "Intermediate.h"

Intermediate::Intermediate()
	: Config::Config()
{ 
	correct_event = true;
}

Intermediate::~Intermediate()
{ 
	
}


void Intermediate::fill_good_hits(single_gh_data _good_hit_data)
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

bool Intermediate::was_correct_event()
{
	Intermediate::check_hits();
	return correct_event;
}

void Intermediate::check_hits()
{
	Intermediate::choose_corr_leading_up();
	Intermediate::choose_corr_leading_down();
	//bool size_up = check_size_up();
	//bool size_down = check_size_down();
	bool coincidence = check_coincidence();
	if (coincidence)
	{
		correct_event = true;
	}
	else correct_event = false;
}

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
void Intermediate::choose_corr_leading_up()
{
	int iterations = RoughEdgeUp.size()-1;
	if (RoughEdgeUp.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdgeUp.at(i)&&0==RoughEdgeUp.at(i+1)&&RoughElementUp.at(i)==RoughElementUp.at(i+1))
		{
			if (check_time_range(RoughTrealUp.at(i))&&check_elements_range(RoughElementUp.at(i)))
			{
				TrealUp.push_back(RoughTrealUp.at(i));
				ElementUp.push_back(RoughElementUp.at(i));
			}
		}
		//if (RoughEdgeUp.at(i)==RoughEdgeUp.at(i+1)) break;
	}
}

void Intermediate::choose_corr_leading_down()
{
	int iterations = RoughEdgeDown.size()-1;
	if (RoughEdgeDown.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdgeDown.at(i)&&0==RoughEdgeDown.at(i+1)&&RoughElementDown.at(i)==RoughElementDown.at(i+1))
		{
			if (check_time_range(RoughTrealDown.at(i))&&check_elements_range(RoughElementDown.at(i)))
			{
				TrealDown.push_back(RoughTrealDown.at(i));
				ElementDown.push_back(RoughElementDown.at(i));
			}
		}
		//if (RoughEdgeDown.at(i)==RoughEdgeDown.at(i+1)) break;
	}
}

bool Intermediate::check_elements_range(int element)
{
	if (element >= Config::Intermediate_element_min && element <= Config::Intermediate_element_max)
	{
		return true;
	}
	else return false;
}

bool Intermediate::check_size_up()
{
	if (Config::Intermediate_hits == -1) return true;
	if ((unsigned int)Config::Intermediate_hits == ElementUp.size()) 
	{
		return true;
	}
	else return false;
}

bool Intermediate::check_size_down()
{
	if (Config::Intermediate_hits == -1) return true;
	if ((unsigned int)Config::Intermediate_hits == ElementDown.size()) 
	{
		return true;
	}
	else return false;
}

bool Intermediate::check_time_range(double treal)
{
	if (treal > Config::Intermediate_time_min && treal < Config::Intermediate_time_max)
	{
		return true;
	}
	else return false;
}

bool Intermediate::check_coincidence()
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

TOF_hist_data* Intermediate::get_hist_data()
{
	TOF_hist_data *intermediate_data = new TOF_hist_data(RoughElementUp,RoughElementDown,ElementUp,ElementDown);
	intermediate_data->rough_multiplicity_up = RoughElementUp.size(); // RoughElementDown has all elements with leading and trailing edges
	intermediate_data->rough_multiplicity_down = RoughElementDown.size();
	intermediate_data->preselected_multiplicity_up = 2*ElementUp.size(); // ElementDown only single correct elements -> multiplicity = size*2
	intermediate_data->preselected_multiplicity_down = 2*ElementDown.size();
	intermediate_data->rough_elements_up = RoughElementUp;
	intermediate_data->rough_elements_down = RoughElementDown;
	intermediate_data->preselected_elements_up = ElementUp;
	intermediate_data->preselected_elements_down = ElementDown;

	return intermediate_data;
}
