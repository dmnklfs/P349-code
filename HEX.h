#ifndef HEX_H
#define HEX_H
#include "DCLayer.h"
#include "MinuitFit.h"

#define NHEXL1  7	// layer 1 is the closest one to START
#define NHEXL2  6
#define NHEXL3  5
#define NHEXL4  4
#define NHEXL5  3 
#define NHEXL6  2
#define NHEXL7  1	// layer 7 is the closest one to HEX

class HEX
{
public:
    std::vector<double> AllWiresAbsolutePositionX;
    std::vector<double> AllWiresAbsolutePositionZ;

    std::vector<double> AllHitsAbsolutePositionX;
    std::vector<double> AllHitsAbsolutePositionZ;

    HEX();
    HEX(const Config &_config);
    ~HEX();
    void fill_good_hits(single_gh_data _good_hit_data);
    HEX_hist_data* get_hist_data();
    bool was_correct_event();
    int get_no_of_layers_with_hits();
    void calculate_relative_and_absolute_positions();
    void calculate_wire_positions_in_detector();
    void calculate_distances_from_wires();
    double test_get_chosen_position(int _no_of_layer); // dell it 24.12.16
    data_for_HEX_calibration get_data_for_calibration();

    bool plot_event();
    TGraph* get_all_hits_plot();
    TGraph* get_detector_plot();
    void collect_hits_from_all_layers();
    void set_hits_absolute_positions();
    data_for_HEX_track_reco get_data_for_track_reco();

private:
    //void calculate_distances_from_wires();
    DCLayer *Layer[7];
    int no_of_layers_with_hits;
    bool correct_event;
    double HEX_max_time;
    int HEX_no_of_planes_with_hits;
    int HEX_no_of_cells_with_hits;

    bool fit_with_inclined;
    double half_x_dim;
    double half_z_dim;
    double x_lab_position;
    double z_lab_position;
    double z_offset;
    double x_offset;
    double y_rotation_angle;
    double layer_wire_frame_offset[7];
    double layer_angle[7];
    int    no_of_wires[7];
    double distance_to_1st_layer;
    double distance_between_straight_wires;
    double distance_between_inclined_wires;
    double distance_between_layers;

    // just for the purpose of the event display - with reversed value of the x coordinate
    std::vector<double> AllHitsAbsolutePositionXEventDisplay;
};


#endif

/*
Double_t drift_time[90]=
    {
    0.56,   1.67,   2.92,   4.12,   5.48,   6.75,   8.10,   9.53,  10.94,  12.27,
    13.90,  15.29,  16.94,  18.42,  19.86,  21.75,  23.51,  25.15,  27.46,  29.74,
    31.56,  34.03,  36.45,  39.15,  41.84,  44.67,  47.90,  51.20,  54.77,  58.19,
    62.33,  66.00,  70.61,  74.77,  79.16,  84.26,  89.55,  94.53, 100.87, 105.71,
    112.46, 118.18, 124.46, 131.02, 137.87, 145.06, 151.92, 160.83, 167.84, 177.47,
    184.63, 192.93, 201.92, 211.89, 221.30, 230.72, 240.57, 251.95, 262.67, 271.81,
    284.97, 296.39, 309.60, 321.73, 337.37, 348.64, 364.84, 379.19, 395.19, 410.91,
    428.81, 445.82, 468.34, 488.07, 508.18, 531.53, 552.92, 581.01, 611.01, 639.09,
    669.84, 708.49, 749.66, 791.98, 838.73, 880.15, 928.95, 969.01,1012.50,1056.81
    };

Double_t distance[90]=
    {
    0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,
    1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,
    3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,
    4.6,4.7,4.8,4.9,5.0,5.1,5.2,5.3,5.4,5.5,5.6,5.7,5.8,5.9,6.0,
    6.1,6.2,6.3,6.4,6.5,6.6,6.7,6.8,6.9,7.0,7.1,7.2,7.3,7.4,7.5,
    7.6,7.7,7.8,7.9,8.0,8.1,8.2,8.3,8.4,8.5,8.6,8.7,8.8,8.9,9.0
    };
*/