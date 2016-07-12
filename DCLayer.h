#ifndef DCLayer_H
#define DCLayer_H

#include "Config.h"
#include "struct.h"

class DCLayer
{
public:
	DCLayer();
	~DCLayer();
	void fill_rough_data(single_gh_data _good_hit_data);
	void fill_preselected_data(single_gh_data _good_hit_data);
	DCLayer_hist_data* get_hist_data();
	bool was_correct_event();

	// after preselection
	std::vector<double> DriftTime;
	std::vector<int> Wire;

	// rough data: before preselection
	std::vector<double> RoughDriftTime;
	std::vector<int> RoughWire;
	std::vector<int> RoughEdge;

private:
	void check_hits();
	bool correct_event;
};

#endif