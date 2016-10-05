#ifndef SINGLE_EVENT_H
#define SINGLE_EVENT_H

#include "Start.h"
#include "TOF.h"
#include "D1.h"
#include "D2.h"
#include "HEX.h"
#include "Intermediate.h"
#include "Fiber.h"

class SingleEvent
	: public Start, public TOF, public D1, public D2, public HEX, public Intermediate, public Fiber
{
public:
	SingleEvent();
	SingleEvent(const Config &_config);
	~SingleEvent();
	void fill_good_hits(const int _stage, single_gh_data _good_hit_data); // 10.07: UNUSED NOW, -> if in main
	bool was_correct_event(const int stage);
	hist_data get_hist_data();
	event_to_display get_event_to_display();
	double getTOF();
	void test_calculate_distances();

private:
	bool correct_event;
};

#endif