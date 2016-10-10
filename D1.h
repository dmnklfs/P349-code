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
    //XZ_positions* get_event_to_display();
    single_detector_data_to_display* get_plots_to_display();
    TGraph* get_all_hits_plot();
    TGraph* get_detector_plot();
	bool was_correct_event();
	int get_no_of_layers_with_hits();
    void calculate_distances_from_wires();
    void calculate_relative_and_absolute_positions(); // now in the function collect_hits_from_all_layers!!
    void collect_hits_from_all_layers();

private:
    void calculate_distances_from_wires_in_layer();
	DCLayer *Layer[8];
	int no_of_layers_with_hits;
	bool correct_event;
    double D1_max_time;

    double half_x_dim;
    double half_z_dim;
    double x_lab_position;
    double z_lab_position;
    double z_offset;
    double x_offset;
    double y_rotation_angle;
    double layer_wire_frame_offset[8];
    double distance_to_1st_layer;
    double distance_between_wires;
    double distance_between_layers;

    std::vector<double> AllHitsAbsolutePositionX;
    std::vector<double> AllHitsAbsolutePositionZ;

    // just for the purpose of the event display - with reversed value of the x coordinate
    std::vector<double> AllHitsAbsolutePositionXEventDisplay;

	// config

};


#endif
