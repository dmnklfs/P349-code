#ifndef HEX_H
#define HEX_H
#include "DCLayer.h"

#define NHEXL1  7	// layer 1 is the closest one to START
#define NHEXL2  6
#define NHEXL3  5
#define NHEXL4  4
#define NHEXL5  3 
#define NHEXL6  2
#define NHEXL7  1	// layer 7 is the closest one to D2

class HEX
	: public Config
{
public:
	HEX();
	~HEX();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	HEX_hist_data* get_hist_data();
	bool was_correct_event();
	int get_no_of_layers_with_hits();

private:
	DCLayer *Layer[7];
	int no_of_layers_with_hits;
	bool correct_event;
};


#endif