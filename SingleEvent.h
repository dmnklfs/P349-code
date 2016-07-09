#ifndef SINGLE_EVENT_H
#define SINGLE_EVENT_H
#include "Start.h"
#include "TOF.h"

class SingleEvent
	: public Start, public TOF
{
public:
	SingleEvent();
	~SingleEvent();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data);
	bool was_correct_event(const int stage);
	hist_data get_hist_data();

private:
	bool correct_event;
};

#endif