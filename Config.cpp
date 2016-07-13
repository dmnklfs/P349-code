#include "Config.h"

Config::Config()
{
	// here hit = one correct singal (leading and trailing edge corresponding to TWO hits from easyparser)
	start_hits = 1;
	start_time_min = -1500;
	start_time_max = 1500;

	TOF_hits  = 1;
	TOF_time_min = -1500;
	TOF_time_max = 1500;
	TOF_element_min = 5;
	TOF_element_max = 9;

	Intermediate_hits  = 1;
	Intermediate_time_min = -1500;
	Intermediate_time_max = 1500;
	Intermediate_element_min = 1;
	Intermediate_element_max = 16;

	D1_layer1_max_hits = 10;	// unused now. 12.07.16
	D1_layer1_min_hits =  0;
	D1_layer2_max_hits = 10;
	D1_layer2_min_hits =  0;
	D1_layer3_max_hits = 10;
	D1_layer3_min_hits =  0;
	D1_layer4_max_hits = 10;
	D1_layer4_min_hits =  0;
	D1_layer5_max_hits = 10;
	D1_layer5_min_hits =  0;
	D1_layer6_max_hits = 10;
	D1_layer6_min_hits =  0;
	D1_drift_time_min = -1500;
	D1_drift_time_max =  1500;
	
	// ---DRIFT CHEMBER D2---
	// ...

	// ---HEX---
	// ...

	// ---FIBER HODOSCOPE---
	// ranges of elements
	element_V_min = 0;
	element_V_max = 70;
	element_H_min = 0;
	element_H_max = 70;
	element_D_min = 0;
	element_D_max = 70;
}

Config::~Config()
{

}
