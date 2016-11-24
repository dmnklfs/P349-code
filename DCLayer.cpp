#include "DCLayer.h"

DCLayer::DCLayer()
{ }

DCLayer::DCLayer(const std::vector<double> &_drift_time_offset, const std::vector<double> &_calib_time, const std::vector<double> &_calib_dist, const double _min_drift_time, const double _max_drift_time, const int _min_no, const int _max_no)
{
	DriftTimeOffset = _drift_time_offset;
	CalibrationTimes = _calib_time;
	CalibrationDistances = _calib_dist;
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
	//std::cout << "DCLayer::choose_corr_leading()" << std::endl;
	int iterations = RoughEdge.size()-1;
	if (RoughEdge.size()-1 < 0) iterations = 0;
	for (int i = 0; i < iterations; i++)
	{
		if (1==RoughEdge.at(i)&&0==RoughEdge.at(i+1)&&RoughWire.at(i)==RoughWire.at(i+1))//&&RoughWire.at(i)>=10&&RoughWire.at(i)<=26)
		{
			//std::cout << "time before check: " << RoughDriftTime.at(i) << std::endl;
			if (check_time_range(RoughDriftTime.at(i) + DriftTimeOffset.at(-1+RoughWire.at(i))))
			{	
				DriftTime.push_back(RoughDriftTime.at(i) + DriftTimeOffset.at(-1+RoughWire.at(i)));
				Wire.push_back(RoughWire.at(i));
				TOT.push_back(RoughDriftTime.at(i+1)-RoughDriftTime.at(i));
				//break;
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
	DCLayer_hist_data *DCLayer_data = new DCLayer_hist_data(RoughWire, Wire, RoughDriftTime, DriftTime, TOT);
	DCLayer_data -> rough_multiplicity = RoughWire.size();
	DCLayer_data -> preselected_multiplicity = Wire.size();
	return DCLayer_data;
}

void DCLayer::apply_drift_time_offset()
{
	for (unsigned int i = 0; i < DriftTime.size(); i++)
	{
		//std::cout << "apply_drift_time_offset" << std::endl;
		//std::cout << Wire.at(i) << std::endl;
		//std::cout << "apply_drift_time_offset" << std::endl;
		DriftTime.at(i) = DriftTime.at(i) + DriftTimeOffset.at(Wire.at(i)-1);
	}
}

void DCLayer::calculate_distances_from_wires()
{
	//std::cout << "DCLayer::calculate_distances_from_wires()" << std::endl;

	for (unsigned int i = 0; i < DriftTime.size(); i++)
	{
		double time_bin_width = max_drift_time/(CalibrationTimes.size()-1);
		double dist_bin_width = 2/(CalibrationTimes.size()-1);
		//std::cout << "drift time: " << DriftTime.at(i) << std::endl;
		double bin_no = floor(DriftTime.at(i)/time_bin_width);
		//std::cout << "bin no: " << bin_no << std::endl;
		double distance = CalibrationDistances.at(bin_no) + dist_bin_width*(CalibrationDistances.at(bin_no+1) - CalibrationDistances.at(bin_no))/(CalibrationTimes.at(bin_no+1) - CalibrationTimes.at(bin_no));
		HitsDistancesFromWires.push_back(distance);
	}
}
