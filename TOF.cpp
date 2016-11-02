#include "TOF.h"

TOF::TOF()
{ 
	correct_event = true;
}

TOF::TOF(const Config &_config)
{
	correct_event = true;
	element_min = _config.TOF_element_min;
	element_max = _config.TOF_element_max;
	hits = _config.TOF_hits;
	time_min = _config.TOF_time_min;
	time_max = _config.TOF_time_max;
}

TOF::~TOF()
{ 
	
}


void TOF::fill_good_hits(single_gh_data _good_hit_data)
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

bool TOF::was_correct_event()
{
	TOF::check_hits();
	return correct_event;
}

void TOF::check_hits()
{
	// here the correct signals are chosen, do not remove it
	TOF::choose_corr_leading_up();
	TOF::choose_corr_leading_down();
	bool size_up = check_size_up();
	bool size_down = check_size_down();
	bool coincidence = check_coincidence();
	if (size_up&&size_down&&coincidence)	// condition only on the upper layer
	{
		// comment the line below if no conditions on size d
		//mean_time = 0.5*(TrealUp.at(0)+TrealDown.at(0));
		correct_event = true;
	}
	else correct_event = false;
}

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
// (applies constraints on time range and elements range according to Config)
void TOF::choose_corr_leading_up()
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

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
// (applies constraints on time range and elements range according to Config)
void TOF::choose_corr_leading_down()
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

bool TOF::check_elements_range(int element)
{
	if (element >= element_min && element <= element_max)
	{
		return true;
	}
	else return false;
}

bool TOF::check_size_up()
{
	if  (hits == -1) return true;
	if ((unsigned int) hits == ElementUp.size()) 
	{
		return true;
	}
	else return false;
}

bool TOF::check_size_down()
{
	if  (hits == -1) return true;
	if ((unsigned int) hits == ElementDown.size()) 
	{
		return true;
	}
	else return false;
}

bool TOF::check_time_range(double treal)
{
	if (treal > time_min && treal < time_max)
	{
		return true;
	}
	else return false;
}

bool TOF::check_coincidence()
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

TOF_hist_data* TOF::get_hist_data()
{
	TOF_hist_data *TOF_data = new TOF_hist_data(RoughElementUp,RoughElementDown,ElementUp,ElementDown);
	TOF_data->rough_multiplicity_up = RoughElementUp.size(); // RoughElementDown has all elements with leading and trailing edges
	TOF_data->rough_multiplicity_down = RoughElementDown.size();
	TOF_data->preselected_multiplicity_up = 2*ElementUp.size(); // ElementDown only single correct elements -> multiplicity = size*2
	TOF_data->preselected_multiplicity_down = 2*ElementDown.size();
	TOF_data->rough_elements_up = RoughElementUp;
	TOF_data->rough_elements_down = RoughElementDown;
	TOF_data->preselected_elements_up = ElementUp;
	TOF_data->preselected_elements_down = ElementDown;

	return TOF_data;
}

double TOF::getTime()
{
	return mean_time;
}