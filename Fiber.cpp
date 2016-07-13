#include "Fiber.h"

Fiber::Fiber()
	: Config::Config()
{ 
	correct_event = true;
}

Fiber::~Fiber()
{ 
	
}


void Fiber::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	if (1 ==_stage)  // input data before preselection
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

	if (2 ==_stage)  // input data after preselection
	{
		if ( 1 == _good_hit_data.layer) Fibers_V.push_back(_good_hit_data.element);
		if ( 0 == _good_hit_data.layer) Fibers_H.push_back(_good_hit_data.element);
		if ( 2 == _good_hit_data.layer) Fibers_D.push_back(_good_hit_data.element);
	}
}

bool Fiber::was_correct_event()
{
	Fiber::check_hits();
	return correct_event;
}

void Fiber::check_hits()
{
	if (true)
	{
		correct_event = true;
	}
	else correct_event = false;
	Fiber::fill_data_if_correct();
}

void Fiber::fill_data_if_correct()
{
	Fibers_V = Rough_Fibers_V;
	Fibers_H = Rough_Fibers_H;
	Fibers_D = Rough_Fibers_D;
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
