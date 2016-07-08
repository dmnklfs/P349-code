#include "Config.h"

Config::Config()
{
	
	start_hits = 1;   // one correct singal (leading and trailing edge)
	start_time_min = -1500;
	start_time_max = 1500;

	TOF_element_min = 1;
	TOF_element_max = 10;
	TOF_hits  = 1;
	TOF_time_min = -1500;
	TOF_time_max = 1500;
	
/*
	INTERMEDIATE_element_min = 1;
	INTERMEDIATE_element_max = 16;
	INTERMEDIATE_layer_up_hits = 2;
	INTERMEDIATE_layer_down_hits = 2;
	INTERMEDIATE_time_min = -1500;
	INTERMEDIATE_time_max = -1500;
	//INTERMEDIATE_pos_y;
	//INTERMEDIATE_pos_z;
	D1_layer1_max_hits = 10;
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
	D1_drift_time_max = 1500;*/
}

Config::~Config()
{

}
