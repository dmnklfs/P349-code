#ifndef D1_H
#define D1_H
#include "DCLayer.h"

#define ND1L1  8	// layer 1 is the closest one to D1
#define ND1L2  7
#define ND1L3  6
#define ND1L4  5
#define ND1L5  4 
#define ND1L6  3
#define ND1L7  2
#define ND1L8  1 // layer 8 is the closest one to TOF

class D1
{
public:
	D1();
	D1(const Config &_config);
	~D1();
	void fill_good_hits(single_gh_data _good_hit_data);
	D1_hist_data* get_hist_data();
	bool was_correct_event();
	int get_no_of_layers_with_hits();
    void calculate_distances_from_wires();
    void calculate_absolute_positions();

private:
	DCLayer *Layer[8];
	int no_of_layers_with_hits;
	bool correct_event;
    double D1_max_time;

    double x_det_center;
    double z_det_center;
    double z_offset;
    double x_offset;
    double y_rotation_angle;

	// config

};


#endif
