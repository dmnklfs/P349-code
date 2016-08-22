#include "D2.h"

D2::D2()
{
	for (int i = 0; i < 6; i++)
	{
		Layer[i] = new DCLayer(config.D2_drift_time_min[i],config.D2_drift_time_max[i],config.D2_layer_min_hits[i],config.D2_layer_max_hits[i]);
	}
}

D2::D2(Config &_config)
{
	config = _config;
	for (int i = 0; i < 6; i++)
	{
		Layer[i] = new DCLayer(config.D2_drift_time_min[i],config.D2_drift_time_max[i],config.D2_layer_min_hits[i],config.D2_layer_max_hits[i]);
	}
}

D2::~D2()
{  
	for (int i = 0; i < 6; i++)
	{
		delete Layer[i];
	}
}

void D2::fill_good_hits(single_gh_data _good_hit_data)
{
	if (ND2L1 == _good_hit_data.layer) Layer[0]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L2 == _good_hit_data.layer) Layer[1]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L3 == _good_hit_data.layer) Layer[2]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L4 == _good_hit_data.layer) Layer[3]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L5 == _good_hit_data.layer) Layer[4]->DCLayer::fill_rough_data(_good_hit_data);
	if (ND2L6 == _good_hit_data.layer) Layer[5]->DCLayer::fill_rough_data(_good_hit_data);
}

bool D2::was_correct_event()
{
	correct_event = false;
	no_of_layers_with_hits = 0;
	bool correct_in_layer[6];
	for (int i = 0; i < 6; i++)
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

D2_hist_data* D2::get_hist_data()
{
	D2_hist_data* D2_data = new D2_hist_data();
	for (int i = 0; i < 6; i++)
	{
		D2_data -> layer_data[i] = Layer[i]-> DCLayer::get_hist_data();
	}
	return D2_data;
}

int D2::get_no_of_layers_with_hits()
{
	return no_of_layers_with_hits;
}