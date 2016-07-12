#include "HEX.h"

HEX::HEX()
{
	Layer = new DCLayer[7];
}

HEX::~HEX()
{  
	delete[] Layer;
}

void HEX::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	if (1 ==_stage)  // input data before preselection
	{
		if (NHEXL1 == _good_hit_data.layer) Layer[0].DCLayer::fill_rough_data(_good_hit_data);
		if (NHEXL2 == _good_hit_data.layer) Layer[1].DCLayer::fill_rough_data(_good_hit_data);
		if (NHEXL3 == _good_hit_data.layer) Layer[2].DCLayer::fill_rough_data(_good_hit_data);
		if (NHEXL4 == _good_hit_data.layer) Layer[3].DCLayer::fill_rough_data(_good_hit_data);
		if (NHEXL5 == _good_hit_data.layer) Layer[4].DCLayer::fill_rough_data(_good_hit_data);
		if (NHEXL6 == _good_hit_data.layer) Layer[5].DCLayer::fill_rough_data(_good_hit_data);
		if (NHEXL7 == _good_hit_data.layer) Layer[6].DCLayer::fill_rough_data(_good_hit_data);
	}

	if (2 ==_stage)  // input data after preselection
	{
		if (NHEXL1 == _good_hit_data.layer) Layer[0].DCLayer::fill_preselected_data(_good_hit_data);
		if (NHEXL2 == _good_hit_data.layer) Layer[1].DCLayer::fill_preselected_data(_good_hit_data);
		if (NHEXL3 == _good_hit_data.layer) Layer[2].DCLayer::fill_preselected_data(_good_hit_data);
		if (NHEXL4 == _good_hit_data.layer) Layer[3].DCLayer::fill_preselected_data(_good_hit_data);
		if (NHEXL5 == _good_hit_data.layer) Layer[4].DCLayer::fill_preselected_data(_good_hit_data);
		if (NHEXL6 == _good_hit_data.layer) Layer[5].DCLayer::fill_preselected_data(_good_hit_data);
		if (NHEXL7 == _good_hit_data.layer) Layer[6].DCLayer::fill_preselected_data(_good_hit_data);
	}
}

bool HEX::was_correct_event()
{
	correct_event = false;
	bool correct_in_layer[7];
	for (int i = 0; i < 7; i++)
	{
		correct_in_layer[i] = Layer[i].DCLayer::was_correct_event();
	}
	if (correct_in_layer[0])
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
		HEX_data -> layer_data[i] = Layer[i].DCLayer::get_hist_data();
	}
	return HEX_data;
}