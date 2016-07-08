#ifndef SINGLE_EVENT_H
#define SINGLE_EVENT_H
#include "Start.h"

class SingleEvent
	: public Start
{
public:
	SingleEvent();
	~SingleEvent();
	void fill_good_hits(int _stage, int _layer, int _element, double _treal, int _edge);
	bool was_correct_event(int stage);

private:
	bool correct_event;
};

#endif