#ifndef D2_H
#define D2_H
#include "DCLayer.h"

#define ND2L1  1	// layer 1 is the closest one to HEX
#define ND2L2  2
#define ND2L3  3
#define ND2L4  4
#define ND2L5  5 
#define ND2L6  6	// layer 6 is the closest one to D1

class D2
	: public Config
{
public:
	D2();
	~D2();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	D2_hist_data* get_hist_data();
	bool was_correct_event();
	int get_no_of_layers_with_hits();

private:
	DCLayer *Layer[6];
	int no_of_layers_with_hits;
	bool correct_event;
};


#endif
