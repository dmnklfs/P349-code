#include "D2.h"

D2::D2()
{
	Layer = new DCLayer[6];
}

D2::~D2()
{  
	delete[] Layer;
}

void D2::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	if (1 ==_stage)  // input data before preselection
	{
		if (ND2L1 == _good_hit_data.layer) Layer[0].DCLayer::fill_rough_data(_good_hit_data);
		if (ND2L2 == _good_hit_data.layer) Layer[1].DCLayer::fill_rough_data(_good_hit_data);
		if (ND2L3 == _good_hit_data.layer) Layer[2].DCLayer::fill_rough_data(_good_hit_data);
		if (ND2L4 == _good_hit_data.layer) Layer[3].DCLayer::fill_rough_data(_good_hit_data);
		if (ND2L5 == _good_hit_data.layer) Layer[4].DCLayer::fill_rough_data(_good_hit_data);
		if (ND2L6 == _good_hit_data.layer) Layer[5].DCLayer::fill_rough_data(_good_hit_data);
	}

	if (2 ==_stage)  // input data after preselection
	{
		if (ND2L1 == _good_hit_data.layer) Layer[0].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND2L2 == _good_hit_data.layer) Layer[1].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND2L3 == _good_hit_data.layer) Layer[2].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND2L4 == _good_hit_data.layer) Layer[3].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND2L5 == _good_hit_data.layer) Layer[4].DCLayer::fill_preselected_data(_good_hit_data);
		if (ND2L6 == _good_hit_data.layer) Layer[5].DCLayer::fill_preselected_data(_good_hit_data);
	}
}

bool D2::was_correct_event()
{
	correct_event = false;
	bool correct_in_layer[6];
	for (int i = 0; i < 6; i++)
	{
		correct_in_layer[i] = Layer[i].DCLayer::was_correct_event();
	}
	if (correct_in_layer[0])
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
		D2_data -> layer_data[i] = Layer[i].DCLayer::get_hist_data();
	}
	return D2_data;
}