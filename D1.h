#ifndef D1_H
#define D1_H
#include "DCLayer.h"
#include "MinuitFit.h"

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
    TGraph* get_all_hits_plot();
    TGraph* get_detector_plot();
    data_for_D1_simple_calibration get_data_for_simple_calibration();
    data_for_D1_calibration get_data_for_calibration();
    bool plot_event();
	bool was_correct_event();
	int get_no_of_layers_with_hits();
    void calculate_distances_from_wires();
    void calculate_relative_and_absolute_positions(); // now in the function collect_hits_from_all_layers!!
    void collect_hits_from_all_layers();
    double test_get_chosen_position(int _no_of_layer, int _add_in_layer);
    TGraph* plot_track_in_D1();
    void set_hits_absolute_positions();

    std::vector<double> AllWiresAbsolutePositionX;
    std::vector<double> AllWiresAbsolutePositionZ;

    std::vector<double> AllHitsAbsolutePositionX;
    std::vector<double> AllHitsAbsolutePositionZ;

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

    // just for the purpose of the event display - with reversed value of the x coordinate
    std::vector<double> AllHitsAbsolutePositionXEventDisplay;

	// config

};


#endif
