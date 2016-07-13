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
	// no of correct signals (leading & trailing edge) in up (down) layer
	unsigned int TOF_hits;
	// time range for signals
	double TOF_time_min;
	double TOF_time_max;
	// range of selected elements (1 - 10)
	int TOF_element_min;
	int TOF_element_max;
	// detector position
	// ...

	// ---Intermediate---
	// no of correct signals (leading & trailing edge) in up (down) layer
	unsigned int Intermediate_hits;
	// time range for signals
	double Intermediate_time_min;
	double Intermediate_time_max;
	// range of selected elements (1 - 10)
	int Intermediate_element_min;
	int Intermediate_element_max;
	// detector position
	// ...

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

	// ---DRIFT CHEMBER D2---
	// ...

	// ---HEX---
	// ...

	// ---FIBER HODOSCOPE---
	// ranges of elements
	int element_V_min, element_V_max;
	int element_H_min, element_H_max;
	int element_D_min, element_D_max;
};

#endif