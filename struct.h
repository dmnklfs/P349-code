#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>
#include <vector>

// in main, good hits loop
struct single_gh_data
{
	int layer, detector, element, edge;
	double treal;	
};

// in order to use references to vectors - struct constructor:
//struct typeOuter {
//  typeOuter(typeInner1& o, typeInner2& t) : one(o), two(t) { }
//  typeInner1 &one;
//  typeInner2 &two;
//}; 

// STRUCT FOR EventDisplay CLASS
struct event_to_display
{
	std::vector<TGraph*> HitsPlots; // tu byly referencje
	std::vector<TGraph*> DetectorPlots;
	TGraph* track;
};

struct data_for_D1_simple_calibration
{
	double positionsX[4]; // from wires
	double positionsZ[4];
	double drift_times[4];
	double distane_from_wire[4];
	int left_right[4]; // left - right information
};

struct data_for_D1_calibration
{
	double positionsX[8]; // from wires
	double positionsZ[8];
	double drift_times[8];
};

// STRUCTS USED IN Hist CLASS
struct start_hist_data
{
	start_hist_data(std::vector<int>& _rough_elements_up, std::vector<int>& _rough_elements_down, std::vector<double>& _preselected_time_up, std::vector<double>& _preselected_time_down)
		: rough_elements_up(_rough_elements_up), rough_elements_down(_rough_elements_down), preselected_time_up(_preselected_time_up), preselected_time_down(_preselected_time_down) { }
	unsigned int rough_multiplicity_up, rough_multiplicity_down; 
	unsigned int preselected_multiplicity_up, preselected_multiplicity_down; 
	std::vector<int> &rough_elements_up;
	std::vector<int> &rough_elements_down;
	std::vector<double> &preselected_time_up;
	std::vector<double> &preselected_time_down;
};

struct TOF_hist_data
{
	TOF_hist_data(std::vector<int>& _rough_elements_up, std::vector<int>& _rough_elements_down, std::vector<int>& _preselected_elements_up,	std::vector<int>& _preselected_elements_down, std::vector<double>& _preselected_time_up, std::vector<double>& _preselected_time_down) 
		: rough_elements_up(_rough_elements_up), rough_elements_down(_rough_elements_down), preselected_elements_up(_preselected_elements_up), preselected_elements_down(_preselected_elements_down), preselected_time_up(_preselected_time_up), preselected_time_down(_preselected_time_down) {}
	unsigned int rough_multiplicity_up, rough_multiplicity_down; 
	unsigned int preselected_multiplicity_up, preselected_multiplicity_down;
	std::vector<int> &rough_elements_up;
	std::vector<int> &rough_elements_down;
	std::vector<int> &preselected_elements_up;
	std::vector<int> &preselected_elements_down;
	std::vector<double> &preselected_time_up;
	std::vector<double> &preselected_time_down;
};

struct Fiber_hist_data
{
	Fiber_hist_data(std::vector<int>& _rough_fibers_V, std::vector<int>& _rough_fibers_H, std::vector<int>& _rough_fibers_D, std::vector<int>& _fibers_V, std::vector<int>& _fibers_H, std::vector<int>& _fibers_D) 
		: rough_fibers_V(_rough_fibers_V), rough_fibers_H(_rough_fibers_H), rough_fibers_D(_rough_fibers_D), fibers_V(_fibers_V), fibers_H(_fibers_H), fibers_D(_fibers_D) {}
	unsigned int rough_multiplicity_V, rough_multiplicity_H, rough_multiplicity_D; 
	unsigned int preselected_multiplicity_V, preselected_multiplicity_H, preselected_multiplicity_D; 
	std::vector<int> &rough_fibers_V;
	std::vector<int> &rough_fibers_H;
	std::vector<int> &rough_fibers_D;
	std::vector<int> &fibers_V;	// preselected
	std::vector<int> &fibers_H;
	std::vector<int> &fibers_D;
};

struct DCLayer_hist_data
{
	DCLayer_hist_data(std::vector<int>& _rough_elements, std::vector<int>& _preselected_elements, std::vector<double>& _rough_times, std::vector<double>& _preselected_times, std::vector<double>& _tot)
		: rough_elements(_rough_elements), preselected_elements(_preselected_elements), rough_times(_rough_times), preselected_times(_preselected_times), tot(_tot) {}
	unsigned int rough_multiplicity; 
	unsigned int preselected_multiplicity;
	std::vector<int> &rough_elements;
	std::vector<int> &preselected_elements;
	std::vector<double> &rough_times;
	std::vector<double> &preselected_times;
	std::vector<double> &tot;
};

struct D1_hist_data
{
	DCLayer_hist_data* layer_data[8];
	int D1_no_of_cells_with_hits;
	int D1_no_of_planes_with_hits;
};

struct D2_hist_data
{
	DCLayer_hist_data* layer_data[6];
};

struct HEX_hist_data
{
	DCLayer_hist_data* layer_data[7];
};

// structure required to fill histos by ... function
struct hist_data
{
	start_hist_data 	*start_data;
	TOF_hist_data 		*tof_data;
	D1_hist_data 		*d1_data;
	D2_hist_data 		*d2_data;
	HEX_hist_data 		*hex_data;
	TOF_hist_data 		*intermediate_data;
	Fiber_hist_data 	*fiber_data;
};

 #endif
