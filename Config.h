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
	int start_hits;
	// time range for signals
	double start_time_min;
	double start_time_max;
	// detector position
	// ...

	// ---TOF---
	// no of correct signals (leading & trailing edge) in up (down) layer
	int TOF_hits;
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
	int Intermediate_hits;
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
	int D1_layer_max_hits[8];
	int D1_layer_min_hits[8];

	// drift time range
	double D1_drift_time_max[8];
	double D1_drift_time_min[8];

	// ---DRIFT CHEMBER D2---
	// min and max number of hits in layers (if set to -1: any value is ok)
	int D2_layer_max_hits[6];
	int D2_layer_min_hits[6];

	// drift time range
	double D2_drift_time_max[6];
	double D2_drift_time_min[6];

	// ---HEX---
	// min and max number of hits in layers (if set to -1: any value is ok)
	int HEX_layer_max_hits[7];
	int HEX_layer_min_hits[7];

	// drift time range
	double HEX_drift_time_max[7];
	double HEX_drift_time_min[7];

	// ---FIBER HODOSCOPE---
	// ranges of elements
	int element_V_min, element_V_max;
	int element_H_min, element_H_max;
	int element_D_min, element_D_max;
};

#endif