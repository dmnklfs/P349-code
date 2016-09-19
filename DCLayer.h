#ifndef DCLayer_H
#define DCLayer_H

#include "Config.h"
#include "struct.h"

class DCLayer
{
public:
	DCLayer();
	DCLayer(const std::vector<double> &_drift_time_offset, const std::vector<double> &_calibration_times, const std::vector<double> &_calibration_distances, const double _min_drift_time, const double _max_drift_time, const int _min_no, const int _max_no);
	~DCLayer();
	void fill_rough_data(single_gh_data _good_hit_data);
	DCLayer_hist_data* get_hist_data();
	bool was_correct_event();

	// calibration -> niepotrzebne?
	std::vector<double> CalibrationTimes;
	std::vector<double> CalibrationDistances;
	
	// after preselection
	std::vector<double> DriftTime;
	std::vector<int> Wire;

	std::vector<double> HitsXPosition;

	private:
	// rough data: before preselection
	std::vector<double> RoughDriftTime;
	std::vector<int> RoughWire;
	std::vector<int> RoughEdge;

	void check_hits();
	void choose_corr_leading();
	bool check_time_range(double drift_time);
	bool check_size(unsigned int preselected_data_size);

	void apply_drift_time_offset();
	
	// config
	std::vector<double> drift_time_offset;

	bool correct_event;

	double min_drift_time, max_drift_time;
	int min_no, max_no;

	// offset
	double WiresDriftTimeOffset[80];
};

#endif