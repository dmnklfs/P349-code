#include "TOF.h"

TOF::TOF()
	: Config::Config()
{ 
	correct_event = true;
}

TOF::~TOF()
{ 
	
}


void TOF::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
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

bool TOF::was_correct_event()
{
	TOF::check_hits();
	return correct_event;
}

void TOF::check_hits()
{
	bool config_size_up = TOF::check_size_up();
	bool config_size_down = TOF::check_size_down();
	bool same_elements = TOF::check_elements(RoughElementDown, RoughElementUp);
	bool correct_signal_up = TOF::check_signal(RoughEdgeUp, RoughTrealUp);
	//std::cout << "ok1" << std::endl;
	//std::cout << RoughEdgeDown.size() << " " << RoughTrealDown.size() << std::endl;
	bool correct_signal_down = TOF::check_signal(RoughEdgeDown, RoughTrealDown);
	//std::cout << "ok2" << std::endl;
	if (config_size_up && config_size_down && same_elements && correct_signal_up && correct_signal_down)
	{
		correct_event = true;
	}
	else correct_event = false;
	TOF::fill_data_if_correct();
}

bool TOF::check_signal(std::vector<int> & Edge, std::vector<double > & Time)
{
	bool corr_signal = true;
	if (2*Config::TOF_hits == Edge.size())
	{
		for (unsigned int i = 0; i < Config::TOF_hits; i++)
		{
			if ( 1 == Edge.at(2*i) && 0 == Edge.at(2*i+1) )
			{
				if (TOF::check_time_range( Time.at(2*i)))
				{
					continue;
				}
				else corr_signal = false;
			}
			else corr_signal = false;
		}
	}
	return corr_signal;
}

bool TOF::check_elements(std::vector<int> & _ElementDown, std::vector<int> & _ElementUp)
{
	bool corr_elements = true;
	if (TOF::check_size_up()&&TOF::check_size_down())
	{
		for (unsigned int i = 0; i < Config::TOF_hits; i++)
		{
			if (_ElementUp.at(i) == _ElementDown.at(i))
			{
				if (_ElementUp.at(i) >= Config::TOF_element_min && _ElementUp.at(i) <= Config::TOF_element_max)
				{
					continue;
				}
				else corr_elements = false;
			}
			else corr_elements = false;
		}
	}
	else corr_elements = false;
	return corr_elements;
}

bool TOF::check_size_up()
{
	if (Config::TOF_hits*2 == RoughElementUp.size()) 
	{
		return true;
	}
	else return false;
}

bool TOF::check_size_down()
{
	if (Config::TOF_hits*2 == RoughElementDown.size()) 
	{
		return true;
	}
	else return false;
}

bool TOF::check_time_range(double treal)
{
	if (treal > Config::TOF_time_min && treal < Config::TOF_time_max)
	{
		return true;
	}
	else return false;
}

void TOF::fill_data_if_correct()
{
	if (correct_event)
	{
		for (unsigned int i = 0; i < Config::TOF_hits; i++)
		{
			TrealUp.push_back(RoughTrealUp.at(2*i));
			TrealDown.push_back(RoughTrealDown.at(2*i));
			ElementUp.push_back(RoughElementUp.at(2*i));
			ElementDown.push_back(RoughElementDown.at(2*i));
		}
	}
}

TOF_hist_data TOF::get_hist_data()
{
	TOF_hist_data TOF_data;
	TOF_data.rough_multiplicity_up = RoughElementDown.size(); // RoughElementDown has all elements with leading and trailing edges
	TOF_data.rough_multiplicity_down = RoughElementUp.size();
	TOF_data.preselected_multiplicity_up = 2*ElementDown.size(); // ElementDown only single correct elements -> multiplicity = size*2
	TOF_data.preselected_multiplicity_down = 2*ElementUp.size();
	TOF_data.rough_elements_up = RoughElementUp;
	TOF_data.rough_elements_down = RoughElementDown;
	TOF_data.preselected_elements_up = ElementUp;
	TOF_data.preselected_elements_down = ElementDown;

	return TOF_data;
}