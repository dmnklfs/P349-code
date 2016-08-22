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

bool DCLayer::was_correct_event()
{
	DCLayer::check_hits();
	return correct_event;
}

void DCLayer::check_hits()
{
	// here the correct signals are chosen, do not remove it
	choose_corr_leading();
	
	if (check_size(Wire.size()))
	{
		correct_event = true;
	}
	else correct_event = false;
}

// makes a loop over edges vector and chooses trailing times from correct pairs of leading and trailing edges
// (applies constraints on time range and elements range according to Config)
void DCLayer::choose_corr_leading()
{
	int iterations = RoughEdge.size()-1;
	if (RoughEdge.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdge.at(i)&&0==RoughEdge.at(i+1)&&RoughWire.at(i)==RoughWire.at(i+1))
		{
			if (check_time_range(RoughDriftTime.at(i) + WiresDriftTimeOffset[1+RoughWire.at(i)]))
			{	
				DriftTime.push_back(RoughDriftTime.at(i) + WiresDriftTimeOffset[1+RoughWire.at(i)]);
				Wire.push_back(RoughWire.at(i));
			}
		}
		//if (RoughEdge.at(i)==RoughEdge.at(i+1)) break;
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

void DCLayer::set_drift_time_offset()
{
	// instead of that -> eg. reading from a file in the D1, D2, HEX classes and than setting this drift time offset there
	for (int i = 0; i < 80; i++)
	{
		WiresDriftTimeOffset[i] = 225;
	}
}

