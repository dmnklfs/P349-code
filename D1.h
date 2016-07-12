#ifndef D1_H
#define D1_H
#include "DCLayer.h"

#define ND1L1  1	// layer 1 is the closest one to the start detector
#define ND1L2  2
#define ND1L3  3
#define ND1L4  4
#define ND1L5  5 
#define ND1L6  6
#define ND1L7  7
#define ND1L8  8 // layer 8 is the closest one to d2 drift chamber

class D1
{
public:
	D1();
	~D1();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	D1_hist_data* get_hist_data();
	bool was_correct_event();

private:
	DCLayer *Layer;
	bool correct_event;
};


#endif
