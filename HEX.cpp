#include "HEX.h"

HEX::HEX()
{ }

HEX::HEX(const Config &_config)
{
	for (int i = 0; i < 8; i++)
	{
		Layer[i] = new DCLayer(i, _config.HEX_drift_time_offset, _config.D1_L1_calibration_times, _config.D1_L1_calibration_distances, _config.D1_drift_time_min[i],_config.D1_drift_time_max[i],_config.D1_layer_min_hits[i],_config.D1_layer_max_hits[i]);
	}
}

HEX::~HEX()
{  
	for (int i = 0; i < 7; i++)
	{
		delete Layer[i];
	}
}

void HEX::fill_good_hits(single_gh_data _good_hit_data)
{
	if (NHEXL1 == _good_hit_data.layer) Layer[0] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL2 == _good_hit_data.layer) Layer[1] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL3 == _good_hit_data.layer) Layer[2] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL4 == _good_hit_data.layer) Layer[3] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL5 == _good_hit_data.layer) Layer[4] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL6 == _good_hit_data.layer) Layer[5] -> DCLayer::fill_rough_data(_good_hit_data);
	if (NHEXL7 == _good_hit_data.layer) Layer[6] -> DCLayer::fill_rough_data(_good_hit_data);
}

bool HEX::was_correct_event()
{
	correct_event = false;
	no_of_layers_with_hits = 0;
	bool correct_in_layer[7];
	for (int i = 0; i < 7; i++)
	{
		correct_in_layer[i] = Layer[i]-> DCLayer::was_correct_event();
		if (correct_in_layer[i]) no_of_layers_with_hits++;
	}
	if (no_of_layers_with_hits >= 4)
	{
		correct_event = true;
	}
	return correct_event;
}

HEX_hist_data* HEX::get_hist_data()
{
	HEX_hist_data* HEX_data = new HEX_hist_data();
	for (int i = 0; i < 7; i++)
	{
		HEX_data -> layer_data[i] = Layer[i] -> DCLayer::get_hist_data();
	}
	return HEX_data;
}

int HEX::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}