#include "SingleEvent.h"

SingleEvent::SingleEvent()
{
	std::cout << "Object created " << std::endl;
}

SingleEvent::~SingleEvent()
{
	std::cout << "Object destructed " << std::endl;
}

bool SingleEvent::was_correct_event(int stage)
{
	bool start = Start::was_correct_event();

	if (start || stage == 2)
	{
		return true;
	}
	else return false;
}

void SingleEvent::fill_good_hits(int _stage, int _layer, int _element, double _treal, int _edge)
{
	Start::fill_good_hits(_stage, _layer, _element, _treal, _edge);
}
