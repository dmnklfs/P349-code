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
    data_for_D1_track_reco get_data_for_track_reco();
    bool plot_event();
	bool was_correct_event();
	int get_no_of_layers_with_hits();
    void calculate_distances_from_wires();
    void calculate_wire_positions_in_detector();
    void set_hits_absolute_positions();

private:
    void calculate_distances_from_wires_in_layer();
	DCLayer *Layer[8];
	int no_of_layers_with_hits;
	bool correct_event;
    double D1_max_time;
    int D1_no_of_planes_with_hits;
    int D1_no_of_cells_with_hits;

    bool fit_with_inclined;
    double half_x_dim;
    double half_z_dim;
    double x_lab_position;
    double z_lab_position;
    double z_offset;
    double x_offset;
    double y_rotation_angle;
    double layer_wire_frame_offset[8];
    double layer_angle[8];
    int    no_of_wires[8];
    double distance_to_1st_layer;
    double distance_between_straight_wires;
    double distance_between_inclined_wires;
    double distance_between_layers;
};


#endif
