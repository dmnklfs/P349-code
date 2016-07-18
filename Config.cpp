#include "Config.h"

// in order to set the coincidence between detectors see SingleEvent::was_correct_event() in SingleEvent.cpp
// in order to provide specific conditions for certain detector see function was_correct_event() in appropriate .cpp file

Config::Config()
{
	// here hit = one correct singal (leading and trailing edge corresponding to TWO hits from easyparser)
	start_hits = 1;
	start_time_min = -1500;
	start_time_max = 1500;

	TOF_hits  = 1; // if -1 is set - any number of hits is accepted
	TOF_time_min = -1500;
	TOF_time_max = 1500;
	TOF_element_min = 1;
	TOF_element_max = 10;

	Intermediate_hits  = -1; // if -1 is set - any number of hits is accepted
	Intermediate_time_min = -1500;
	Intermediate_time_max = 1500;
	Intermediate_element_min = 1;
	Intermediate_element_max = 16;

	for (int i = 0; i < 8; i++)
	{
		D1_layer_min_hits[i] = 1;
		D1_layer_max_hits[i] = 9;
		D1_drift_time_min[i] = -1500;
		D1_drift_time_max[i] = 1500;
	}
	
	// ---DRIFT CHEMBER D2---
	for (int i = 0; i < 6; i++)
	{
		D2_layer_min_hits[i] = 1;
		D2_layer_max_hits[i] = 9;
		D2_drift_time_min[i] = -1500;
		D2_drift_time_max[i] = 1500;
	}

	// ---HEX---
	for (int i = 0; i < 7; i++)
	{
		HEX_layer_min_hits[i] = 1;
		HEX_layer_max_hits[i] = 9;
		HEX_drift_time_min[i] = -1500;
		HEX_drift_time_max[i] = 1500;
	}

	// ---FIBER HODOSCOPE---
	// ranges of elements
	element_V_min = 0;
	element_V_max = 70;
	element_H_min = 0;
	element_H_max = 70;
	element_D_min = 0;
	element_D_max = 160;
	hit_V_min = 1;
	hit_V_max = 20;
	hit_H_min = 1;
	hit_H_max = 20;
	hit_D_min = 1;
	hit_D_max = 20;
}

Config::~Config()
{

}
