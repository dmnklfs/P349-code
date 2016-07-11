#ifndef D1_H
#define D1_H
#include "D1Layer.h"

#define NL1  8
#define NL2  7
#define NL3  6
#define NL4  5
#define NL5  4 
#define NL6  3
#define NL7  2
#define NL8  1

class D1
{
public:
	D1();
	~D1();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	D1_hist_data* get_hist_data();
	bool was_correct_event();

private:
	D1Layer *Layer;
	bool correct_event;
};


#endif
