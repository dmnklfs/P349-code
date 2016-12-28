#ifndef D2_H
#define D2_H
#include "DCLayer.h"

#define ND2L1  1	// layer 1 is the closest one to HEX
#define ND2L2  2
#define ND2L3  3
#define ND2L4  4
#define ND2L5  5 
#define ND2L6  6	// layer 6 is the closest one to D1

class D2
{
public:
	D2();
	D2(const Config &_config);
	~D2();
	void fill_good_hits(single_gh_data _good_hit_data);
	D2_hist_data* get_hist_data();
	bool was_correct_event();
	int get_no_of_layers_with_hits();
    void calculate_relative_and_absolute_positions();
    void calculate_distances_from_wires();
    double test_get_chosen_position(int _no_of_layer); // dell it 24.12.16

    // for event display
    bool plot_event();
    TGraph* get_all_hits_plot();
    TGraph* get_detector_plot();
    void collect_hits_from_all_layers();
    void set_hits_absolute_positions();

    std::vector<double> AllWiresAbsolutePositionX;
    std::vector<double> AllWiresAbsolutePositionZ;

    std::vector<double> AllHitsAbsolutePositionX;
    std::vector<double> AllHitsAbsolutePositionZ;

private:
	DCLayer *Layer[6];
	int no_of_layers_with_hits;
	bool correct_event;

	// config
    double half_x_dim;
    double half_z_dim;
    double x_lab_position;
    double z_lab_position;
    double z_offset;
    double x_offset;
    double y_rotation_angle;
    double layer_wire_frame_offset[6];
    double distance_to_1st_layer;
    double distance_between_wires;
    double distance_between_layers;

    // just for the purpose of the event display - with reversed value of the x coordinate
    std::vector<double> AllHitsAbsolutePositionXEventDisplay;
};


#endif
