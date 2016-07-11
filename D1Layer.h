#ifndef D1LAYER_H
#define D1LAYER_H

#include "Config.h"
#include "struct.h"

class D1Layer
{
public:
	D1Layer();
	~D1Layer();
	void fill_rough_data(single_gh_data _good_hit_data);
	void fill_preselected_data(single_gh_data _good_hit_data);
	D1Layer_hist_data* get_hist_data();
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