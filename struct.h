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
struct start_hist_data
{
	start_hist_data() { }
	unsigned int rough_multiplicity_up, rough_multiplicity_down; 
	unsigned int preselected_multiplicity_up, preselected_multiplicity_down; 
};

struct TOF_hist_data
{
	TOF_hist_data(std::vector<int>& _rough_elements_up, std::vector<int>& _rough_elements_down, std::vector<int>& _preselected_elements_up,	std::vector<int>& _preselected_elements_down) 
		: rough_elements_up(_rough_elements_up), rough_elements_down(_rough_elements_down), preselected_elements_up(_preselected_elements_up), preselected_elements_down(_preselected_elements_down) {}
	unsigned int rough_multiplicity_up, rough_multiplicity_down; 
	unsigned int preselected_multiplicity_up, preselected_multiplicity_down;
	std::vector<int> &rough_elements_up;
	std::vector<int> &rough_elements_down;
	std::vector<int> &preselected_elements_up;
	std::vector<int> &preselected_elements_down;
};

struct D1Layer_hist_data
{
	D1Layer_hist_data(std::vector<int>& _rough_elements, std::vector<int>& _preselected_elements, std::vector<double>& _rough_times, std::vector<double>& _preselected_times)
		: rough_elements(_rough_elements), preselected_elements(_preselected_elements), rough_times(_rough_times), preselected_times(_preselected_times) {}
	unsigned int rough_multiplicity; 
	unsigned int preselected_multiplicity;
	std::vector<int> &rough_elements;
	std::vector<int> &preselected_elements;
	std::vector<double> &rough_times;
	std::vector<double> &preselected_times;
};

struct D1_hist_data
{
	D1Layer_hist_data* layer_data[8];
};

// structure required to fill histos by ... function
struct hist_data
{
	start_hist_data 	*start_data;
	TOF_hist_data 		*tof_data;
	D1_hist_data 		*d1_data;
};

 #endif
