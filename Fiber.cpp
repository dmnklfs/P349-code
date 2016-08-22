#include "Fiber.h"

Fiber::Fiber()
{ 
	correct_event = true;
}

Fiber::Fiber(Config &_config)
{
	correct_event = true;
	config = _config;
}

Fiber::~Fiber()
{ 
	
}


void Fiber::fill_good_hits(single_gh_data _good_hit_data)
{
	if ( 1 == _good_hit_data.layer)
	{
		Edge_V.push_back(_good_hit_data.edge);
		Rough_Fibers_V.push_back(_good_hit_data.element);
	}
	if ( 0 == _good_hit_data.layer)
	{
		Edge_H.push_back(_good_hit_data.edge);
		Rough_Fibers_H.push_back(_good_hit_data.element);
	}
	if ( 2 == _good_hit_data.layer)
	{
		Edge_D.push_back(_good_hit_data.edge);
		Rough_Fibers_D.push_back(_good_hit_data.element);
	}
}

bool Fiber::was_correct_event()
{
	Fiber::check_hits();
	return correct_event;
}

void Fiber::check_hits()
{
	choose_corr_leading_V();
	choose_corr_leading_H();
	choose_corr_leading_D();
	if (check_size_V()&&check_size_H()&&check_size_D())
	{
		correct_event = true;
	}
	else correct_event = false;
}

void Fiber::choose_corr_leading_V()
{
	int iterations = Rough_Fibers_V.size()-1;
	if (Edge_V.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==Edge_V.at(i)&&0==Edge_V.at(i+1)&&Rough_Fibers_V.at(i)==Rough_Fibers_V.at(i+1))
		{
			if (check_elements_range_V(Rough_Fibers_V.at(i)))
			{
				Fibers_V.push_back(Rough_Fibers_V.at(i));
			}
		}
		//if (Edge_V.at(i)==Edge_V.at(i+1)) break;
	}
}

void Fiber::choose_corr_leading_H()
{
	int iterations = Rough_Fibers_H.size()-1;
	if (Edge_H.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==Edge_H.at(i)&&0==Edge_H.at(i+1)&&Rough_Fibers_H.at(i)==Rough_Fibers_H.at(i+1))
		{
			if (check_elements_range_H(Rough_Fibers_H.at(i)))
			{
				Fibers_H.push_back(Rough_Fibers_H.at(i));
			}
		}
		//if (Edge_H.at(i)==Edge_H.at(i+1)) break;
	}
}

void Fiber::choose_corr_leading_D()
{
	int iterations = Rough_Fibers_D.size()-1;
	if (Edge_D.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==Edge_D.at(i)&&0==Edge_D.at(i+1)&&Rough_Fibers_D.at(i)==Rough_Fibers_D.at(i+1))
		{
			if (check_elements_range_D(Rough_Fibers_D.at(i)))
			{
				Fibers_D.push_back(Rough_Fibers_D.at(i));
			}
		}
		//if (Edge_D.at(i)==Edge_D.at(i+1)) break;
	}
}

bool Fiber::check_elements_range_V(int element)
{
	if (element >= config.element_V_min && element <= config.element_V_max)//&&element!=48)
	{
		return true;
	}
	else return false;
}

bool Fiber::check_elements_range_H(int element)
{
	if (element >= config.element_H_min && element <= config.element_H_max)//&&element!=48)
	{
		return true;
	}
	else return false;
}

bool Fiber::check_elements_range_D(int element)
{
	if (element >= config.element_D_min && element <= config.element_D_max)
	{
		return true;
	}
	else return false;
}

bool Fiber::check_size_V()
{
	if (-1 == config.hit_V_min || -1 == config.hit_V_max) return true;
	if (Fibers_V.size()>=(unsigned int)config.hit_V_min && Fibers_V.size()<=(unsigned int)config.hit_V_max) return true;
	else return false;
}

bool Fiber::check_size_H()
{
	if (-1 == config.hit_H_min || -1 == config.hit_H_max) return true;
	if (Fibers_H.size()>=(unsigned int)config.hit_H_min && Fibers_H.size()<=(unsigned int)config.hit_H_max) return true;
	else return false;
}

bool Fiber::check_size_D()
{
	if (-1 == config.hit_D_min || -1 == config.hit_D_max) return true;
	if (Fibers_D.size()>=(unsigned int)config.hit_D_min && Fibers_D.size()<=(unsigned int)config.hit_D_max) return true;
	else return false;
}

Fiber_hist_data* Fiber::get_hist_data()
{
	Fiber_hist_data *Fiber_data = new Fiber_hist_data(Rough_Fibers_V, Rough_Fibers_H, Rough_Fibers_D, Fibers_V, Fibers_H, Fibers_D);
	Fiber_data -> rough_multiplicity_V = Rough_Fibers_V.size(); 
	Fiber_data -> rough_multiplicity_H = Rough_Fibers_H.size(); 
	Fiber_data -> rough_multiplicity_D = Rough_Fibers_D.size(); 
	Fiber_data -> preselected_multiplicity_V = Fibers_V.size(); 
	Fiber_data -> preselected_multiplicity_H = Fibers_H.size(); 
	Fiber_data -> preselected_multiplicity_D = Fibers_D.size(); 
	return Fiber_data;
}
