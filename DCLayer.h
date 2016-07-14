#ifndef DCLayer_H
#define DCLayer_H

#include "Config.h"
#include "struct.h"

class DCLayer
{
public:
	DCLayer();
	DCLayer(double _min_drift_time, double _max_drift_time, int _min_no, int _max_no);
	~DCLayer();
	void fill_rough_data(single_gh_data _good_hit_data);
	void fill_preselected_data(single_gh_data _good_hit_data);
	DCLayer_hist_data* get_hist_data();
	bool was_correct_event();

	// after preselection
	std::vector<double> DriftTime;
	std::vector<int> Wire;

	private:
	// rough data: before preselection
	std::vector<double> RoughDriftTime;
	std::vector<int> RoughWire;
	std::vector<int> RoughEdge;

	void check_hits();
	void choose_corr_leading();
	bool check_time_range(double drift_time);
	bool check_size(unsigned int preselected_data_size);
	bool correct_event;

	double min_drift_time, max_drift_time;
	int min_no, max_no;

	
};

#endif