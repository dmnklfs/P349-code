#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
	Config();
	~Config();

	// configuration
	// ---START---
	// no of correct signals (leading & trailing edge) in up (down) layer
	unsigned int start_hits;
	// time range for signals
	double start_time_min;
	double start_time_max;
	// detector position
	// ...

	// ---TOF---
	// range of selected elements (1 - 10)
	int TOF_element_min;
	int TOF_element_max;
	// no of correct signals (leading & trailing edge) in up (down) layer
	int TOF_hits;
	// time range for signals
	double TOF_time_min;
	double TOF_time_max;
	// detector position
	// ...

	// ---INTERMEDIATE---
	// range of selected elements (1 - 16)
	int INTERMEDIATE_element_min;
	int INTERMEDIATE_element_max;
	// no of correct signals (leading & trailing edge) in up/down layer
	int INTERMEDIATE_layer_up_hits;
	int INTERMEDIATE_layer_down_hits;
	// time range for signals (depends on the trigger channel in the easyparser; from -1500 to 1500)
	double INTERMEDIATE_time_min;
	double INTERMEDIATE_time_max;
	// detector position
	double INTERMEDIATE_pos_y;
	double INTERMEDIATE_pos_z;

	// ---DRIFT CHAMBER D1---
	// min and max number of hits in layers (if set to -1: any value is ok)
	// for a correct event ALL conditions need to be fulfilled
	int D1_layer1_max_hits;
	int D1_layer1_min_hits;
	int D1_layer2_max_hits;
	int D1_layer2_min_hits;
	int D1_layer3_max_hits;
	int D1_layer3_min_hits;
	int D1_layer4_max_hits;
	int D1_layer4_min_hits;
	int D1_layer5_max_hits;
	int D1_layer5_min_hits;
	int D1_layer6_max_hits;
	int D1_layer6_min_hits;
	// drift time range
	double D1_drift_time_max;
	double D1_drift_time_min;
};

#endif