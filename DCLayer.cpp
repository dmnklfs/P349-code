#include "DCLayer.h"

DCLayer::DCLayer()
{
	min_drift_time = -1500;
	max_drift_time = 1500;
	min_no = 0;
	max_no = 20;
}

DCLayer::DCLayer(double _min_drift_time, double _max_drift_time, int _min_no, int _max_no)
{
	min_drift_time = _min_drift_time;
	max_drift_time = _max_drift_time;
	min_no = _min_no;
	max_no = _max_no;
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
	choose_corr_leading();
	if (check_size(Wire.size()))
	{
		correct_event = true;
	}
	else correct_event = false;
}

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
void DCLayer::choose_corr_leading()
{
	int iterations = RoughEdge.size()-1;
	if (RoughEdge.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdge.at(i)&&0==RoughEdge.at(i+1)&&RoughWire.at(i)==RoughWire.at(i+1))
		{
			if (check_time_range(RoughDriftTime.at(i)))
			{
				DriftTime.push_back(RoughDriftTime.at(i));
				Wire.push_back(RoughWire.at(i));
			}
		}
		if (RoughEdge.at(i)==RoughEdge.at(i+1)) break;
	}
}

bool DCLayer::check_time_range(double drift_time)
{
	if (drift_time > min_drift_time && drift_time < max_drift_time) return true;
	else return false;
}

bool DCLayer::check_size(unsigned int preselected_data_size)
{
	if (-1==min_no || -1 == max_no) return true;
	if (preselected_data_size >= (unsigned int)min_no && preselected_data_size <= (unsigned int)max_no) return true;
	else return false;
}

DCLayer_hist_data* DCLayer::get_hist_data()
{
	DCLayer_hist_data *DCLayer_data = new DCLayer_hist_data(RoughWire, Wire, RoughDriftTime, DriftTime);
	DCLayer_data -> rough_multiplicity = RoughWire.size();
	DCLayer_data -> preselected_multiplicity = Wire.size();
	return DCLayer_data;
}