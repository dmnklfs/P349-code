#include "D1.h"

D1::D1()
{
	Layer1 = new D1Layer;
	Layer2 = new D1Layer;
	Layer7 = new D1Layer;
	Layer8 = new D1Layer;
}

D1::~D1()
{  
	delete Layer1;
	delete Layer2;
	delete Layer7;
	delete Layer8;
}

void D1::fill_good_hits(const int _stage, single_gh_data _good_hit_data)
{
	if (1 ==_stage)  // input data before preselection
	{
		if ( NL1 == _good_hit_data.layer) Layer1 -> D1Layer::fill_rough_data(_good_hit_data);
		if ( NL2 == _good_hit_data.layer) Layer2 -> D1Layer::fill_rough_data(_good_hit_data);
		if ( NL7 == _good_hit_data.layer) Layer7 -> D1Layer::fill_rough_data(_good_hit_data);
		if ( NL8 == _good_hit_data.layer) Layer8 -> D1Layer::fill_rough_data(_good_hit_data);
	}

	if (2 ==_stage)  // input data after preselection
	{
		if ( NL1 == _good_hit_data.layer) Layer1 -> D1Layer::fill_preselected_data(_good_hit_data);
		if ( NL2 == _good_hit_data.layer) Layer2 -> D1Layer::fill_preselected_data(_good_hit_data);
		if ( NL7 == _good_hit_data.layer) Layer7 -> D1Layer::fill_preselected_data(_good_hit_data);
		if ( NL8 == _good_hit_data.layer) Layer8 -> D1Layer::fill_preselected_data(_good_hit_data);
	}
}

bool D1::was_correct_event()
{
	correct_event = false;
	bool layer1 = Layer1 -> D1Layer::was_correct_event();
	bool layer2 = Layer2 -> D1Layer::was_correct_event();
	bool layer7 = Layer7 -> D1Layer::was_correct_event();
	bool layer8 = Layer8 -> D1Layer::was_correct_event();
	if (layer1)
	{
		correct_event = true;
	}
	return correct_event;
}

D1_hist_data D1::get_hist_data()
{
	D1_hist_data d1_data;
	d1_data.layer1_data = Layer1 -> D1Layer::get_hist_data();
	d1_data.layer2_data = Layer2 -> D1Layer::get_hist_data();
	d1_data.layer7_data = Layer7 -> D1Layer::get_hist_data();
	d1_data.layer8_data = Layer8 -> D1Layer::get_hist_data();
	return d1_data;
}