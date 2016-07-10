#include "D1Layer.h"

D1Layer::D1Layer()
{

}

D1Layer::~D1Layer()
{

}

void D1Layer::fill_rough_data(single_gh_data _good_hit_data)
{
	RoughDriftTime.push_back(_good_hit_data.treal);
	RoughWire.push_back(_good_hit_data.element);
	RoughEdge.push_back(_good_hit_data.edge);
}
void D1Layer::fill_preselected_data(single_gh_data _good_hit_data)
{
	DriftTime.push_back(_good_hit_data.treal);
	Wire.push_back(_good_hit_data.element);
}

bool D1Layer::was_correct_event()
{
	D1Layer::check_hits();
	return correct_event;
}

void D1Layer::check_hits()
{
	if (true)
	{
		Wire = RoughWire;
		DriftTime = RoughDriftTime;
	}
	correct_event = true;
}

D1Layer_hist_data D1Layer::get_hist_data()
{
	D1Layer_hist_data d1layer_data;
	d1layer_data.rough_multiplicity = RoughWire.size();
	d1layer_data.preselected_multiplicity = Wire.size();
	d1layer_data.rough_elements = RoughWire;
	d1layer_data.preselected_elements = Wire;
	return d1layer_data;
}