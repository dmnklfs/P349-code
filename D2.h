#ifndef D2_H
#define D2_H
#include "DCLayer.h"

#define ND2L1  6
#define ND2L2  5
#define ND2L3  4
#define ND2L4  3
#define ND2L5  2 
#define ND2L6  1

class D2
{
public:
	D2();
	~D2();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	D2_hist_data* get_hist_data();
	bool was_correct_event();

private:
	DCLayer *Layer;
	bool correct_event;
};


#endif
