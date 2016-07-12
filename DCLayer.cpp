#include "DCLayer.h"

DCLayer::DCLayer()
{

}

DCLayer::~DCLayer()
{

}

void DCLayer::fill_rough_data(single_gh_data _good_hit_data)
{
	RoughDriftTime.push_back(_good_hit_data.treal);
	RoughWire.push_back(_good_hit_data.element);
	RoughEdge.push_back(_good_hit_data.edge);
}
void DCLayer::fill_preselected_data(single_gh_data _good_hit_data)
{
	DriftTime.push_back(_good_hit_data.treal);
	Wire.push_back(_good_hit_data.element);
}

bool DCLayer::was_correct_event()
{
	DCLayer::check_hits();
	return correct_event;
}

void DCLayer::check_hits()
{
	if (true)
	{
		Wire = RoughWire;
		DriftTime = RoughDriftTime;
	}
	correct_event = true;
}

DCLayer_hist_data* DCLayer::get_hist_data()
{
	DCLayer_hist_data *DCLayer_data = new DCLayer_hist_data(RoughWire, Wire, RoughDriftTime, DriftTime);
	DCLayer_data -> rough_multiplicity = RoughWire.size();
	DCLayer_data -> preselected_multiplicity = Wire.size();
	return DCLayer_data;
}