#include "D1.h"

D1::D1()
{
	Layer = new DCLayer[8];
}

D1::~D1()
{  
	delete[] Layer;
}

void D1::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	if (1 ==_stage)  // input data before preselection
	{
		if (ND1L1 == _good_hit_data.layer) Layer[0].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L2 == _good_hit_data.layer) Layer[1].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L3 == _good_hit_data.layer) Layer[2].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L4 == _good_hit_data.layer) Layer[3].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L5 == _good_hit_data.layer) Layer[4].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L6 == _good_hit_data.layer) Layer[5].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L7 == _good_hit_data.layer) Layer[6].DCLayer::fill_rough_data(_good_hit_data);
		if (ND1L8 == _good_hit_data.layer) Layer[7].DCLayer::fill_rough_data(_good_hit_data);
	}

	if (2 ==_stage)  // input data after preselection
	{
		if (ND1L1 == _good_hit_data.layer) Layer[0].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L2 == _good_hit_data.layer) Layer[1].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L3 == _good_hit_data.layer) Layer[2].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L4 == _good_hit_data.layer) Layer[3].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L5 == _good_hit_data.layer) Layer[4].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L6 == _good_hit_data.layer) Layer[5].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L7 == _good_hit_data.layer) Layer[6].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND1L8 == _good_hit_data.layer) Layer[7].DCLayer::fill_preselected_data(_good_hit_data);
	}
}

bool D1::was_correct_event()
{
	correct_event = false;
	bool correct_in_layer[8];
	for (int i = 0; i < 8; i++)
	{
		correct_in_layer[i] = Layer[i].DCLayer::was_correct_event();
	}
	if (correct_in_layer[0])
	{
		correct_event = true;
	}
	return correct_event;
}

D1_hist_data* D1::get_hist_data()
{
	D1_hist_data* d1_data = new D1_hist_data();
	for (int i = 0; i < 8; i++)
	{
		d1_data -> layer_data[i] = Layer[i].DCLayer::get_hist_data();
	}
	return d1_data;
}